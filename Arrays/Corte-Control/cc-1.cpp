// Ejercicio C-1: Resumen de ventas por vendedor
// Una empresa registra las ventas del mes en un array ordenado por código de vendedor.
// Cada registro contiene: código de vendedor y monto de venta. Se pide mostrar, para cada
// vendedor: código, cantidad de ventas realizadas, monto total y monto promedio por venta.
#include <iostream>
#include <string>
using namespace std;

struct Venta {
    int codigoVendedor;
    float montoVenta;
};

void cortePorVendedor(Venta arrayVentas[], int len);

int main() {

    Venta arrayVentas[] = {
        {101, 1500.50},
        {101, 2000.00},
        {102, 3000.00},
        {102, 2500.00},
        {103, 4000.00},
        {103, 3500.00},
        {103, 4500.00}
    };

    cortePorVendedor(arrayVentas, 7);

}

void cortePorVendedor(Venta arrayVentas[], int len) {
    int i = 0;
    while (i < len) {
        int codigoActual = arrayVentas[i].codigoVendedor;
        int cantidadVentas = 0;
        float montoTotal = 0.0;

        // Acumulamos mientras el código de vendedor sea el mismo
        while (i < len && arrayVentas[i].codigoVendedor == codigoActual) {
            cantidadVentas++;
            montoTotal += arrayVentas[i].montoVenta;
            i++;
        }

        // Calculamos el monto promedio
        float montoPromedio = montoTotal / cantidadVentas;

        // Mostramos los resultados para el vendedor actual
        cout << "Código Vendedor: " << codigoActual << endl;
        cout << "Cantidad de Ventas: " << cantidadVentas << endl;
        cout << "Monto Total: " << montoTotal << endl;
        cout << "Monto Promedio por Venta: " << montoPromedio << endl;
        cout << "-----------------------------" << endl;
    }

}