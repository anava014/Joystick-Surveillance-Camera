<?php
        $position = $_GET["position"];
        $fp = fopen('request.txt', 'w');
        fwrite($fp, $position);
        fclose($fp);
        echo $position
?>

