#!/usr/bin/awk -f

BEGIN{
    FS = ","
}

$2 == 6 {
    print $6 > "junio.csv"
}
$2 == 7 {
    print $6 > "julio.csv"
}
$2 == 8 {
    print $6 > "agosto.csv"
}
$2 == 9 {
    print $6 > "septiembre.csv"
}
# awk -f filtrado.awk villarrica.csv