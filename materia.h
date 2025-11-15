#ifndef MATERIA_H
#define MATERIA_H

#define MAX_NOMBRE_MATERIA 50

typedef struct {
    int id;                      // Identificador único de la materia
    char nombre[MAX_NOMBRE_MATERIA];  // Nombre de la materia
} Materia;

// Prototipos
Materia* crearMateria(int id, const char *nombre);
void modificarMateria(Materia *m, const char *nuevoNombre);
void mostrarMateria(const Materia *m);
void liberarMateria(Materia *m);

#endif
