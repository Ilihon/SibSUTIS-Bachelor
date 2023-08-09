<?php
$color = 'green';
$size = "22";
$var1 = 'Alice';
$var2 = "My friend is $var1<br/>";
echo $var2;
$var3 = 'My friend is $var1<br/>';
echo $var3;
$var4 = &$var1;
echo "$var4<br/>";
$var1 = 'Bob';
$var2 = "My friend is $var1<br/>";
echo $var2;
$var3 = 'My friend is $var1<br/>';
echo $var3;
echo "$var4<br/>";
$user = "Michael";
$$user = "Jackson";
echo "$Michael <br/>";
$p = 3.141592;
echo "Pi number is $p<br/>";
echo gettype($p);
$p1 = (boolean) $p;
$p2 = (integer) $p;
echo "<br/>temporary bool $p1 <br/>";
echo "temporary int $p2";
settype($p, "string");
echo "<br/>string $p <br/>";
echo gettype($p);
settype($p, "integer");
echo "<br/>int $p <br/>";
echo gettype($p);
settype($p, "boolean");
echo "<br/>bool $p <br/>";
echo gettype($p);
?>

<html>
<head>
</head>
<body>
  <h1
  <?php echo "style='color: ${color}'"; ?>
  >TEXT</h1>
  <p><<?php echo "font size=${size}"; ?>> Size </p>
</body>
</html>