#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#define MAX_NOMBRE 50

typedef struct { 
    int materiaId;
    int nota;  // -1 si no rindió
} InscripcionMateria;

typedef struct {
    int id;                      // Identificador único del estudiante
    char nombre[MAX_NOMBRE];     // Nombre del estudiante
    int edad;                    // Edad del estudiante
    InscripcionMateria *materias; // Array dinámico de materias inscritas con sus notas
    int cantMaterias;            // Cantidad de materias en las que está inscrito
} Estudiante;

// Prototipos de funciones relacionadas con estudiantes
Estudiante* crearEstudiante(int id, const char *nombre, int edad);
void modificarEstudiante(Estudiante *e, const char *nuevoNombre, int nuevaEdad);
void mostrarEstudiante(const Estudiante *e);
void liberarEstudiante(Estudiante *e);

#endif

/*--Define la estructura Estudiante con su ID, nombre, edad y materias.

  --Los prototipos permiten usar estas funciones en otros archivos.*/