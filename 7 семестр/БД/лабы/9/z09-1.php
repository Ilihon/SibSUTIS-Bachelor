<html lang="en">
<head>
    <title>Task 1</title>
    <meta charset="UTF-8"
</head>
<body>
<h1>Задание не задалось</h1>
<p>
    <?php
    ini_set('display_errors', 1);
    ini_set('display_startup_errors', 1);
    error_reporting(E_ALL);

    $user = 'root';
    $passwd = '';
    $conn = mysqli_connect('localhost', $user, $passwd);
    if (!$conn) {
        echo 'Unable to connect to database';
        echo mysqli_error($conn);
    }

    $database = 'sample';
    mysqli_select_db($conn, $database);

    $result = mysqli_query($conn, 'drop table if exists notebook01;');
    echo "${result}<br/>";

    $result = mysqli_query($conn, '
        create table notebook01
        (
            id       int auto_increment,
            name     varchar(50) null,
            city     varchar(50) null,
            address  varchar(50) null,
            birthday date        null,
            mail     varchar(20) null,
            constraint notebook01_pk
                primary key (id)
        );');
    echo "${result}<br/>";

    ?>
</p>
</body>
</html>
