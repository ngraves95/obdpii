<?php

$ja = array(
    "Some PID 1" => array(
        "pid_value" => 104,
        "pid_units" => "kPa"
    ),
    "Some PID 2" => array(
        "pid_value" => 72.2,
        "pid_units" => "%"
    ),
    "Time" => array(
        "pid_value" => date('i:s'),
        "pid_units" => "time"
    )
);

echo json_encode($ja);

?>