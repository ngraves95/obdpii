<?php

$db = new mysqli("localhost", "obdii", "obdii", "mock");

if ($db->connect_errno) {
    echo "Connect failed: ".$db->connect_error;
    exit();
}

$target_pids = array();

if(isset($_GET["pid"]) && !empty($_GET["pid"])) {
    $target_pids = $_GET["pid"];
} else {
    echo "{}";
    exit();
}

//ERROR

// Validate pids. If any are not numeric, remove them.
// for ($i = 0; $i < count($target_pids); i++) {
//     if (!is_numeric($target_pids[i])) {
//         unset($target_pids[i]);
//     }
// }

//$target_pids = array_values($target_pids);

// END ERROR

// Get PID data from OBD-II. Data is passed via stdout.
$obdii_pid_param_string = join(" ", $target_pids);
$obdii_reader = "./main";
$obdii_raw = json_decode(utf8_encode(exec($obdii_reader." ".$obdii_pid_param_string)));

$obdii_data = array();
foreach ($obdii_raw as $key => $value) {
    $obdii_data[$key] = $value;
}

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
        "pid_value" => $obdii_data[$metadata_row["pid"]],
        "pid_units" => $metadata_row["units"]
    );
}

$db->close();
echo json_encode($output);

?>