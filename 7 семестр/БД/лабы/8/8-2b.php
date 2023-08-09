<html>
<head>
    <title> Result </title>
</head>
<body>
<?php

$username = $_POST["username"];
$answers = $_POST["answers"];
$right_answers_count = 0;
$right_answers = ["0", "1", "2", "0", "1"];

for ($i = 0; $i < count($right_answers); $i++) {
    if ($answers[$i] === $right_answers[$i]) {
        $right_answers_count = $right_answers_count + 1;
    }
}

print "$username, your result: ";

switch ($right_answers_count) {
    case "0":
        print "0. It's so bad!";
        break;
    case "1":
        print "1. It's bad!";
        break;
    case "2":
        print "2. Bag grade!";
        break;
    case "3":
        print "3. It's normal!";
        break;
    case "4":
        print "4. You're good!";
        break;
    case "5":
        print "5. Excellent!";
        break;
}

print "<br><br><a href='8-2a.html'>Назад</a>";
?>
</body>
</html>