#!/usr/bin/awk -f

BEGIN{
    FS = ","
}
(NR>1){
    sum_VT += $4
    sum_magnitud += $5
    sum_SO2 += $6
    sum_altura += $7
    cont = 0
    for (i=1; i<=NR; i++){
        cont++
    }

    mean_VT = sum_VT/cont
    mean_magnitud = sum_magnitud/cont
    mean_SO2 = sum_SO2/cont
    mean_altura = sum_altura/cont

    diff_VT = $4 - mean_VT
    diff_magnitud = $5 - mean_magnitud
    diff_SO2 = $6 - mean_SO2
    diff_altura = $7 - mean_altura

    sum_diff_VT += diff_VT^2
    sum_diff_magnitud += diff_magnitud^2
    sum_diff_SO2 += diff_SO2^2
    sum_diff_altura += diff_altura^2

    sd_VT = sqrt(sum_diff_VT/(cont-1))
    sd_magnitud = sqrt(sum_diff_magnitud/(cont-1))
    sd_SO2 = sqrt(sum_diff_SO2/(cont-1))
    sd_altura = sqrt(sum_diff_altura/(cont-1))

    if ($2 >= 1 && $2 <= 4){
        sumVT += $4
        sumMagnitud += $5
        sumSO2 += $6
        sumAltura += $7
        cont2++
    }

    meanVT = sumVT/cont2
    meanMagnitud = sumMagnitud/cont2
    meanSO2 = sumSO2/cont2
    meanAltura = sumAltura/cont2

    if ($2 >= 1 && $2 <= 4){
        diffVT = $4 - meanVT
        diffMagnitud = $5 - meanMagnitud
        diffSO2 = $6 - meanSO2
        diffAltura = $7 - meanAltura
    }

    sum_diffVT += diffVT^2
    sum_diffMagnitud += diffMagnitud^2
    sum_diffSO2 += diffSO2^2
    sum_diffAltura += diffAltura^2

    sdVT = sqrt(sum_diffVT/(cont-1))
    sdMagnitud = sqrt(sum_diffMagnitud/(cont-1))
    sdSO2 = sqrt(sum_diffSO2/(cont-1))
    sdAltura = sqrt(sum_diffAltura/(cont-1))

}
END{
    print "LOS SIGUIENTES DATOS SON PARA TODOS LOS ELEMENTOS DE LA TABLA \n"
    print "Total de sismos volcanotectónicos:", sum_VT
    print "Promedio de sismos volcanotectónicos diarios:", sum_VT/cont
    print "Desviación estándar de sismos volcanotectónicos diarios:", sd_VT
    print "Promedio de las magnitudes:", sum_magnitud/cont
    print "Desviación estándar de las magnitudes:", sd_magnitud
    print "Promedio de SO2:", sum_SO2/cont
    print "Desviación estándar de SO2:", sd_SO2
    print "promedio de altura:", sum_altura/cont
    print "Desviación estándar de las alturas:", sd_altura
    print "-------------------------------------------------------------------"
    print "LOS SIGUIENTES DATOS SON PARA LOS MESES DE ENERO, FEBRERO, MARZO Y ABRIL \n"
    print "Total de sismos volcanotectónicos:", sumVT
    print "Promedio de sismos volcanotectónicos diarios:", sumVT/cont2
    print "Desviación estándar de sismos volcanotectónicos diarios:", sdVT
    print "Promedio de las magnitudes:", sumMagnitud/cont2
    print "Desviación estándar de las magnitudes:", sdMagnitud
    print "Promedio de SO2:", sumSO2/cont2
    print "Desviación estándar de SO2:", sdSO2
    print "promedio de altura:", sumAltura/cont2
    print "Desviación estándar de las alturas:", sdAltura
}