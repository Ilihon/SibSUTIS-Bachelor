<html> <head>
    <title> Result </title>
</head>
<body>
<?php

$align = $_GET["align"];
$valign = $_GET["valign"];

print "<p><table style='border: 3px solid black; width: 300px; height: 300px'>\n";
print "<tr><td style='text-align: ${align}; vertical-align: ${valign}'>Hello!</td></tr></table>\n";

print "<p><a href='8-1a.html'>Назад</a>";
?>
</body>
</html>