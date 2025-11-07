#ifndef CUENTAS_H
#define CUENTAS_H


#include "estructuras.h"


// Operaciones sobre cuentas (devuelven 0 OK, -1 error)
int crear_cuenta(const char* nombre, const char* dni, double saldo_inicial);
int listar_cuentas();
int mostrar_cuenta_por_numero(int numero);
int depositar(int numero, double monto);
int extraer(int numero, double monto);
int transferir(int origen, int destino, double monto);
int eliminar_cuenta(int numero);


#endif // CUENTAS_H