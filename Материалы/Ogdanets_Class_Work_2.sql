--���� �5. ��������� �������. �������� ������, ���������

-- 1) ��� ������, ����������� ���������� �� ������� (London) ��� ������������� join

select * from orders where 
snum = some(select snum from sales where city = 'London');

-- 2) ���� ���������, ������� �������� ���� �������

select * from sales where
comm > (select avg(comm) from sales);

-- 3) ����� ���������� ��������� � ����������� �� ������� ������, ��������������� �� �������� ����������
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

-- 4) 2, 3, � 4 ������ ������� Sales, ��������������� �� ����������� ����� ��������

SELECT snum, sname, city, comm FROM (
  select snum, sname, city, comm, rownum AS rn from sales)
WHERE rn in (2,3,4)
order by sname;

-- ���� �6. ������������ �������. �������� ������, ���������

-- 1) ����� � ������ ���� ���������, ������� ����� �� ����� ������ ���������

select sname, snum from sales s where (select count(*)
from clients c where c.cnum=s.snum) >= 1;

-- 2) ���� ���������, ������� �������� �� ���� ������� �� ������ ������

select * from sales s1 
where comm < (select avg(comm) from sales s2 where s1.city = s2.city);

-- 3) [�����������] ������ � ����� ���� ���������, ������� � ����� ������ ����������, ������� ��� �� �����������

select * from sales;
select * from clients;

select distinct s.snum, sname from sales s where exists 
(select c.snum from clients c where c.snum != s.snum and s.city = c.city);

-- 4) [join���] ������ � ����� ���� ���������, ������� � ����� ������ ����������, ������� ��� �� �����������

select distinct s.snum, sname from sales s 
inner join clients c on c.city = s.city
where s.snum != c.snum;

select * from orders;

-- 5) ������ ���� �������, � ����� ������� ����� ���������� ������� ������ � ������� ���������� ������ �� ��� �� ����

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

-- ���� �7. ��������� ����������� ������. �������� ������, �������

-- 1) ������ ��� ������ ���������� ��������, ������������ � S, ����������� �������� �������, ����� ���������� ���������

select * from clients;

update clients set city = upper(city)
where city like 'S%';

rollback;

-- 2) ��������� ������ �������� (��������� �� ����� ����� �������� �������), ������ ����� �������� ������ ����� ������� ��� ��������� ���������� �����

select * from sales;

insert into sales values ('1000', 'Ogdanets', 'Moscow', '');

select * from sales where SNAME = 'Ogdanets';

commit;

-- 3) ������� ���� ���������, � ������� �� ������ ����� ���������� � ��� ����� ������� ������ ��������

delete from sales
where city is null and length(sname) > 8;

-- ���� �8. �������� ������. �������� ������, �������

-- 1) ������� ����� �������, ���������� ������ �� ������ �� ������� ��������, � ������ �� ������� ��� �������� null

select * from clients;

create table clients_Ogdanets as
select * from clients where (cnum is not null) and 
(cname is not null) and (city is not null) and (rating is not null)
and (snum is not null);

select * from clients_Ogdanets;

-- 2) ������� ������������� �� ������ ������� �� �.1, ���������� ������ ������� cname � city

create view clients_Ogdanets_view as
(select cname, city from clients_Ogdanets);

select * from clients_Ogdanets_view;

-- 3) ������� ������� �� �.1

drop table clients_Ogdanets;

-- 4) ������� ��������� ���������� �� ������������� �� �.2 ��������� �.1, ����� ����� �.4

select * from clients_Ogdanets_view;

create table clients_Ogdanets as
select * from clients where (cnum is not null) and 
(cname is not null) and (city is not null) and (rating is not null)
and (snum is not null);

select * from clients_Ogdanets_view;

-- ���� �9. ����������� ����������� ������. (��� �������� ������ ����������� ��������������, �.�. � ������� ������ ���� ���� ������ ��)

-- 1) ������� ����� ������� (������� C), ���������� ������ ���������� ������ ������� Clients
create table c_Ogdanets as
select distinct * from clients;

select * from c_Ogdanets;

select * from clients;

select distinct * from clients;

-- 2) ������� ����� ������� (������� S), ���������� ������ ���������� ������ ������� Sales

create table s_Ogdanets as
select distinct * from sales;

select * from sales;

select * from s_Ogdanets;

drop table s_Ogdanets;

-- 3) �������� PRIMARY KEY �� ������� snum ������� S (��� ������������� ������� ������������� snum� � null-��������)
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

-- 4) �������� FOREIGN KEY �� ������� snum ������� � (��� ������������� �� C ������� ������ � ������ snum, ������� ��� � S)

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





