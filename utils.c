#include <stdio.h>
#include <string.h>
#include "utils.h"

void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void leerCadena(char *cadena, int longitud) {
    fgets(cadena, longitud, stdin);
    cadena[strcspn(cadena, "\n")] = '\0';
}

int leerEnteroPositivo(const char *mensaje) {
    int numero;
    do {
        printf("%s", mensaje);
        if (scanf("%d", &numero) != 1 || numero <= 0) {
            printf("Error: Ingrese un número entero positivo.\n");
            limpiarBuffer();
            numero = -1;
        } else {
            limpiarBuffer();
        }
    } while (numero <= 0);
    
    return numero;
}

int validarCadenaNoVacia(const char *cadena) {
    return strlen(cadena) > 0 && cadena[0] != '\n';
}
/*limpiarBuffer() limpia el stdin para evitar que queden saltos de línea pendientes.

leerCadena() permite leer cadenas con espacios de forma segura (evita errores con scanf).*/