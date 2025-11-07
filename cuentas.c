#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"
#include "archivos.h"
#include "cuentas.h"

// Genera un nuevo número de cuenta (simple: último + 1)
static int generar_numero_cuenta() {
    int n = 0;
    int cantidad = 0;
    Cuenta *arr = cargar_cuentas(&cantidad);
    if (!arr) return 1001; // si no hay archivo, empezamos en 1001

    for (int i = 0; i < cantidad; ++i) {
        if (arr[i].numero_cuenta > n) n = arr[i].numero_cuenta;
    }

    free(arr);
    return n + 1;
}

// Buscar índice de cuenta por número
static int buscar_indice_por_numero(Cuenta *arr, int cantidad, int numero) {
    for (int i = 0; i < cantidad; ++i) {
        if (arr[i].activa && arr[i].numero_cuenta == numero)
            return i;
    }
    return -1;
}

int crear_cuenta(const char *nombre, const char *dni, double saldo_inicial) {
    if (!nombre || !dni || saldo_inicial < 0) return -1;

    int cantidad = 0;
    Cuenta *arr = cargar_cuentas(&cantidad);

    Cuenta *nuevo = realloc(arr, sizeof(Cuenta) * (cantidad + 1));
    if (!nuevo) {
        free(arr);
        return -1;
    }
    arr = nuevo;

    int num = generar_numero_cuenta();

    Cuenta c;
    c.numero_cuenta = num;
    strncpy(c.titular, nombre, sizeof(c.titular) - 1);
    c.titular[sizeof(c.titular) - 1] = '\0';
    strncpy(c.dni, dni, sizeof(c.dni) - 1);
    c.dni[sizeof(c.dni) - 1] = '\0';
    c.saldo = saldo_inicial;
    c.activa = 1;

    arr[cantidad] = c;
    int res = guardar_cuentas(arr, cantidad + 1);

    if (res == 0) {
        char buf[256];
        snprintf(buf, sizeof(buf),
                 "CREAR: Cuenta %d | Titular: %s | DNI: %s | Saldo: %.2f",
                 c.numero_cuenta, c.titular, c.dni, c.saldo);
        registrar_movimiento(buf);
    }

    free(arr);
    return (res == 0) ? num : -1;
}

int listar_cuentas() {
    int cantidad = 0;
    Cuenta *arr = cargar_cuentas(&cantidad);

    if (!arr || cantidad == 0) {
        printf("No hay cuentas registradas.\n");
        free(arr);
        return 0;
    }

    printf("%5s | %-20s | %-10s | %10s\n", "Nro", "Titular", "DNI", "Saldo");
    printf("-------------------------------------------------------------\n");

    for (int i = 0; i < cantidad; ++i) {
        if (!arr[i].activa) continue;
        printf("%5d | %-20s | %-10s | %10.2f\n",
               arr[i].numero_cuenta, arr[i].titular, arr[i].dni, arr[i].saldo);
    }

    free(arr);
    return 0;
}

int mostrar_cuenta_por_numero(int numero) {
    int cantidad = 0;
    Cuenta *arr = cargar_cuentas(&cantidad);
    if (!arr) {
        printf("No se encontró la cuenta.\n");
        return -1;
    }

    for (int i = 0; i < cantidad; ++i) {
        if (arr[i].activa && arr[i].numero_cuenta == numero) {
            printf("Cuenta: %d\nTitular: %s\nDNI: %s\nSaldo: %.2f\n",
                   arr[i].numero_cuenta, arr[i].titular, arr[i].dni,
                   arr[i].saldo);
            free(arr);
            return 0;
        }
    }

    printf("Cuenta %d no encontrada.\n", numero);
    free(arr);
    return -1;
}

int depositar(int numero, double monto) {
    if (monto <= 0) return -1;

    int cantidad = 0;
    Cuenta *arr = cargar_cuentas(&cantidad);
    if (!arr) return -1;

    int idx = buscar_indice_por_numero(arr, cantidad, numero);
    if (idx < 0) {
        free(arr);
        return -1;
    }

    arr[idx].saldo += monto;
    int res = guardar_cuentas(arr, cantidad);

    if (res == 0) {
        char buf[256];
        snprintf(buf, sizeof(buf),
                 "DEPOSITO: Cuenta %d | Monto: %.2f | NuevoSaldo: %.2f",
                 numero, monto, arr[idx].saldo);
        registrar_movimiento(buf);
    }

    free(arr);
    return res;
}

int extraer(int numero, double monto) {
    if (monto <= 0) return -1;

    int cantidad = 0;
    Cuenta *arr = cargar_cuentas(&cantidad);
    if (!arr) return -1;

    int idx = buscar_indice_por_numero(arr, cantidad, numero);
    if (idx < 0) {
        free(arr);
        return -1;
    }

    if (arr[idx].saldo < monto) {
        free(arr);
        return -1;
    }

    arr[idx].saldo -= monto;
    int res = guardar_cuentas(arr, cantidad);

    if (res == 0) {
        char buf[256];
        snprintf(buf, sizeof(buf),
                 "EXTRACCION: Cuenta %d | Monto: %.2f | NuevoSaldo: %.2f",
                 numero, monto, arr[idx].saldo);
        registrar_movimiento(buf);
    }

    free(arr);
    return res;
}

int transferir(int origen, int destino, double monto) {
    if (monto <= 0) return -1;

    int cantidad = 0;
    Cuenta *arr = cargar_cuentas(&cantidad);
    if (!arr) return -1;

    int idx_o = buscar_indice_por_numero(arr, cantidad, origen);
    int idx_d = buscar_indice_por_numero(arr, cantidad, destino);

    if (idx_o < 0 || idx_d < 0) {
        free(arr);
        return -1;
    }

    if (arr[idx_o].saldo < monto) {
        free(arr);
        return -1;
    }

    arr[idx_o].saldo -= monto;
    arr[idx_d].saldo += monto;

    int res = guardar_cuentas(arr, cantidad);

    if (res == 0) {
        char buf[256];
        snprintf(buf, sizeof(buf),
                 "TRANSFERENCIA: De %d a %d | Monto: %.2f | SaldoOrig: %.2f | SaldoDest: %.2f",
                 origen, destino, monto, arr[idx_o].saldo, arr[idx_d].saldo);
        registrar_movimiento(buf);
    }

    free(arr);
    return res;
}

int eliminar_cuenta(int numero) {
    int cantidad = 0;
    Cuenta *arr = cargar_cuentas(&cantidad);
    if (!arr) return -1;

    int idx = buscar_indice_por_numero(arr, cantidad, numero);
    if (idx < 0) {
        free(arr);
        return -1; // Cuenta no encontrada
    }

    // Verificar que el saldo sea 0 (con tolerancia para punto flotante)
    if (arr[idx].saldo < -0.01 || arr[idx].saldo > 0.01) {
        free(arr);
        return -2; // Saldo no es cero
    }

    // Marcar cuenta como inactiva (eliminación lógica)
    arr[idx].activa = 0;
    
    int res = guardar_cuentas(arr, cantidad);
    
    if (res == 0) {
        char buf[256];
        snprintf(buf, sizeof(buf),
                 "ELIMINACION: Cuenta %d | Titular: %s | DNI: %s",
                 numero, arr[idx].titular, arr[idx].dni);
        registrar_movimiento(buf);
    }

    free(arr);
    return res;
}
