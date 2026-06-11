// Ejercicio C-3: Facturación mensual por cliente con cliente más rentable
// Un sistema tiene registros de facturas ordenadas por código de cliente. Cada factura tiene:
// código de cliente, número de factura y monto. Se pide: (a) mostrar el total facturado y
// cantidad de facturas por cliente; (b) al finalizar, indicar qué cliente tuvo el mayor monto total.
#include <iostream>
#include <string>
using namespace std;

struct Factura {
    int codigoCliente;
    int numeroFactura;
    float monto;
};

void cortePorCliente(Factura arrayFacturas[], int len);

int main() {
    Factura arrayFacturas[] = {
        {201, 1001, 1500.50},
        {201, 1002, 2000.00},
        {202, 1003, 3000.00},
        {202, 1004, 2500.00},
        {203, 1005, 4000.00},
        {203, 1006, 3500.00},
        {203, 1007, 4500.00}
    };

    cortePorCliente(arrayFacturas, 7);
}

void cortePorCliente(Factura arrayFacturas[], int len) {
    int i = 0;
    int clienteMasRentable = -1; // luego sera reemplazado por el codigo del cliente mas rentable
    float montoMaximo = 0.0;

    while (i < len) {
        int codigoActual = arrayFacturas[i].codigoCliente;
        int cantidadFacturas = 0;
        float totalFacturado = 0.0;

        while(i < len &&codigoActual == arrayFacturas[i].codigoCliente) {
            cantidadFacturas++;
            totalFacturado += arrayFacturas[i].monto;
            i++;
        }

        cout << "Código Cliente: " << codigoActual << endl;
        cout << "Cantidad de Facturas: " << cantidadFacturas << endl;
        cout << "Monto Total: " << totalFacturado << endl;
        cout << "-----------------------------" << endl;

        if (totalFacturado > montoMaximo) {
            montoMaximo = totalFacturado;
            clienteMasRentable = codigoActual;
        }

    }

    cout << "RESUMEN FINAL:" << endl;
    cout << "Cliente más rentable: " << clienteMasRentable << endl;
    cout << "Monto máximo: " << montoMaximo << endl;
}