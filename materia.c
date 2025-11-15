#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "materia.h"

Materia* crearMateria(int id, const char *nombre) {
    Materia *m = (Materia*) malloc(sizeof(Materia));
    if (!m) return NULL;

    m->id = id;
    strncpy(m->nombre, nombre, MAX_NOMBRE_MATERIA - 1);
    m->nombre[MAX_NOMBRE_MATERIA - 1] = '\0';
    return m;
}

void modificarMateria(Materia *m, const char *nuevoNombre) {
    strncpy(m->nombre, nuevoNombre, MAX_NOMBRE_MATERIA - 1);
    m->nombre[MAX_NOMBRE_MATERIA - 1] = '\0';
}

void mostrarMateria(const Materia *m) {
    printf("ID: %d | Materia: %s\n", m->id, m->nombre);
}

void liberarMateria(Materia *m) {
    free(m);
}
