#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#define NAME_MAX_LEN 100
#define DNI_MAX_LEN 20

typedef struct {
    int numero_cuenta;
    char titular[NAME_MAX_LEN];
    char dni[DNI_MAX_LEN];
    double saldo;
    int activa;
} Cuenta;

#endif // ESTRUCTURAS_H
