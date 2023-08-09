<?php
$user = "root";
$password = "";
$database = "sample";


$conn = mysqli_connect('localhost', $user, $password, $database);
if (!$conn) {
    echo 'Unable to connect to database';
    echo mysqli_error($conn);
}
?>