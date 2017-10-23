<?php
$p = 0.2;
$q = 0.8;
$n = 10;
$cnk = function($n, $k)  {
    return gmp_strval(gmp_fact($n)) / (gmp_strval(gmp_fact($k)) * gmp_strval(gmp_fact($n - $k)));
};
$x = [];
$sum = 0;
$m = 0;
for( $i = 0; $i <= $n; $i++) {
    $x[$i] = $cnk($n, $i) * pow($p, $i) * pow($q, $n-$i);
    $sum += $x[$i];
    $m += $x[$i] * $i;
}

//print_r($x);
//print_r($m);
$d = 0;
foreach ($x as $i=>$xi) {
    $d += $xi * pow($xi - $m,2);
}

print_r(sqrt($d));
