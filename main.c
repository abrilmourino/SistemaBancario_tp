#include <stdio.h>
#include <stdlib.h>
#include "sistema.h"
#include "utils.h"

int main() {
    Sistema *sistema = crearSistema();
    if (!sistema) {
        printf("Error fatal: No se pudo inicializar el sistema.\n");
        return 1;
    }
    
    int opcion;

    do {
        printf("\n==== MENU PRINCIPAL ====\n");
        printf("1. Alta estudiante\n");
        printf("2. Baja estudiante\n");
        printf("3. Modificar estudiante\n");
        printf("4. Listar estudiantes\n");
        printf("5. Alta materia\n");
        printf("6. Baja materia\n");
        printf("7. Modificar materia\n");
        printf("8. Listar materias\n");
        printf("9. Inscribir estudiante en materia\n");
        printf("10. Rendir materia\n");
        printf("11. Ver notas de estudiante\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        limpiarBuffer();

        switch (opcion) {
            case 1: altaEstudiante(sistema); break;
            case 2: bajaEstudiante(sistema); break;
            case 3: modificarEstudianteSistema(sistema); break;
            case 4: listarEstudiantes(sistema); break;
            case 5: altaMateria(sistema); break;
            case 6: bajaMateria(sistema); break;
            case 7: modificarMateriaSistema(sistema); break;
            case 8: listarMaterias(sistema); break;
            case 9: inscribirEnMateria(sistema); break;
            case 10: rendirMateria(sistema); break;
            case 11: verNotasEstudiante(sistema); break;
            case 0: printf("Saliendo...\n"); break;
            default: printf("Opción inválida.\n");
        }

    } while (opcion != 0);

    liberarSistema(sistema);
    return 0;
}
