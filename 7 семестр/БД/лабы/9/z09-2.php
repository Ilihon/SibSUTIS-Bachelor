<?php

function parse_arg($name, &$var)
{
    if (isset($_POST[$name]) && $_POST[$name] != '') {
        $var = $_POST[$name];
    }
}

function fatal_if_null($var)
{
    if (is_null($var)) {
        echo "<h3 style='color: coral'>Error, some parameters are missing. Try again.</h3>";
        exit(1);
    }
}

$name = null;
$city = '';
$address = '';
$birthday = null;
$mail = null;

parse_arg('name', $name);
parse_arg('city', $city);
parse_arg('address', $address);
parse_arg('birthday', $birthday);
parse_arg('mail', $mail);

fatal_if_null($name);
fatal_if_null($birthday);
fatal_if_null($mail);

$user = 'root';
$passwd = '';
$conn = mysqli_connect('localhost', $user, $passwd);
if (!$conn) {
    echo 'Unable to connect to database';
    echo mysqli_error($conn);
}

$database = 'sample';
mysqli_select_db($conn, $database);

$query = "insert into notebook01(name, city, address, birthday, mail)
        VALUES ('$name', '$city', '$address', '$birthday', '$mail');";
$result = mysqli_query($conn, $query);
echo "${result}<br/>";

$query = "select * from notebook01;";
$result = mysqli_query($conn, $query);
if (mysqli_num_rows($result) > 0) {
    while ($row = mysqli_fetch_assoc($result)) {
        echo "<p>
                id: ${row['id']}<br/>
                name: ${row['name']}<br/>
                city: ${row['city']}<br/>
                address: ${row['address']}<br/>
                birthday: ${row['birthday']}<br/>
                mail: ${row['mail']}<br/>
              </p>";
    }
}