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
$id = null;
$value = null;

parse_arg('column_name', $name);
parse_arg('id', $id);
parse_arg('column_value', $value);

fatal_if_null($name);
fatal_if_null($id);
fatal_if_null($value);
echo "${id}, ${name}, ${value}";

$user = 'root';
$passwd = '';
$conn = mysqli_connect('localhost', $user, $passwd);
if (!$conn) {
    echo 'Unable to connect to database';
    echo mysqli_error($conn);
}

$database = 'sample';
mysqli_select_db($conn, $database);

$query = "update notebook01 set $name = '$value' where id = '$id'";
$result = mysqli_query($conn, $query);
echo "${result}<br/>";
