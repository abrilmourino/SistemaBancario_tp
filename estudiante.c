#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estudiante.h"

Estudiante* crearEstudiante(int id, const char *nombre, int edad) {
    Estudiante *e = (Estudiante*) malloc(sizeof(Estudiante));
    if (!e) return NULL;

    e->id = id;
    strncpy(e->nombre, nombre, MAX_NOMBRE - 1);
    e->nombre[MAX_NOMBRE - 1] = '\0';
    e->edad = edad;
    e->materias = NULL;
    e->cantMaterias = 0;
    return e;
}

void modificarEstudiante(Estudiante *e, const char *nuevoNombre, int nuevaEdad) {
    strncpy(e->nombre, nuevoNombre, MAX_NOMBRE - 1);
    e->nombre[MAX_NOMBRE - 1] = '\0';
    e->edad = nuevaEdad;
}

void mostrarEstudiante(const Estudiante *e) {
    printf("ID: %d | Nombre: %s | Edad: %d | Materias inscriptas: %d\n",
           e->id, e->nombre, e->edad, e->cantMaterias);
    
    if (e->cantMaterias > 0) {
        printf("  Materias: ");
        for (int i = 0; i < e->cantMaterias; i++) {
            printf("[ID:%d", e->materias[i].materiaId);
            if (e->materias[i].nota != -1) {
                printf(" Nota:%d", e->materias[i].nota);
            } else {
                printf(" Sin rendir");
            }
            printf("]");
            if (i < e->cantMaterias - 1) printf(", ");
        }
        printf("\n");
    }
}

void liberarEstudiante(Estudiante *e) {
    if (e->materias != NULL) free(e->materias);
    free(e);
}
/*crearEstudiante: reserva memoria y carga datos básicos.

modificarEstudiante: cambia nombre o edad.

mostrarEstudiante: imprime por consola.

liberarEstudiante: libera toda la memoria usada por ese estudiante.*/