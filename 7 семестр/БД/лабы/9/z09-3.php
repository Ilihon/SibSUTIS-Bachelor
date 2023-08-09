<?php
$user = 'root';
$passwd = '';
$conn = mysqli_connect('localhost', $user, $passwd);
if (!$conn) {
    echo 'Unable to connect to database';
    echo mysqli_error($conn);
}

$database = 'sample';
mysqli_select_db($conn, $database);

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
