#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Se define el puntero f_potencial cuyos argumentos son posiciones (array multidimensional) y suma de potenciales (puntero).
typedef void (*f_potencial)(double **, double *);

// Función externa que retorna la suma de los potenciales de cada par de partículas para una instancia del tipo Estructura.
// recibe las posiciones (x,y,z) y el puntero a la variable de salida sumaPotencial.
void potencial(double **posiciones, double *sumaPotencial){
    double suma = 0;
    for (int i = 0; i < 8; i++){
        for (int j = i+1; j < 8; j++){
            double dx = posiciones[0][i] - posiciones[0][j];
            double dy = posiciones[1][i] - posiciones[1][j];
            double dz = posiciones[2][i] - posiciones[2][j];
            double r = sqrt(dx*dx + dy*dy + dz*dz);
            double potencial = 4*(pow(1.0/r,12) - pow(1.0/r,6));
            suma += potencial;
        }
    }
    // Se le entrega el cálculo al puntero alojado en la estructura, de forma de poder llamar dicho atributo a través de la instancia creada.
    *sumaPotencial = suma; 
}

// La estructura consta de 3 atributos
struct Estructura{
    f_potencial calculo;
    double **posiciones;
    double sumaPotencial;
};

// La función init inicializa una variable del tipo Estructuca con sus respectivos atributos. las entradas
// corresponden a un puntero *puntero referido a la estructura de Estructura y la función externa que se
// desea utilizar (en este caso potencial).
void init(struct Estructura *puntero, f_potencial funcion){
    puntero->calculo = funcion;
    puntero->sumaPotencial = 0;
    // Se asigna memoria de forma dinámica para 3 elementos de tamaño (double *), esto es, punteros que apuntan hacia un valor double.
    puntero->posiciones = malloc(3 * sizeof(double *));
    // Para cada puntero se asigna memoria para un valor individual double, creando así el array multidimensional.
    for (int i = 0; i < 3; i++){
        puntero->posiciones[i] = malloc(8 * sizeof(double));
    }  
    // Matriz de 3x8 que almacena las posiciones (x,y,z) de cada partícula.
    int asignacion[3][8] = {{0,0,0,0,1,1,1,1},
                            {0,0,1,1,0,0,1,1},
                            {0,1,0,1,0,1,0,1}};
    // Se asigna al array posiciones los valores de la matriz asignacion.
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 8; j++) {
            puntero->posiciones[i][j] = asignacion[i][j];
        }
    }
}

// La función calculos recibe un puntero *puntero y, a través del mismo, ingresa al atributo calculo (el cual deriva en la función externa 'funcion'
// entregada previamente en la función init) y le entrega los argumentos necesarios alojados en los atributos correspondientes. Notar que se entrega la 
// dirección de memoria de sumaPotencial, mas no su valores, esto debido a que la función externa potencial recibe como
// argumento el puntero de esa variable para poder modificar su valor. 
void calculos(struct Estructura *puntero){
    puntero->calculo(puntero->posiciones, &(puntero->sumaPotencial));
}

// Creamos una instancia de la estructura 'Estructura' llamada 'cubo' y un puntero '*puntero_cubo' asignado a la dirección de la instancia.
// Inicializamos la funcion init entregando el puntero y la funcion potencial, realizamos los calculos y finalmente se imprime
// la energía potencial total del sistema accediendo al atributo sumaPotencial con la sintaxis cubo.sumaPotencial.
int main(){
    struct Estructura cubo;
    struct Estructura *puntero_cubo = &cubo;
    init(puntero_cubo, potencial);
    calculos(puntero_cubo);
    printf("Energía potencial del sistema: %lf\n", cubo.sumaPotencial);
}

// Ejecutar el siguiente comando para compilar:

// gcc pregunta_3.c -o testeo -lm

// Ejecutar el siguiente comando para revisar las salidas:

// ./testeo