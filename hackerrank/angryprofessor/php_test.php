<?php

$counter = 0;
$num_testcases = 0;
$all_students_count = 0; 
$required_students = 0;

while($f = fgets(STDIN)) {
    if(strlen($f) > 0) {
        if ($counter == 0) {
            $num_testcases = intval($f);    
        } else {
            if (($counter % 2) == 1) {
                // the n & k line
                $nk_array = explode(" ", $f);
                $all_students_count = $nk_array[0];
                $required_students = $nk_array[1];
            } else if (($counter % 2) == 0) {
                // the students time in line
                $timein_array = explode(" ", $f); 
                $latecomers = 0;
                foreach ($timein_array as $timein) {
                    $in = intval($timein);
                    if($in < 1) {
                        $latecomers++; 
                    } 
                }
                if($latecomers >= $required_students) {
                    printf("NO\n");
                } else {
                    printf("YES\n");
                }
            }
        }   

        $counter++;
    }
}

?>
