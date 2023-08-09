DROP SEQUENCE seq_service;
DROP SEQUENCE seq_addcmp;

CREATE SEQUENCE seq_service;
CREATE SEQUENCE seq_addcmp;

DROP TABLE service_types;
DROP TABLE add_cmp;
DROP TABLE reg;

CREATE TABLE add_cmp (
    id_add_comp NUMBER(4, 0) NOT NULL,
    name_cmp VARCHAR2(20) NOT NULL,
    country VARCHAR2(20) NOT NULL,

    CONSTRAINT id_add_comp PRIMARY KEY(id_add_comp)
);

CREATE TABLE service_types (
    id_srv NUMBER(4, 0) NOT NULL,
    add_cmp VARCHAR2(20) NOT NULL,
    id_comp NUMBER(4, 0) NOT NULL,

    CONSTRAINT id_srv PRIMARY KEY(id_srv),
    CONSTRAINT id_comp FOREIGN KEY(id_comp) REFERENCES add_cmp(id_add_comp)
);

CREATE TABLE reg (
    id_srv NUMBER(4, 0) NOT NULL,
    serv VARCHAR2(20) NOT NULL,
    id_comp NUMBER(4, 0) NOT NULL,
    dates DATE,
    usr VARCHAR2(20) NOT NULL
);
COMMIT;

CREATE OR REPLACE PACKAGE WorkTablePack IS
    PROCEDURE add_data;
    PROCEDURE delete_data;
END;
/

CREATE OR REPLACE PACKAGE BODY WorkTablePack IS
    PROCEDURE add_data IS
    BEGIN
        INSERT INTO add_cmp VALUES (seq_service.NEXTVAL, 'TACC', 'Russia');

        INSERT INTO service_types VALUES (seq_addcmp.NEXTVAL, 'add', seq_service.CURRVAL);
        INSERT INTO service_types VALUES (seq_addcmp.NEXTVAL, 'article', seq_service.CURRVAL);

        INSERT INTO add_cmp VALUES (seq_service.NEXTVAL, 'RT', 'Russia');

        INSERT INTO service_types VALUES (seq_addcmp.NEXTVAL, 'add', seq_service.CURRVAL);
        INSERT INTO service_types VALUES (seq_addcmp.NEXTVAL, 'commercial', seq_service.CURRVAL);

        INSERT INTO add_cmp VALUES (seq_service.NEXTVAL, 'WPP', 'Great Britain');

        INSERT INTO service_types VALUES (seq_addcmp.NEXTVAL, 'article', seq_service.CURRVAL);
        INSERT INTO service_types VALUES (seq_addcmp.NEXTVAL, 'promotion', seq_service.CURRVAL);

        INSERT INTO add_cmp VALUES (seq_service.NEXTVAL, 'Amuse', 'Japap');

        INSERT INTO service_types VALUES (seq_addcmp.NEXTVAL, 'commercial', seq_service.CURRVAL);
        INSERT INTO service_types VALUES (seq_addcmp.NEXTVAL, 'promotion', seq_service.CURRVAL);

        INSERT INTO add_cmp VALUES (seq_service.NEXTVAL, 'Maer', 'Russia');

        INSERT INTO service_types VALUES (seq_addcmp.NEXTVAL, 'add', seq_service.CURRVAL);
        INSERT INTO service_types VALUES (seq_addcmp.NEXTVAL, 'article', seq_service.CURRVAL);

        INSERT INTO add_cmp VALUES (seq_service.NEXTVAL, 'Dentsu', 'Japan');

        INSERT INTO service_types VALUES (seq_addcmp.NEXTVAL, 'promotion', seq_service.CURRVAL);
        INSERT INTO service_types VALUES (seq_addcmp.NEXTVAL, 'add', seq_service.CURRVAL);

        INSERT INTO add_cmp VALUES (seq_service.NEXTVAL, 'BBDO', 'World');

        INSERT INTO service_types VALUES (seq_addcmp.NEXTVAL, 'commercial', seq_service.CURRVAL);
        INSERT INTO service_types VALUES (seq_addcmp.NEXTVAL, 'promotion', seq_service.CURRVAL);

    END add_data;

    PROCEDURE delete_data IS
    BEGIN
        DELETE FROM add_cmp;
        DELETE FROM service_types;
        EXECUTE IMMEDIATE 'DROP SEQUENCE seq_service';
        EXECUTE IMMEDIATE 'DROP SEQUENCE seq_addcmp';
        EXECUTE IMMEDIATE 'CREATE SEQUENCE seq_service';
        EXECUTE IMMEDIATE 'CREATE SEQUENCE seq_addcmp';
    END delete_data;
END;
/

-- CREATE OR REPLACE TRIGGER del
--     BEFORE DELETE ON service_types
--     FOR EACH ROW
-- DECLARE
--     usr VARCHAR2(30);
-- BEGIN
--     usr := USER;
--     INSERT INTO reg (id_srv, serv, id_comp, dates, usr)
--     VALUES (:old.id_srv, :old.add_cmp, :old.id_comp, sysdate, usr);
-- END;
-- /

CREATE OR REPLACE PACKAGE WorkPack IS
    PROCEDURE work_data;
    PROCEDURE delete_service (servs IN VARCHAR2);
    PROCEDURE dyna (usr IN VARCHAR2);
END;
/

CREATE OR REPLACE PACKAGE BODY WorkPack IS
    PROCEDURE work_data IS
    BEGIN
        WorkTablePack.delete_data;
        WorkTablePack.add_data;
    END work_data;

    PROCEDURE delete_service (servs IN VARCHAR2) AS
    BEGIN
        DELETE FROM service_types WHERE add_cmp = servs;
        COMMIT;
    EXCEPTION
        WHEN NO_DATA_FOUND THEN
            DBMS_OUTPUT.PUT_LINE('Данные о ' || servs || ' не найдены в таблице "add_cmp"');
        WHEN OTHERS THEN
            DBMS_OUTPUT.PUT_LINE('Ошибка при удалении');

    END delete_service;

    PROCEDURE dyna (usr in VARCHAR2) AS
    BEGIN
      EXECUTE IMMEDIATE 'CREATE OR REPLACE TRIGGER dele BEFORE DELETE ON service_types FOR EACH ROW BEGIN INSERT INTO reg (id_srv, serv, id_comp, dates, usr) VALUES (:old.id_srv, :old.add_cmp, :old.id_comp, sysdate, '|| usr ||'); END;';
    END dyna;
END;
/

BEGIN
    WorkTablePack.add_data;
    WorkPack.dyna('USER');
END;
/
SELECT * FROM add_cmp;
SELECT * FROM service_types;


BEGIN
    WorkPack.delete_service('add');
END;
/
SELECT * FROM reg;

CREATE OR REPLACE VIEW view_table AS
    SELECT add_cmp.id_add_comp, add_cmp.name_cmp, add_cmp.country, service_types.add_cmp
    FROM add_cmp, service_types
    WHERE add_cmp.id_add_comp = service_types.id_comp;
SELECT * FROM view_table;

GRANT SELECT ON view_table TO public;
-- GRANT EXECUTE ON WorkPack TO public;

-- BEGIN
--     WorkPack.dyna('OVIP');
-- END;
-- /
