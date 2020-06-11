<?php
    // Connect to database
$servername = "localhost";
$database = "smart_irrigation_1";
$username = "sumit";
$password = "senti143";
   // IMPORTANT: If you are using XAMPP you will have to enter your computer IP address here, if you are using webpage enter webpage address (ie. "www.yourwebpage.com")
    $con = mysqli_connect($servername, $username, $password, $database);
       
    // Retrieve all records and display them   
    $result = mysqli_query($con,'SELECT waterhrs FROM data ORDER BY id DESC LIMIT 1');
      
    // Process every record
    
    while($row = mysqli_fetch_array($result))
    {      
        echo  . $row['waterhrs'] .; 
    }
        
    // Close the connection   
    mysqli_close($con);
?>