#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estructuras.h"
#include "cuentas.h"
#include "archivos.h"


static void menu() {
    printf("\n=== MINI BANCO ===\n");
    printf("1) Crear cuenta\n");
    printf("2) Depositar\n");
    printf("3) Extraer\n");
    printf("4) Transferir\n");
    printf("5) Mostrar cuenta por numero\n");
    printf("6) Listar todas las cuentas\n");
    printf("7) Eliminar cuenta\n");
    printf("0) Salir\n");
    printf("Elija una opcion: ");
}

int main() {
    int opcion = -1;
    while (1) {
        menu();
        if (scanf("%d", &opcion) != 1) { // limpiar input
            int c; while ((c = getchar()) != '\n' && c != EOF);
            opcion = -1; continue;
        }
        if (opcion == 0) break;

        if (opcion == 1) {
            char nombre[100]; char dni[30]; double monto;
            printf("Ingrese nombre del titular: ");
            getchar(); // consumir newline
            fgets(nombre, sizeof(nombre), stdin);
            nombre[strcspn(nombre, "\n")] = '\0';
            printf("Ingrese DNI: ");
            fgets(dni, sizeof(dni), stdin);
            dni[strcspn(dni, "\n")] = '\0';
            printf("Saldo inicial: ");
            if (scanf("%lf", &monto) != 1) { printf("Monto invalido.\n"); continue; }
            int nro = crear_cuenta(nombre, dni, monto);
            if (nro > 0) printf("Cuenta creada con numero %d\n", nro);
            else printf("Error al crear la cuenta.\n");
        }
        else if (opcion == 2) {
            int num; double monto;
            printf("Nro de cuenta: "); if (scanf("%d", &num) != 1) { printf("Entrada invalida.\n"); continue; }
            printf("Monto a depositar: "); if (scanf("%lf", &monto) != 1) { printf("Monto invalido.\n"); continue; }
            if (depositar(num, monto) == 0) printf("Depósito exitoso.\n"); else printf("Error en deposito.\n");
        }
        else if (opcion == 3) {
            int num; double monto;
            printf("Nro de cuenta: "); if (scanf("%d", &num) != 1) { printf("Entrada invalida.\n"); continue; }
            printf("Monto a extraer: "); if (scanf("%lf", &monto) != 1) { printf("Monto invalido.\n"); continue; }
            if (extraer(num, monto) == 0) printf("Extraccion exitosa.\n"); else printf("Error en extracción (saldo insuficiente o cuenta inexistente).\n");
        }
        else if (opcion == 4) {
            int ori, dest; double monto;
            printf("Cuenta origen: "); if (scanf("%d", &ori) != 1) { printf("Entrada invalida.\n"); continue; }
            printf("Cuenta destino: "); if (scanf("%d", &dest) != 1) { printf("Entrada invalida.\n"); continue; }
            printf("Monto a transferir: "); if (scanf("%lf", &monto) != 1) { printf("Monto invalido.\n"); continue; }
            if (transferir(ori, dest, monto) == 0) printf("Transferencia exitosa.\n"); else printf("Error en transferencia.\n");
        }
        else if (opcion == 5) {
            int num; printf("Nro de cuenta: "); if (scanf("%d", &num) != 1) { printf("Entrada invalida.\n"); continue; }
            mostrar_cuenta_por_numero(num);
        }
        else if (opcion == 6) {
            listar_cuentas();
        }
        else if (opcion == 7) {
            int num; 
            printf("Nro de cuenta a eliminar: "); 
            if (scanf("%d", &num) != 1) { 
                printf("Entrada invalida.\n"); 
                continue; 
            }
            
            // Mostrar información de la cuenta antes de eliminar
            printf("\nInformación de la cuenta a eliminar:\n");
            if (mostrar_cuenta_por_numero(num) != 0) {
                printf("No se puede eliminar: cuenta no encontrada.\n");
                continue;
            }
            
            // Pedir confirmación
            printf("\n¿Esta seguro que desea eliminar esta cuenta? (s/N): ");
            char confirmacion;
            getchar(); // consumir newline del scanf anterior
            confirmacion = getchar();
            
            if (confirmacion == 's' || confirmacion == 'S') {
                int resultado = eliminar_cuenta(num);
                if (resultado == 0) {
                    printf("Cuenta eliminada exitosamente.\n");
                } else if (resultado == -2) {
                    printf("Error: No se puede eliminar una cuenta con saldo diferente a 0.\n");
                } else {
                    printf("Error al eliminar la cuenta.\n");
                }
            } else {
                printf("Eliminacion cancelada.\n");
            }
        }
        else {
            printf("Opcion invalida.\n");
        }
    }

    printf("Saliendo...\n");
    return 0;

}
