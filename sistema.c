#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sistema.h"
#include "utils.h"

Sistema* crearSistema() {
    Sistema *s = (Sistema*) malloc(sizeof(Sistema));
    if (!s) {
        printf("Error: No se pudo crear el sistema.\n");
        return NULL;
    }
    
    s->cantEstudiantes = 0;
    s->capEstudiantes = 10;
    s->estudiantes = malloc(sizeof(Estudiante*) * s->capEstudiantes);
    if (!s->estudiantes) {
        printf("Error: No se pudo asignar memoria para estudiantes.\n");
        free(s);
        return NULL;
    }

    s->cantMaterias = 0;
    s->capMaterias = 10;
    s->materias = malloc(sizeof(Materia*) * s->capMaterias);
    if (!s->materias) {
        printf("Error: No se pudo asignar memoria para materias.\n");
        free(s->estudiantes);
        free(s);
        return NULL;
    }

    return s;
}

void liberarSistema(Sistema *s) {
    for (int i = 0; i < s->cantEstudiantes; i++)
        liberarEstudiante(s->estudiantes[i]);
    for (int i = 0; i < s->cantMaterias; i++)
        liberarMateria(s->materias[i]);

    free(s->estudiantes);
    free(s->materias);
    free(s);
}

// ===== CRUD ESTUDIANTES =====
void altaEstudiante(Sistema *s) {
    if (s->cantEstudiantes == s->capEstudiantes) {
        s->capEstudiantes *= 2;
        s->estudiantes = realloc(s->estudiantes, sizeof(Estudiante*) * s->capEstudiantes);
        if (!s->estudiantes) {
            printf("Error: No se pudo asignar memoria.\n");
            return;
        }
    }

    int id = s->cantEstudiantes + 1;
    char nombre[50];
    int edad;

    // Validar nombre
    do {
        printf("Ingrese nombre: ");
        leerCadena(nombre, 50);
        if (!validarCadenaNoVacia(nombre)) {
            printf("Error: El nombre no puede estar vacío.\n");
        }
    } while (!validarCadenaNoVacia(nombre));

    // Validar edad
    edad = leerEnteroPositivo("Ingrese edad: ");

    s->estudiantes[s->cantEstudiantes++] = crearEstudiante(id, nombre, edad);
    printf("Estudiante agregado correctamente.\n");
}

void listarEstudiantes(const Sistema *s) {
    if (s->cantEstudiantes == 0) {
        printf("No hay estudiantes registrados.\n");
        return;
    }

    printf("\n--- LISTADO DE ESTUDIANTES ---\n");
    for (int i = 0; i < s->cantEstudiantes; i++)
        mostrarEstudiante(s->estudiantes[i]);
}

void bajaEstudiante(Sistema *s) {
    int id;
    printf("Ingrese ID del estudiante a eliminar: ");
    scanf("%d", &id);
    limpiarBuffer();

    for (int i = 0; i < s->cantEstudiantes; i++) {
        if (s->estudiantes[i]->id == id) {
            liberarEstudiante(s->estudiantes[i]);
            for (int j = i; j < s->cantEstudiantes - 1; j++)
                s->estudiantes[j] = s->estudiantes[j + 1];
            s->cantEstudiantes--;
            printf("Estudiante eliminado.\n");
            return;
        }
    }
    printf("No se encontró el estudiante.\n");
}

void modificarEstudianteSistema(Sistema *s) {
    int id;
    printf("Ingrese ID del estudiante a modificar: ");
    scanf("%d", &id);
    limpiarBuffer();

    for (int i = 0; i < s->cantEstudiantes; i++) {
        if (s->estudiantes[i]->id == id) {
            char nombre[50];
            int edad;
            printf("Nuevo nombre: ");
            leerCadena(nombre, 50);
            printf("Nueva edad: ");
            scanf("%d", &edad);
            limpiarBuffer();

            modificarEstudiante(s->estudiantes[i], nombre, edad);
            printf("Estudiante modificado.\n");
            return;
        }
    }
    printf("No se encontró el estudiante.\n");
}

// ===== CRUD MATERIAS =====
void altaMateria(Sistema *s) {
    if (s->cantMaterias == s->capMaterias) {
        s->capMaterias *= 2;
        s->materias = realloc(s->materias, sizeof(Materia*) * s->capMaterias);
        if (!s->materias) {
            printf("Error: No se pudo asignar memoria.\n");
            return;
        }
    }

    int id = s->cantMaterias + 1;
    char nombre[50];
    
    // Validar nombre de materia
    do {
        printf("Ingrese nombre de materia: ");
        leerCadena(nombre, 50);
        if (!validarCadenaNoVacia(nombre)) {
            printf("Error: El nombre de la materia no puede estar vacío.\n");
        }
    } while (!validarCadenaNoVacia(nombre));

    s->materias[s->cantMaterias++] = crearMateria(id, nombre);
    printf("Materia agregada correctamente.\n");
}

void listarMaterias(const Sistema *s) {
    if (s->cantMaterias == 0) {
        printf("No hay materias registradas.\n");
        return;
    }

    printf("\n--- LISTADO DE MATERIAS ---\n");
    for (int i = 0; i < s->cantMaterias; i++)
        mostrarMateria(s->materias[i]);
}

void bajaMateria(Sistema *s) {
    int id;
    printf("Ingrese ID de la materia a eliminar: ");
    scanf("%d", &id);
    limpiarBuffer();

    for (int i = 0; i < s->cantMaterias; i++) {
        if (s->materias[i]->id == id) {
            liberarMateria(s->materias[i]);
            for (int j = i; j < s->cantMaterias - 1; j++)
                s->materias[j] = s->materias[j + 1];
            s->cantMaterias--;
            printf("Materia eliminada.\n");
            return;
        }
    }
    printf("No se encontró la materia.\n");
}

void modificarMateriaSistema(Sistema *s) {
    int id;
    printf("Ingrese ID de la materia a modificar: ");
    scanf("%d", &id);
    limpiarBuffer();

    for (int i = 0; i < s->cantMaterias; i++) {
        if (s->materias[i]->id == id) {
            char nombre[50];
            printf("Nuevo nombre de la materia: ");
            leerCadena(nombre, 50);

            modificarMateria(s->materias[i], nombre);
            printf("Materia modificada correctamente.\n");
            return;
        }
    }
    printf("No se encontró la materia.\n");
}

// ===== RELACIONES =====
void inscribirEnMateria(Sistema *s) {
    int idEst, idMat;
    printf("ID estudiante: ");
    scanf("%d", &idEst);
    printf("ID materia: ");
    scanf("%d", &idMat);
    limpiarBuffer();

    if (idEst <= 0 || idEst > s->cantEstudiantes || idMat <= 0 || idMat > s->cantMaterias) {
        printf("ID inválido.\n");
        return;
    }

    Estudiante *e = s->estudiantes[idEst - 1];
    
    // Verificar si ya está inscrito
    for (int i = 0; i < e->cantMaterias; i++) {
        if (e->materias[i].materiaId == idMat) {
            printf("El estudiante ya está inscrito en esta materia.\n");
            return;
        }
    }

    InscripcionMateria *temp = realloc(e->materias, sizeof(InscripcionMateria) * (e->cantMaterias + 1));
    if (!temp) {
        printf("Error: No se pudo asignar memoria para la inscripción.\n");
        return;
    }
    e->materias = temp;
    e->materias[e->cantMaterias].materiaId = idMat;
    e->materias[e->cantMaterias].nota = -1; // No rindió aún
    e->cantMaterias++;

    printf("Estudiante %s inscrito en materia %s.\n",
           e->nombre, s->materias[idMat - 1]->nombre);
}

void rendirMateria(Sistema *s) {
    int idEst, idMat;
    printf("ID estudiante: ");
    scanf("%d", &idEst);
    printf("ID materia: ");
    scanf("%d", &idMat);
    limpiarBuffer();

    if (idEst <= 0 || idEst > s->cantEstudiantes || idMat <= 0 || idMat > s->cantMaterias) {
        printf("ID inválido.\n");
        return;
    }

    Estudiante *e = s->estudiantes[idEst - 1];
    
    // Buscar la materia en las inscripciones del estudiante
    for (int i = 0; i < e->cantMaterias; i++) {
        if (e->materias[i].materiaId == idMat) {
            int nota;
            printf("Ingrese nota (0-10): ");
            scanf("%d", &nota);
            limpiarBuffer();
            
            if (nota < 0 || nota > 10) {
                printf("Nota inválida. Debe ser entre 0 y 10.\n");
                return;
            }
            
            e->materias[i].nota = nota;
            printf("Estudiante %s - Materia %s: nota %d registrada.\n",
                   e->nombre, s->materias[idMat - 1]->nombre, nota);
            return;
        }
    }
    printf("El estudiante no está inscrito en esta materia.\n");
}

void verNotasEstudiante(Sistema *s) {
    int idEst;
    printf("Ingrese ID del estudiante: ");
    scanf("%d", &idEst);
    limpiarBuffer();

    if (idEst <= 0 || idEst > s->cantEstudiantes) {
        printf("ID de estudiante inválido.\n");
        return;
    }

    Estudiante *e = s->estudiantes[idEst - 1];
    printf("\n--- NOTAS DE %s ---\n", e->nombre);
    
    if (e->cantMaterias == 0) {
        printf("No está inscrito en ninguna materia.\n");
        return;
    }

    for (int i = 0; i < e->cantMaterias; i++) {
        int idMat = e->materias[i].materiaId;
        printf("Materia: %s - ", s->materias[idMat - 1]->nombre);
        if (e->materias[i].nota == -1) {
            printf("Sin rendir\n");
        } else {
            printf("Nota: %d\n", e->materias[i].nota);
        }
    }
}
