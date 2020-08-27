<?php
// MySQL baglan
include(“mysql.php”);
// get ile veri alan Sql kodu
$SQL = “INSERT INTO test.temperature (sensor ,celsius) VALUES (‘”.$_GET[“serial”].”‘, ‘”.$_GET[“temperature”].”‘)”;
// Sql kodunu calistir
mysql_query($SQL);
?>
