#ifndef ARCHIVOS_H
#define ARCHIVOS_H


#include "estructuras.h"


// Rutas de archivos
#define CUENTAS_FILE "data/cuentas.dat"
#define MOVIMIENTOS_FILE "data/movimientos.txt"


// Funciones de archivos
Cuenta* cargar_cuentas(int *cantidad);
int guardar_cuentas(Cuenta *cuentas, int cantidad);
int registrar_movimiento(const char *texto);


#endif // ARCHIVOS_H