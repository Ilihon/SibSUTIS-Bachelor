<?php

function vid_structure($conn, $table)
{
    print "<h4>Структура таблицы $table</h4>";
    $mysql_data_type_hash = array(
        1 => 'tinyint',
        2 => 'smallint',
        3 => 'int',
        4 => 'float',
        5 => 'double',
        7 => 'timestamp',
        8 => 'bigint',
        9 => 'mediumint',
        10 => 'date',
        11 => 'time',
        12 => 'datetime',
        13 => 'year',
        16 => 'bit',
        252 => 'text',
        253 => 'varchar',
        254 => 'char',
        246 => 'decimal'
    );
    $mysql_data_type_flag = array(
        1 => 'NOT_NULL_FLAG',
        2 => 'PRI_KEY_FLAG',
        4 => 'UNIQUE_KEY_FLAG',
        16 => 'BLOB_FLAG',
        32 => 'UNSIGNED_FLAG',
        64 => 'ZEROFILL_FLAG',
        128 => 'BINARY_FLAG',
        256 => 'ENUM_FLAG',
        512 => 'AUTO_INCREMENT_FLAG',
        1024 => 'TIMESTAMP_FLAG',
        2048 => 'SET_FLAG',
        32768 => 'NUM_FLAG',
        16384 => 'PART_KEY_FLAG',
        32768 => 'GROUP_FLAG',
        65536 => 'UNIQUE_FLAG'
    );

    $query = "describe $table";
    $result = mysqli_query($conn, $query);
    $num_fields = mysqli_num_fields($result);
    for ($x=0; $x<$num_fields; $x++) {
        $properties = mysqli_fetch_field_direct($result, $x);
        $flag = $properties->flags;
        print $mysql_data_type_hash[$properties->type]." ". ($properties->length). " ".($properties->name)." ";
        foreach($mysql_data_type_flag as $key => $value){
            if($key & $flag){
                print  $mysql_data_type_flag[$key]." ";
            }
        }
        print "</br>";
    }

//    if (mysqli_num_rows($result) > 0) {
//        while ($row = mysqli_fetch_assoc($result)) {
//            print $row['Field'] . " " . $row['Type'] . " " . $row['Null'] . " NULL " . $row['Key'] . " " . $row['Default'] . " " . $row['Extra'] . "</br>";
//
//
//        }
//    }
}

function vid_content($conn, $table)
{
    print "<h4>Содержимое таблицы $table</h4>";

    $tabname = array(
        "cnum" => "номер покупателя",
        "cname" => "имя покупателя",
        "city" => "город",
        "rating" => "рейтинг покупателя",
        "snum" => "номер продавца",
        "onum" => "номер заказа",
        "amt" => "стоимость заказа",
        "odate" => "дата заказа",
        "sname" => "имя продавца",
        "comm" => "комиссионные"
    );
    $query = "select * from $table";
    $result = mysqli_query($conn, $query);
    $num_fields = mysqli_num_fields($result);
    print "<table border=\"1\" cellpadding=\"5\" cellspacing=\"1\">\n";
    print "<tr>\n";
    for ($x = 0; $x < $num_fields; $x++) {
        $name = mysqli_fetch_field_direct($result, $x)->name;
        print "\t<th>$tabname[$name]</br>$name</th>\n";
    }
    print "</tr>\n";
    while ($a_row = mysqli_fetch_row($result)) {
        print "<tr style='padding:5px 10px'>\n";
        foreach ($a_row as $field)
            print "\t<td>$field</td>\n";
        print "</tr>\n";
    }
    print "</table>\n";
}


if (isset($_POST['cust'])) {
    $cust = $_POST['cust'];
    if (isset($cust[0])) {
        vid_structure($conn, 'cust');
    }
    if (isset($cust[1])) {
        vid_content($conn, 'cust');
    }

}

if (isset($_POST['ord'])) {
    $cust = $_POST['ord'];
    if (isset($cust[0])) {
        vid_structure($conn, 'ord');
    }
    if (isset($cust[1])) {
        vid_content($conn, 'ord');
    }

}

if (isset($_POST['sal'])) {
    $cust = $_POST['sal'];
    if (isset($cust[0])) {
        vid_structure($conn, 'sal');
    }
    if (isset($cust[1])) {
        vid_content($conn, 'sal');
    }

}
echo "<form action='z10-1.html'>
         </br>
        <input type='submit' value='Вернуться на выбор таблицы'/>
      </form>"
?>