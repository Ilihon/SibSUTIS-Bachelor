<!-- <?php
$color = 'green';
$size = "22";
$var1 = 'Alice';
$var4 = &$var1;
$var2 = "My friend is $var1<br/>";
echo $var2;
$var3 = 'My friend is $var1<br/>';
echo $var3;
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
$p1 = (boolean) $p;
$p2 = (integer) $p;
echo "Pi number is $p<br/>";
echo gettype($p);
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
?> -->

<html>
<head>
</head>
<body>
  <?php
  if (isset($_GET['lang'])) {
    $lang = $_GET['lang'];
  }
  if ($lang == "ru") {
    print "Russke";
  }
  elseif ($lang == "en") {
    print "Angleske";
  }
  elseif ($lang == "fr") {
    print "Franzuoske";
  }
  elseif ($lang == "de") {
    print "Nemezke";
  }
  else {
    print "Ce cho za $lang";
  }
  if (isset($_GET['num'])) {
    $num = $_GET['num'];
  }
  if (is_numeric($num)) {
    $num = str_split($num);
  }
  else{
    echo "<br/>This is not a number!<br/>";
  }
  $len = count($num);
  if ($len > 5){
    print "Number is too big!";
  }
  echo "<br/>";
  switch ($len) {
    case 5:
      $res = $num[0] * $num[1] * $num[2] * $num[3] * $num[4];
      print "$res";
      break;
    case 4:
      $res = $num[0] * $num[1] * $num[2] * $num[3];
      print "$res";
      break;
    case 3:
        $res = $num[0] * $num[1] * $num[2];
        print "$res";
        break;
    case 2:
      $res = $num[0] * $num[1];
      print "$res";
      break;
    case 1:
        $res = $num[0];
        print "$res";
        break;
    default:
      print "Dich kakayato";
      break;
  }
  if (isset($_GET['color'])) {
    $color = $_GET['color'];
  }
  print "<table border=1 cellpadding=5 style='border: 10px' bgcolor='white'>\n";
  for ($y=1; $y <= 10; $y++) {
      print "<tr>\n";
      for ($x=1; $x <= 10; $x++) {
        if ($y==1 or $x ==1){
          print "\t<td bgcolor = '$color'>";
          print "<p><font color = 'green'> $x*$y </p>";
        }
        else{
          print "\t<td>";
          print "<p> $x*$y </p>";
        }
        print "</td>\n";
      }
      print "</tr>\n";
    }
  print "</table>";
  $size = 70;
  $array = array("ponedelnik", "vtornik", "creda", "chetverg", "pyatniza", "sybbota", "voskresenie");
  $colorr = array("red", "green", "grey", "yellow", "black", "pink", "blue");
  for ($y=1; $y <= 7; $y++) {
    WeekDay($array[$y-1], $colorr[$y-1]);
    $size -= 10;
  }
  function WeekDay($day, $colrr) {
    global $size;
      print "<p style='font-size: {$size}px'><font color=$colrr>$day</font></p>";
  }

   ?>
</body>
</html>
