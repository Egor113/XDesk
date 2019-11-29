--Тема №5. Вложенные запросы. Написать запрос, выводящий…

-- 1) все заказы, оформленные продавцами из Лондона (London) без использования join

select * from orders where 
snum = some(select snum from sales where city = 'London');

-- 2) всех продавцов, имеющих комиссию выше средней

select * from sales where
comm > (select avg(comm) from sales);

-- 3) общее количество продавцов и покупателей из каждого города, отсортированное по убыванию количества
select * from sales;
select * from clients;

WITH t1 AS
(SELECT COUNT(*) as c, city FROM Clients
GROUP BY city
UNION
SELECT COUNT (*) as c, city FROM Sales
GROUP BY city)
SELECT SUM (c) s, city FROM t1
GROUP BY city
ORDER BY s desc;

-- 4) 2, 3, и 4 строки таблицы Sales, отсортированной по возрастанию имени продавца

SELECT snum, sname, city, comm FROM (
  select snum, sname, city, comm, rownum AS rn from sales)
WHERE rn in (2,3,4)
order by sname;

-- Тема №6. Соотнесенные запросы. Написать запрос, выводящий…

-- 1) имена и номера всех продавцов, которые имеют не менее одного заказчика

select sname, snum from sales s where (select count(*)
from clients c where c.cnum=s.snum) >= 1;

-- 2) всех продавцов, имеющих комиссию не ниже средней по своему городу

select * from sales s1 
where comm < (select avg(comm) from sales s2 where s1.city = s2.city);

-- 3) [подзапросом] номера и имена всех продавцов, имеющих в своем городе заказчиков, которых они не обслуживают

select * from sales;
select * from clients;

select distinct s.snum, sname from sales s where exists 
(select c.snum from clients c where c.snum != s.snum and s.city = c.city);

-- 4) [join’ом] номера и имена всех продавцов, имеющих в своем городе заказчиков, которых они не обслуживают

select distinct s.snum, sname from sales s 
inner join clients c on c.city = s.city
where s.snum != c.snum;

select * from orders;

-- 5) номера всех заказов, а также разницу между стоимостью каждого заказа и средней стоимостью заказа за тот же день

select onum, onum-(select avg(onum)
from orders r2 where r1.odate = r2.odate)
from orders r1
where r1.onum is not null;


with average as (select avg(amt) from orders 
--group by EXTRACT(day FROM odate)
--order by EXTRACT(day FROM odate)
)
select onum, odate , amt - avg(amt) from orders
group by odate, onum;

(select * from average);

select avg(amt) from orders 
group by EXTRACT(day FROM odate)
order by EXTRACT(day FROM odate);

select amt from orders where amt is not null;

select amt, EXTRACT(day FROM odate) "oday" from orders 
group by EXTRACT(day FROM odate)
order by EXTRACT(day FROM odate);

select onum, abs(sum(amt) - (select avg(nvl(amt,0)) avrg from orders)) diff, odate from orders
group by odate, onum;

-- Тема №7. Изменение содержимого таблиц. Написать запрос, который…

-- 1) делает все города проживания клиентов, начинающиеся с S, написанными большими буквами, затем откатывает изменения

select * from clients;

update clients set city = upper(city)
where city like 'S%';

rollback;

-- 2) добавляет нового продавца (некоторые из полей можно оставить пустыми), причем новый продавец должен стать видимым для остальных слушателей курса

select * from sales;

insert into sales values ('1000', 'Ogdanets', 'Moscow', '');

select * from sales where SNAME = 'Ogdanets';

commit;

-- 3) удаляет всех продавцов, у которых не указан город проживания и чьи имена длиннее восьми символов

delete from sales
where city is null and length(sname) > 8;

-- Тема №8. Создание таблиц. Написать запрос, который…

-- 1) создает новую таблицу, содержащую только те строки из таблицы клиентов, в каждой из которых нет значений null

select * from clients;

create table clients_Ogdanets as
select * from clients where (cnum is not null) and 
(cname is not null) and (city is not null) and (rating is not null)
and (snum is not null);

select * from clients_Ogdanets;

-- 2) создает представление на основе таблицы из п.1, включающее только столбцы cname и city

create view clients_Ogdanets_view as
(select cname, city from clients_Ogdanets);

select * from clients_Ogdanets_view;

-- 3) удаляет таблицу из п.1

drop table clients_Ogdanets;

-- 4) пробует запросить содержимое из представления из п.2 выполнить п.1, затем снова п.4

select * from clients_Ogdanets_view;

create table clients_Ogdanets as
select * from clients where (cnum is not null) and 
(cname is not null) and (city is not null) and (rating is not null)
and (snum is not null);

select * from clients_Ogdanets_view;

-- Тема №9. Ограничения целостности данных. (все названия каждый придумывает самостоятельно, т.е. у каждого должен быть свой объект БД)

-- 1) Создать новую таблицу (таблица C), содержащую только уникальные строки таблицы Clients
create table c_Ogdanets as
select distinct * from clients;

select * from c_Ogdanets;

select * from clients;

select distinct * from clients;

-- 2) Создать новую таблицу (таблица S), содержащую только уникальные строки таблицы Sales

create table s_Ogdanets as
select distinct * from sales;

select * from sales;

select * from s_Ogdanets;

drop table s_Ogdanets;

-- 3) Добавить PRIMARY KEY на столбец snum таблицы S (при необходимости удалить повторяющиеся snumы и null-значения)
alter table s_Ogdanets
add constraint snum_pk_Ogdanets PRIMARY KEY (snum);

ALTER TABLE s_Ogdanets
DROP CONSTRAINT snum_pk;

delete from s_Ogdanets 
where snum is null or rowid not in
(SELECT MIN(rowid)
FROM s_Ogdanets
GROUP BY snum);

commit;

-- 4) Добавить FOREIGN KEY на столбец snum таблицы С (при необходимости из C удалить строки с такими snum, которых нет в S)

ALTER TABLE products
ADD CONSTRAINT fk_supplier
  FOREIGN KEY (supplier_id)
  REFERENCES supplier(supplier_id);
  
alter table c_Ogdanets
add constraint fk_c_Ogdanets
    foreign key (snum)
    references s_Ogdanets(snum);
    
delete from c_Ogdanets 
where snum not in
(SELECT snum from s_Ogdanets);





