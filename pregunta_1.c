#include <stdio.h>
#include <stdlib.h>

int main() {

    // Se inicializan los valores de k y W como enteros y el vector solución x que se rellena con ceros.
    int k[] = {1, 2, 1, 1, 2};
    int W[] = {2, 1, 2}; 
    double x[] = {0, 0, 0};

    // Se genera la matriz A para luego resolver el problema W=Ax.
    double A[3][3] = {{k[0]+k[1]+k[2]+k[4], -k[2], -k[4]},
                      {-k[2], k[2]+k[3], -k[3]},
                      {-k[4], -k[3], k[3]+k[4]}};

    // Se genera la matríz aumentada combinando la matriz A con la matriz identidad I.
    double B[3][6];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            B[i][j] = A[i][j];
        }
        for (int j = 3; j < 6; j++) {
            if (j == i+3) {
                B[i][j] = 1;
            } else {
                B[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        // Se realiza pivoteo parcial.
        int max_row = i;
        for (int j = i+1; j < 3; j++) {
            if (abs(B[j][i]) > abs(B[max_row][i])) {
                max_row = j;
            }
        }
        if (max_row != i) {
            for (int j = i; j < 6; j++) {
                double temp = B[i][j];
                B[i][j] = B[max_row][j];
                B[max_row][j] = temp;
            }
        }

        // Diagonales igual a 1.
        double pivot = B[i][i];
        for (int j = i; j < 6; j++) {
            B[i][j] /= pivot;
        }

        // Todos los elementos fuera de la diagonal iguales a 0.
        for (int j = 0; j < 3; j++) {
            if (j != i) {
                double factor = B[j][i];
                for (int k = i; k < 6; k++) {
                    B[j][k] -= factor * B[i][k];
                }
            }
        }
    }

    // Leer y mostrar los datos.
    for (int i = 0; i < 3; i++) {
        x[i] = B[i][3];
        printf("x[%d] = %lf\n", i, x[i]);
    }
}

// Compilar y ejecutar, de todas formas los resultados no son correctos