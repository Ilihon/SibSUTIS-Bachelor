<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Title</title>
</head>
<body>
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
                <div class='block'>
                    <table>
                        <tr>
                        <td>Id</td><td>${row['id']}</td>
                        </tr>
                        <tr>
                        <td>name</td><td>${row['name']}</td>
                        </tr>
                        <tr>
                        <td>city</td><td>${row['city']}</td>
                        </tr>
                        <tr>
                        <td>address</td><td>${row['address']}</td>
                        </tr>
                        <tr>
                        <td>birthday</td><td>${row['birthday']}</td>
                        </tr>
                        <tr>
                        <td>mail</td><td>${row['mail']}</td>
                        </tr>
                    </table>
                    <form action='task4.php' method='post'>
                        <input type='hidden' name='id' value='${row['id']}'>
                        <select name='column_name'>
                            <option value='name'>name</option>
                            <option value='address'>address</option>
                            <option value='birthday'>birthday</option>
                            <option value='mail'>mail</option>
                        </select>
                        <input type='text' name='column_value'/>
                        <input type='submit' value='Отправить'/>
                    </form> 
                </div>
              </p>";
    }
}
?>
</body>
</html>
