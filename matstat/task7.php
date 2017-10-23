<?php
$x = [9, 12, 9, 22, 15, 15, 18,14, 23, 12];

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
$s = 0;
foreach($freq as $xi => $data)
{
    $m += $xi * $data['relfreq'];
}

foreach ($freq as $xi => $data)
{
    //$d = $xi * pow($xi - $m, 2) / count($x);
    $s += 1/count($x) * $data['count'] * (pow($xi - $m, 2));
}

print_r($m);
print_r(['d' => $d, 'de' => sqrt($d), 's' => $s]);
//ksort($freq2);
//print_r($freq2);
//print_r(['count' => count($x), 'grouped' => count($freq)]);
