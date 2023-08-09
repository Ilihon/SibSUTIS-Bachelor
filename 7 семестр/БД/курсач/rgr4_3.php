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

if(isset($_GET['column'])){
    $comm = $_GET['column'];
}

$query = "select $comm from t4";
$result = mysqli_query($conn, $query);
$num_fields = mysqli_num_fields($result);
print "<table border=\"1\" cellpadding=\"5\" cellspacing=\"1\">\n";
print "<tr>\n";
for ($x = 0; $x < $num_fields; $x++) {
    $name = mysqli_fetch_field_direct($result, $x)->name;
    print "\t<th>$name</th>\n";
}
print "</tr>\n";
while ($a_row = mysqli_fetch_row($result)) {
    print "<tr style='padding:5px 10px'>\n";
    foreach ($a_row as $field)
        print "\t<td>$field</td>\n";
    print "</tr>\n";
}
print "</table>\n";