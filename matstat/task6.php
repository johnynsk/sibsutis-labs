<?php
$values = "66 83 64 55 75 65 67 54 70 44 51 86 67 58 73 71 46 86 68 79 50 58 66 69 61 64 78 78 60 46 71 71 74 79 65 61 62 84 53 67 49 54 63 60 57 70 52 74 65 61";
$x = explode(" ", $values);

$freq=[];
$freq2 = [];
$m = 0;
foreach ($x as $xi) {
    if (!isset($freq[$xi])) {
        $freq[$xi] = ['count' => 0, 'relfreq' => 0];
    }

    $seq = (int)(($xi-45)/6);

    if (!isset($freq2[$seq])) {
        $freq2[$seq] = ['count' => 0, 'relfreq' => 0];
    }

    $freq[$xi]['count']++;
    $freq[$xi]['relfreq'] = $freq[$xi]['count'] / count($x);
//    $freq2[$seq]['count']++;
//    $freq2[$seq]['relfreq'] = $freq2[$seq]['count'] / 6;
//    $freq2[$seq]['grouped'][$xi] = 1;
}
$d = 0;
foreach($freq as $xi => $data)
{
    $m += $xi * $data['relfreq'];
}

foreach ($freq as $xi => $data)
{
    $d = $xi * pow($xi - $m, 2) / count($x);
}

print_r($m);
print_r(['d' => $d, 'de' => sqrt($d)]);
ksort($freq);
foreach($freq as $key=>$value) {
    echo " " . $value['count'].";";
}
echo "\n";
print_r(implode(";", array_keys($freq)));
//ksort($freq2);
//print_r($freq2);
//print_r(['count' => count($x), 'grouped' => count($freq)]);
