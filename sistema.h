#ifndef SISTEMA_H
#define SISTEMA_H

#include "estudiante.h"
#include "materia.h"

typedef struct {
    Estudiante **estudiantes;
    int cantEstudiantes;
    int capEstudiantes;

    Materia **materias;
    int cantMaterias;
    int capMaterias;
} Sistema;

// Funciones principales
Sistema* crearSistema();
void liberarSistema(Sistema *s);

// CRUD Estudiantes
void altaEstudiante(Sistema *s);
void bajaEstudiante(Sistema *s);
void modificarEstudianteSistema(Sistema *s);
void listarEstudiantes(const Sistema *s);

// CRUD Materias
void altaMateria(Sistema *s);
void bajaMateria(Sistema *s);
void modificarMateriaSistema(Sistema *s);
void listarMaterias(const Sistema *s);

// Relaciones
void inscribirEnMateria(Sistema *s);
void rendirMateria(Sistema *s);
void verNotasEstudiante(Sistema *s);

#endif
