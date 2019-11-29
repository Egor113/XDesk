select * from ticket where state_id =  '-1';

select * from ticket where state_id =  '-1' and text like 'Ogdanets%';

INSERT INTO task (id, change_id, ticket_id, guid, header, text, priority_id, state_id, client_id, create_date, external_system) 
select id ,'IDC2D620524153zdzPWAoX9OFgW4UB', id, guid, header, text, '3', '2', '106', create_date, 'ASKO' from ticket 
where id in (select id from ticket where state_id =  '-1');

select * from ticket;

select * from task order by id desc;

select count (*) from task;

rollback;