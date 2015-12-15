<?php
$db = new mysqli("localhost", "obdii", "obdii", "mock");
if ($db->connect_errno) {
    echo "Connect failed: ".$db->connect_error;
    exit();
 }
$pid_query = "select pid, name, units from pid_metadata";
$pid_result = $db->query($pid_query);

if (!$pid_result) {
    $pid_result->close();
}
$output = "";
while ($pid_row = $pid_result->fetch_assoc()) {
     $output = $output.'<option value="'.$pid_row["pid"].'" label="'
             .$pid_row["name"].'">'.$pid_row["units"]."</option>";
}
?>

<!DOCTYPE html>
<html>
  <head>
    <title>OBDPII</title>
    <link rel="stylesheet" type="text/css" href="./dashboard.css" />
    <meta content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=0" name="viewport" />
    <script src="./dashboard.js"></script>
  </head>
  <body onload="update()" ontouchstart="">
    <div class="add-button" onclick="togglePidSelector()">+</div>
    <select id="pidsel" class="pid-selector" name="pids"
	      onchange="registerPid()" >
                <option value=""> -- Please select a PID -- </option>
    <?php echo $output ?>
    </select>
    <div id="content">
      <div id="content-inner">
	<ul id="content-list"></ul>
      </div>

    </div>
  </body>
</html>
