<?php
$MyUsername = “kullaniciadiniz”;  // 
$MyPassword = “parolaniz”;  // 
$MyHostname = “localhost”;      // 
$dbh = mysql_pconnect($MyHostname , $MyUsername, $MyPassword);
$selected = mysql_select_db(“test”,$dbh);
?>
