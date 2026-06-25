// Ejercicio 3 — Corte de control
// El archivo ventas.dat (sucursal, vendedor, monto) está ordenado por sucursal. Generá un
// informe con el total vendido por cada sucursal y, además, el monto de la venta más alta de
// cada una.

// Preguntas guía:

// 1. ¿Qué propiedad del archivo garantiza que el corte de control funcione?
// El archivo debe estar ordenado por la clave de agrupamiento, que en este caso 
// es la sucursal. Si el archivo estuviera desordenado, las ventas de la sucursal 1 
// estarían mezcladas con las de la 2 y la 3, y el bucle interno "cortaría" constantemente 
// en lugar de agrupar todo correctamente.

// 2. ¿En qué punto inicializás los acumuladores de cada grupo (total y máximo)?
// Justo después de entrar al primer while (el que recorre los grupos) y antes de entrar al 
// segundo while (el que procesa los registros de ese grupo específico). Si los inicializás 
// al principio del programa, se acumularía todo; si los inicializás dentro del while interno, 
// se reiniciarían con cada factura.

// 3. ¿Cómo te asegurás de imprimir también el informe de la última sucursal?
// El informe se imprime exactamente a la salida del while interno. Esto garantiza que, cuando el 
// archivo se termine (fread devuelva 0), el ciclo interno cortará y automáticamente ejecutará los 
// cout para esa última sucursal procesada antes de que el ciclo externo termine.


#include <iostream>
#include <cstdio>

using namespace std;

// 1. Estructura del registro
struct Venta {
    int sucursal;
    char vendedor[50]; // char array en lugar de string, como manda la regla de oro
    float monto;
};

// Declaraciones
void inicializarArchivoVentas();
void corteDeControlVentas(const char* nombreArchivo);

int main() {
    inicializarArchivoVentas();

    cout << "=== INFORME DE VENTAS POR SUCURSAL ===" << endl;
    corteDeControlVentas("ventas.dat");

    return 0;
}

// Patrón algorítmico de Corte de Control en Archivo
void corteDeControlVentas(const char* nombreArchivo) {
    FILE* f = fopen(nombreArchivo, "rb");
    if (f == NULL) {
        cout << "Error: No se pudo abrir el archivo." << endl;
        return;
    }

    Venta venta;
    int leido = fread(&venta, sizeof(Venta), 1, f); 

    while (leido == 1) {
        int sucursalActual = venta.sucursal;
        float totalSucursal = 0.0;
        float maximaVenta = -1.0;

        while (leido == 1 && venta.sucursal == sucursalActual) {
            totalSucursal += venta.monto;

            if (venta.monto > maximaVenta) {
                maximaVenta = venta.monto;
            }

            // Lectura al final del ciclo interno para avanzar el puntero
            leido = fread(&venta, sizeof(Venta), 1, f); 
        }

        // Al cortar (porque cambió la sucursal o terminó el archivo)
        cout << "Sucursal " << sucursalActual << ":" << endl;
        cout << "  -> Total vendido: $" << totalSucursal << endl;
        cout << "  -> Mayor venta: $" << maximaVenta << endl;
        cout << "--------------------------------------" << endl;
    }

    fclose(f);
}


// Función auxiliar para tener datos con los que probar
void inicializarArchivoVentas() {
    FILE* f = fopen("ventas.dat", "wb");
    if (f == NULL) return;

    Venta ventasPrueba[] = {
        {10, "Gomez", 5000.0},
        {10, "Perez", 12000.0},
        {10, "Gomez", 3000.0},
        {25, "Lopez", 45000.0},
        {25, "Suarez", 15000.0},
        {30, "Diaz",  22000.0}
    };

    fwrite(ventasPrueba, sizeof(Venta), 6, f);
    fclose(f);
}