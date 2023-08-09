<?php
$user = "root";
$password = "";
$database = "sample";

$conn = mysqli_connect('localhost', $user, $password);
if (!$conn) {
    echo 'Unable to connect to database';
    echo mysqli_error($conn);
}

mysqli_select_db($conn, $database);
printf("Успешно: %s</br>", $conn->host_info);

$query = "drop table if exists t4";
$result = mysqli_query($conn, $query);
print("$result");

$query = "
create table t4
(id int auto_increment, command varchar(15) NOT NULL, commtype varchar(15) NOT NULL, PRIMARY KEY (id));
INSERT INTO t4 (command, commtype)   VALUES ('ALTER SESSION', 'Управления');
INSERT INTO t4 (command, commtype)   VALUES ('ALTER SESSION', 'Управления');
INSERT INTO t4 (command, commtype)   VALUES ('COMMIT', 'Управления');
INSERT INTO t4 (command, commtype)   VALUES ('ROLLBACK', 'Управления');
INSERT INTO t4 (command, commtype)   VALUES ('DELETE', 'DML');
INSERT INTO t4 (command, commtype)   VALUES ('INSERT', 'DML');
INSERT INTO t4 (command, commtype)   VALUES ('SELECT', 'DML');
INSERT INTO t4 (command, commtype)   VALUES ('UPDATE', 'DML');
INSERT INTO t4 (command, commtype)   VALUES ('ALTER ROLE', 'DDL');
INSERT INTO t4 (command, commtype)   VALUES ('ALTER VIEW', 'DDL');
INSERT INTO t4 (command, commtype)   VALUES ('CREATE ROLE', 'DDL');
INSERT INTO t4 (command, commtype)   VALUES ('CREATE TABLE', 'DDL');
INSERT INTO t4 (command, commtype)   VALUES ('DROP', 'DDL');
INSERT INTO t4 (command, commtype)   VALUES ('GRANT', 'DDL');
INSERT INTO t4 (command, commtype)   VALUES ('REVOK', 'DDL');
INSERT INTO t4 (command, commtype)   VALUES ('TRUNCATE', 'DDL');
";
$result = mysqli_multi_query($conn, $query);
print("$result");
?>
