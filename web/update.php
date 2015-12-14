<?php

$json = '{'.
      '"pid_list" : ['.
          '{ "pid_name":"Some PID 1", "pid_value":104, "pid_units":"kPa" }'.
          '{ "pid_name":"Some PID 2", "pid_value":72, "pid_units":"%" }'.
          '{ "pid_name":"Some PID 3", "pid_value":14, "pid_units":"oC" }'.
          '{ "pid_name":"Some PID 4", "pid_value":0.123, "pid_units":"mm" }'.
      '] }';
echo $json;

?>