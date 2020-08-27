<?php
// MySQL Baglan
include(‘mysql.php’);
?>
<html>
<head>
<title>SASTEC 1 VERİ YÖNETİM MERKEZİ</title>
<style type=”text/css”>
.table_titles, .table_cells_odd, .table_cells_even {
padding-right: 20px;
padding-left: 20px;
color: #000;
}
.table_titles {
color: #FFF;
background-color: #666;
}
.table_cells_odd {
background-color: #CCC;
}
.table_cells_even {
background-color: #FAFAFA;
}
table {
border: 2px solid #333;
}
body { font-family: “Trebuchet MS”, Arial; }
</style>
</head>
<body>
<h1>SASTEC 1 PARAMETRELER</h1>
<table border=”0″ cellspacing=”0″ cellpadding=”4″>
<tr>
<td class=”table_titles”>ID</td>
<td class=”table_titles”>Tarih-Saat</td>
<td class=”table_titles”>Sensor</td>
<td class=”table_titles”>Sicaklik</td>
</tr>
<?php
// Kayitlari veritabanindan oku
$result = mysql_query(“SELECT * FROM temperature ORDER BY id ASC”);
// Satir renk gecisi
$oddrow = true;
// tum kayitlari isle
while( $row = mysql_fetch_array($result) )
{
if ($oddrow)
{
$css_class=’ class=”table_cells_odd”‘;
}
else
{
$css_class=’ class=”table_cells_even”‘;
}
$oddrow = !$oddrow;
echo ‘<tr>’;
echo ‘   <td’.$css_class.’>’.$row[“id”].'</td>’;
echo ‘   <td’.$css_class.’>’.$row[“event”].'</td>’;
echo ‘   <td’.$css_class.’>’.$row[“sensor”].'</td>’;
echo ‘   <td’.$css_class.’>’.$row[“celsius”].'</td>’;
echo ‘</tr>’;
}
?>
</table>
</body>
</html>

//// GOKTUGUNVER SIMURG AVIATION & SPACE TEC 
