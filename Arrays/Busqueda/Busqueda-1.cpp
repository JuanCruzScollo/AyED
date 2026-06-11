// Ejercicio B-1: Sistema de productos con búsqueda y estadísticas
// Una tienda tiene hasta 50 productos almacenados en un array. Cada producto tiene
// nombre, precio y stock. El sistema debe: (a) permitir buscar un producto por nombre; (b) si
// se encuentra, mostrar sus datos e indicar si el stock es bajo (< 5 unidades); (c) informar
// cuántos productos tienen precio mayor al encontrado.
#include <iostream>
#include <string>
using namespace std;

// Definimos el struct para que el compilador sepa qué es un "Producto"
struct Producto {
    string nombre;
    float precio;
    int stock;
};

// Declaración de funciones para que main las conozca
int buscar(Producto arr[], int len, string nombre);
void mostrarDatosYValidarStock(Producto producto);
void informarCantProductosMayor(Producto arr[], int len, float precio);
void resolverB1(Producto arr[], int len, string nombre);


int main() {
    // Ejemplo de prueba por si querés testearlo
    const int MAX = 50;
    Producto inventario[MAX] = {
        {"Teclado Mech", 4500.50, 3},
        {"Mouse Gamer", 3200.00, 10},
        {"Monitor 24", 85000.00, 2},
        {"Auriculares", 6800.00, 15}
    };
    int cantidadActual = 4;

    cout << "--- Ejecutando Ejercicio B-1 ---" << endl;
    resolverB1(inventario, cantidadActual, "Teclado Mech");
    
    return 0;
}


// De aca para abajo es lo importante
void resolverB1(Producto arr[], int len, string nombre){
    int pos = buscar(arr, len, nombre);
    if (pos == -1) {
        cout << "Producto no encontrado." << endl;
    } else {
        mostrarDatosYValidarStock(arr[pos]);
        informarCantProductosMayor(arr, len, arr[pos].precio);
    }
}

// (a) Permitir buscar un producto por nombre
int buscar(Producto arr[], int len, string nombre) {
    for (int i = 0; i < len; i++) {
        if(arr[i].nombre == nombre) {
            return i; // Devuelve el índice donde lo encontró
        }
    }
    return -1; // Si sale del ciclo, no existía
}

// (b) Mostrar sus datos e indicar si el stock es bajo (< 5 unidades)
void mostrarDatosYValidarStock(Producto producto) {
    cout << "\n=== Datos del Producto ===" << endl;
    cout << "Nombre: " << producto.nombre << endl;
    cout << "Precio: $" << producto.precio << endl;
    cout << "Stock actual: " << producto.stock << " unidades." << endl;
    
    if(producto.stock < 5){
        cout << "[ALERTA]: El stock es bajo (menor a 5 unidades)." << endl;
    }
}

// (c) Informar cuántos productos tienen precio mayor al encontrado
void informarCantProductosMayor(Producto arr[], int len, float precio) {
    int cont = 0;
    
    for (int i = 0; i < len; i++) {
        if(arr[i].precio > precio) {
            cont++;
        }
    }
    
    cout << "Cantidad de productos con mayor precio: " << cont << endl;
}