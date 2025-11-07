#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "archivos.h"
#include "estructuras.h"



// Carga todas las cuentas desde CUENTAS_FILE.
// Devuelve un arreglo dinámico (malloc) y coloca la cantidad en *cantidad.
// El llamador debe free() el arreglo.
Cuenta* cargar_cuentas(int *cantidad) {
FILE *f = fopen(CUENTAS_FILE, "rb");
*cantidad = 0;
if (!f) return NULL; // no hay archivo todavía


// averiguar cuántas cuentas hay
fseek(f, 0, SEEK_END);
long size = ftell(f);
rewind(f);
if (size == 0) { fclose(f); return NULL; }


int n = (int)(size / sizeof(Cuenta));
Cuenta *arr = malloc(sizeof(Cuenta) * n);
if (!arr) { fclose(f); return NULL; }


size_t read = fread(arr, sizeof(Cuenta), n, f);
if (read != (size_t)n) {
free(arr);
fclose(f);
return NULL;
}


fclose(f);
*cantidad = n;
return arr;
}


// Guarda todas las cuentas en CUENTAS_FILE (sobrescribe).
int guardar_cuentas(Cuenta *cuentas, int cantidad) {
FILE *f = fopen(CUENTAS_FILE, "wb");
if (!f) return -1;
size_t written = fwrite(cuentas, sizeof(Cuenta), cantidad, f);
fclose(f);
return (written == (size_t)cantidad) ? 0 : -1;
}


// Registra un movimiento en MOVIMIENTOS_FILE (texto, append)
int registrar_movimiento(const char *texto) {
FILE *f = fopen(MOVIMIENTOS_FILE, "a");
if (!f) return -1;
fprintf(f, "%s\n", texto);
fclose(f);
return 0;
}