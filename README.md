# Sistema Bancario

Este proyecto es una simulación de un sistema bancario desarrollado en C. Permite la gestión completa de cuentas bancarias, registro de movimientos y almacenamiento persistente de datos en archivos.

## Estructura del Proyecto

```
SistemaBancario/
├── main.c              # Archivo principal con menú e interfaz de usuario
├── cuentas.c           # Implementación de operaciones bancarias
├── cuentas.h           # Declaraciones de funciones de cuentas
├── archivos.c          # Funciones para manejo de archivos y persistencia
├── archivos.h          # Declaraciones de funciones de archivos
├── estructuras.h       # Definición de estructuras de datos
├── Makefile           # Script para compilar el proyecto
└── data/
    ├── cuentas.dat    # Archivo binario con datos de cuentas
    └── movimientos.txt # Registro de todas las transacciones
```

## Funcionalidades

### Gestión de Cuentas
- ✅ **Crear cuenta**: Registro de nuevas cuentas con titular, DNI y saldo inicial
- ✅ **Consultar cuenta**: Mostrar información detallada por número de cuenta
- ✅ **Listar cuentas**: Visualizar todas las cuentas activas del sistema
- ✅ **Eliminar cuenta**: Eliminación lógica de cuentas con saldo cero

### Operaciones Bancarias
- ✅ **Depósitos**: Agregar dinero a cualquier cuenta activa
- ✅ **Retiros**: Extraer dinero verificando saldo disponible
- ✅ **Transferencias**: Mover dinero entre cuentas del sistema

### Sistema de Persistencia
- ✅ **Almacenamiento binario**: Datos de cuentas en formato eficiente
- ✅ **Log de transacciones**: Registro detallado de todas las operaciones
- ✅ **Eliminación lógica**: Las cuentas eliminadas se conservan en el historial

## Menú del Sistema

```
=== MINI BANCO ===
1) Crear cuenta
2) Depositar
3) Extraer
4) Transferir
5) Mostrar cuenta por número
6) Listar todas las cuentas
7) Eliminar cuenta
0) Salir
```

## Compilación y Ejecución

### Opción 1: Con Make (si está disponible)
```bash
make
./sistema_bancario
```

### Opción 2: Compilación manual con GCC
```bash
gcc -Wall -Wextra -g -o sistema_bancario main.c cuentas.c archivos.c
./sistema_bancario
```

### En Windows con PowerShell
```powershell
gcc -Wall -Wextra -g -o sistema_bancario.exe main.c cuentas.c archivos.c
.\sistema_bancario.exe
```

## Características Técnicas

### Estructuras de Datos
```c
typedef struct {
    int numero_cuenta;           // Identificador único
    char titular[100];           // Nombre del titular
    char dni[20];               // Documento de identidad
    double saldo;               // Saldo actual
    int activa;                 // Estado (1=activa, 0=eliminada)
} Cuenta;
```

### Validaciones Implementadas
- 🔒 **Saldo suficiente**: Verificación antes de retiros y transferencias
- 🔒 **Cuentas activas**: Solo se pueden operar cuentas no eliminadas
- 🔒 **Eliminación segura**: Solo permite eliminar cuentas con saldo cero
- 🔒 **Confirmación**: Solicita confirmación antes de eliminar cuentas
- 🔒 **Precisión numérica**: Manejo correcto de números decimales

### Códigos de Retorno
| Función | Código | Significado |
|---------|--------|-------------|
| General | `0` | Operación exitosa |
| General | `-1` | Error general o cuenta no encontrada |
| Eliminar | `-2` | No se puede eliminar (saldo ≠ 0) |

## Archivos de Datos

### `data/cuentas.dat`
- Formato binario para almacenamiento eficiente
- Contiene todas las cuentas (activas e inactivas)
- Se actualiza automáticamente tras cada operación

### `data/movimientos.txt`
- Formato de texto plano legible
- Registro cronológico de todas las transacciones
- Ejemplos:
  ```
  CREAR: Cuenta 1001 | Titular: Juan Pérez | DNI: 12345678 | Saldo: 1000.00
  DEPOSITO: Cuenta 1001 | Monto: 500.00 | NuevoSaldo: 1500.00
  TRANSFERENCIA: De 1001 a 1002 | Monto: 200.00 | SaldoOrig: 1300.00 | SaldoDest: 200.00
  ELIMINACION: Cuenta 1003 | Titular: Ana García | DNI: 87654321
  ```

## Requisitos del Sistema

- **Compilador**: GCC o compatible con estándares C99+
- **Sistema Operativo**: Windows, Linux, macOS
- **Memoria**: Mínima (el sistema maneja archivos eficientemente)
- **Dependencias**: Solo librerías estándar de C

## Consideraciones de Seguridad

- ✅ Las cuentas eliminadas se conservan para auditoría
- ✅ Todas las operaciones quedan registradas en el log
- ✅ Validación de entrada para prevenir errores
- ✅ Manejo seguro de memoria (liberación correcta)

## Autor

- Abril Mouriño




