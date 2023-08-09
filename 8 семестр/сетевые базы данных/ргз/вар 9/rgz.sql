drop sequence uid_seq;
drop sequence sid_seq;

create sequence uid_seq start with 1 increment by 1;
create sequence sid_seq start with 1 increment by 1;

drop table speciality;
drop table university;

create table university (
    univ_id number(3) not null,
    uname varchar2(50) not null,

    constraint univid_uk unique(univ_id),
    constraint uname primary key(uname)
);

create table speciality (
    spec_id number(3) not null,
    sname varchar2(50) not null,
    univid_val number(3) not null,

    constraint specid_pk primary key(spec_id),
    constraint univid_fk foreign key(univid_val) references university(univ_id) 
);

create or replace package tablePack is
    procedure add_data;
    procedure clear_data;
end;
/
create or replace package body tablePack is
    procedure add_data is
    begin
        insert into university values (uid_seq.nextval, 'SibSUTIS');
        insert into speciality values (sid_seq.nextval, 'IVT', uid_seq.currval);
        insert into speciality values (sid_seq.nextval, 'MRM', uid_seq.currval);
        insert into speciality values (sid_seq.nextval, 'MTS', uid_seq.currval);
        insert into speciality values (sid_seq.nextval, 'AVS', uid_seq.currval);

        insert into university values (uid_seq.nextval, 'NSU');
        insert into speciality values (sid_seq.nextval, 'IVT', uid_seq.currval);
        insert into speciality values (sid_seq.nextval, 'Economics', uid_seq.currval);
        insert into speciality values (sid_seq.nextval, 'MassMedia', uid_seq.currval);

        insert into university values (uid_seq.nextval, 'NSPU');
        insert into speciality values (sid_seq.nextval, 'IVT', uid_seq.currval);
        insert into speciality values (sid_seq.nextval, 'English', uid_seq.currval);
        insert into speciality values (sid_seq.nextval, 'PhysMath', uid_seq.currval);
        insert into speciality values (sid_seq.nextval, 'French', uid_seq.currval);

        insert into university values (uid_seq.nextval, 'NSTU');
        insert into speciality values (sid_seq.nextval, 'IVT', uid_seq.currval);
        insert into speciality values (sid_seq.nextval, 'English', uid_seq.currval);
        insert into speciality values (sid_seq.nextval, 'Economics', uid_seq.currval);
        insert into speciality values (sid_seq.nextval, 'MTS', uid_seq.currval);

        insert into university values (uid_seq.nextval, 'MSU');
        insert into speciality values (sid_seq.nextval, 'IVT', uid_seq.currval);
        insert into speciality values (sid_seq.nextval, 'Economics', uid_seq.currval);
        insert into speciality values (sid_seq.nextval, 'MassMedia', uid_seq.currval);
        insert into speciality values (sid_seq.nextval, 'Mec.-Math', uid_seq.currval);
        insert into speciality values (sid_seq.nextval, 'Physics', uid_seq.currval);
        insert into speciality values (sid_seq.nextval, 'Chemical', uid_seq.currval);

        insert into university values (uid_seq.nextval, 'MSTU');
        insert into speciality values (sid_seq.nextval, 'IVT', uid_seq.currval);
        insert into speciality values (sid_seq.nextval, 'English', uid_seq.currval);
        insert into speciality values (sid_seq.nextval, 'Economics', uid_seq.currval);
        insert into speciality values (sid_seq.nextval, 'PhysMath', uid_seq.currval);
        insert into speciality values (sid_seq.nextval, 'MTS', uid_seq.currval);

        insert into university values (uid_seq.nextval, 'MSPU');
        insert into speciality values (sid_seq.nextval, 'IVT', uid_seq.currval);
        insert into speciality values (sid_seq.nextval, 'English', uid_seq.currval);
        insert into speciality values (sid_seq.nextval, 'PhysMath', uid_seq.currval);
        insert into speciality values (sid_seq.nextval, 'French', uid_seq.currval);
    end add_data;

    procedure clear_data is 
    begin
        delete from university;
        delete from speciality;
        execute immediate 'drop sequence uid_seq';
        execute immediate 'drop sequence sid_seq';
    end clear_data;
end;
/
begin 
    tablePack.add_data;
end;
/

drop table delete_register;
create table delete_register (
    command_name varchar2(20) not null,
    deleted_record varchar2(50) not null,
    time_of_event date
);
commit;

create or replace trigger del_trigger
    before delete on university
    for each row
begin
    if deleting then
        insert into delete_register(command_name, deleted_record, time_of_event)
            values ('Delete', :old.uname, sysdate);
    end if;
end;
/

create or replace package pcg_2 is
    type top2 is varray(2) of varchar2(50);
    procedure del_university(to_delete in varchar2 default null);
    procedure view_top2;
end pcg_2;
/
create or replace package body pcg_2 is
    type t_top2 is varray(2) of varchar2(50);
    p_top2 t_top2 := t_top2('first', 'second');

    procedure del_university(to_delete in varchar2 default null) is
    begin
        delete from speciality where univid_val in (select univ_id from university where uname = to_delete);
        delete from university where uname = to_delete;
        commit;
    end del_university;

    procedure view_top2 is
        u_first_max varchar2(50);
        u_second_max varchar2(50);
        no_fetch exception;
    begin
        select uname into u_first_max from (select uname, (select count(*) from speciality where univ_id = univid_val) as num 
            from university order by num desc) where rownum = 1; 
        select uname into u_second_max from (select a.*, rownum rnum from (select uname, (select count(*) from speciality where univ_id = univid_val) as num 
            from university order by num desc) a where rownum <= 2) where rnum = 2;
        
        if u_first_max = '' or u_second_max = '' then
            raise no_fetch;
        end if;

        p_top2(1) := u_first_max;
        p_top2(2) := u_second_max;

        dbms_output.put_line('First min: ' || p_top2(1));
        dbms_output.put_line('Second min: ' ||  p_top2(2));

        exception when no_fetch then
            dbms_output.put_line('No data was fetched');
            raise;
        
    end view_top2;
end pcg_2;
/

begin 
    pcg_2.del_university('GBD');
    pcg_2.view_top2;
end;