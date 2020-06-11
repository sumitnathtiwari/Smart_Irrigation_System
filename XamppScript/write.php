<?php
$servername = "localhost";
$database = "smart_irrigation_1";
$username = "sumit";
$password = "senti143";

// Create connection

$conn = mysqli_connect($servername, $username, $password, $database);

// Check connection

if (!$conn) {

    die("Connection failed: " . mysqli_connect_error());

}
//http://localhost:8081/smart1/write.php?ph_value=174&rain=yes&temp=100&humidity=15&pressure=782&moisture=45&greenness=124&red=300&blue=160&ir=1&ldr=712
$sql = "INSERT INTO data (ph_value,rain,temp,humidity,pressure,moisture,greenness,red,blue,ir,ldr) VALUES ('".$_GET["ph_value"]."','".$_GET["rain"]."','".$_GET["temp"]."','".$_GET["humidity"]."','".$_GET["pressure"]."','".$_GET["moisture"]."','".$_GET["greenness"]."','".$_GET["red"]."','".$_GET["blue"]."','".$_GET["ir"]."','".$_GET["ldr"]."')";
//if (isset($_POST)) {
//$ph_value=$_POST['ph_value'];
//$rain=$_POST['rain'];
//$temp=$_POST['temp'];
//$humid=$_POST['humid'];
//$sql = "INSERT INTO data (ph_value,rain,temp,humid) VALUES ('$ph_value','$rain','$temp','$humid')";    
if (mysqli_query($conn, $sql)) {
      echo "New record created successfully";
} else {
      echo "Error: " . $sql . "<br>" . mysqli_error($conn);
}
//}
//else{
	//echo "NO POST COMMAND";
//}
mysqli_close($conn);
?>