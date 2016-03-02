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

$output = array();
while ($pid_row = $pid_result->fetch_assoc()) {
    $output[$pid_row["pid"]] = array("name" => $pid_row["name"],
                                     "units" => $pid_row["units"]);

}

echo json_encode($output);

?>