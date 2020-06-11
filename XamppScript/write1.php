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
//http://localhost:8081/smart1/write1.php?temperature=174&humidity=52&Pressure=558
$sql = "INSERT INTO data2 (temperature,humidity,Pressure) VALUES ('".$_GET["temperature"]."','".$_GET["humidity"]."','".$_GET["Pressure"]."')";
//if (isset($_POST)) {
//$Green=$_POST['Green'];
//$ir_alert=$_POST['ir_alert'];
//$moisture=$_POST['moisture'];
//$sql = "INSERT INTO data (Green,ir_alert,moisture) VALUES ('$Green','$ir_alert','$moisture')";    
if (mysqli_query($conn, $sql)) {
      echo "New record created successfully";
} else {
      echo "Error: " . $sql . "<br>" . mysqli_error($conn);
//}
}
//else{
	//echo "NO POST COMMAND";
//}
mysqli_close($conn);
?>