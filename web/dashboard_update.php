<?php

$db = new mysqli("localhost", "obdii", "obdii", "mock");

if ($db->connect_errno) {
    echo "Connect failed: ".$db->connect_error;
    exit();
}

// How to get target pids? Maybe send via json?
$target_pids = array(17, 12, 13, 15); // 0x17 is Throttle Position.

// Get names and units from pid_metadata table.
$where_clause = join(",", $target_pids);
$metadata_query = "select pid, name, units from pid_metadata where pid in "
                ."(".$where_clause.")";
$metadata_result = $db->query($metadata_query);

// Get values from <DATA TABLE> table.


// Set up output format

$output = array();

if (!$metadata_result) {
    $metadata_result->close();
}

while ($metadata_row = $metadata_result->fetch_assoc()) {
    $output[$metadata_row["name"]] = array(
        "pid_value" => 0,//$obdii_row[$metadata_row["pid"]];
        "pid_units" => $metadata_row["units"]
    );
}

echo json_encode($output);

?>