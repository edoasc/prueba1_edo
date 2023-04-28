Ejecutar el script pregunta_2.awk con la siguiente linea de comando en bash

cat villarrica.csv | awk -f pregunta_2.awk

Creamos 4 archivos .csv que contengan la data de los meses de junio, julio, agosto y septiembre respectivamente ejecutando el siguiente comando en bash

awk -f filtrado.awk villarrica.csv

Para generar los histograma ejecutamos la siguiente secuenta en gnuplot para cada uno de los meses

set terminal png
set output 'junio.png'
set xrange[0:30]
plot 'junio.csv' with histogram title "Concentraciones de SO2 para Junio" fillcolor rgb "red"

Reemplazar para cada mes los nombres correspondientes
