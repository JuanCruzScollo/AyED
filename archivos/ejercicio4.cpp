// Ejercicio 4 — Apareo con claves coincidentes
// Dos depósitos tienen su stock en depo1.dat y depo2.dat (código, cantidad), ambos ordenados
// por código. Generá unificado.dat ordenado por código; si un código aparece en ambos
// depósitos, sumá las cantidades en un único registro.
// Preguntas guía:

// 1. ¿Cuántas ramas tiene la comparación en este caso (menor, mayor, igual)? ¿Qué hacés
// en la rama de igualdad?

// Tiene 3 ramas:
// A < B: Grabás el registro de A en el archivo nuevo y avanzás solo la lectura de A.
// A > B: Grabás el registro de B en el archivo nuevo y avanzás solo la lectura de B.
// A == B: (Acá está la magia de este ejercicio). Como el código está en ambos depósitos, 
// sumás las dos cantidades y grabás un único registro con ese total.

// 2. Cuando uno de los archivos se agota, ¿cómo procesás lo que queda en el otro?

// Con dos bucles while individuales al final. Vas a tener un while (leidoA == 1) para volcar todo 
// lo que haya sobrado del depósito 1, y un while (leidoB == 1) para volcar lo del depósito 2. 

// 3. ¿Por qué este problema NO requiere ninguna búsqueda?
// Porque ambos archivos ya están ordenados por la misma clave (el codigo del producto).

#include <iostream>
#include <cstdio>

using namespace std;

struct Producto {
    int codigo;
    int cantidad;
};

void inicializarDepositos();
void unificarStock(const char* archA, const char* archB, const char* archC);
void mostrarUnificado(const char* nombreArchivo);

int main() {
    inicializarDepositos();

    cout << "Realizando el apareo de archivos..." << endl;
    unificarStock("depo1.dat", "depo2.dat", "unificado.dat");

    cout << "\n=== STOCK UNIFICADO ===" << endl;
    mostrarUnificado("unificado.dat");

    return 0;
}

// Patrón algorítmico de Apareo con 3 ramas
void unificarStock(const char* nomA, const char* nomB, const char* nomC) {
    // Abrimos los dos orígenes en lectura y el destino en escritura
    FILE* depo1 = fopen(nomA, "rb");
    FILE* depo2 = fopen(nomB, "rb");
    FILE* uni = fopen(nomC, "wb");

    if (depo1 == NULL || depo2 == NULL || uni == NULL) {
        cout << "Error abriendo los archivos." << endl;
        return;
    }

    Producto pa, pb;
    
    int leidoA = fread(&pa, sizeof(Producto), 1, depo1);
    int leidoB = fread(&pb, sizeof(Producto), 1, depo2);

    // Comparamos mientras HAYA DATOS EN AMBOS [cite: 259, 260]
    while (leidoA == 1 && leidoB == 1) {
        if (pa.codigo < pb.codigo) {
            // El menor es A: grabamos A y avanzamos A 
            fwrite(&pa, sizeof(Producto), 1, uni);
            leidoA = fread(&pa, sizeof(Producto), 1, depo1);
        } 
        else if (pa.codigo > pb.codigo) {
            // El menor es B: grabamos B y avanzamos B
            fwrite(&pb, sizeof(Producto), 1, uni);
            leidoB = fread(&pb, sizeof(Producto), 1, depo2);
        } 
        else {
            // SON IGUALES: sumamos cantidades, grabamos y avanzamos AMBOS 
            Producto pUnificado;
            pUnificado.codigo = pa.codigo;
            pUnificado.cantidad = pa.cantidad + pb.cantidad;
            
            fwrite(&pUnificado, sizeof(Producto), 1, uni);
            
            leidoA = fread(&pa, sizeof(Producto), 1, depo1);
            leidoB = fread(&pb, sizeof(Producto), 1, depo2);
        }
    }

    // Volcamos el remanente del Deposito 1 (si quedó algo)
    while (leidoA == 1) {
        fwrite(&pa, sizeof(Producto), 1, uni);
        leidoA = fread(&pa, sizeof(Producto), 1, depo1);
    }

    // Volcamos el remanente del Deposito 2 (si quedó algo)
    while (leidoB == 1) {
        fwrite(&pb, sizeof(Producto), 1, uni);
        leidoB = fread(&pb, sizeof(Producto), 1, depo2);
    }

    fclose(depo1);
    fclose(depo2);
    fclose(uni);
}


// Funciones auxiliares para poder probar el programa
void inicializarDepositos() {
    FILE* depo1 = fopen("depo1.dat", "wb");
    FILE* depo2 = fopen("depo2.dat", "wb");
    
    if (depo1 != NULL) {
        // Códigos en Depo 1: 101, 105, 110
        Producto p1[] = {{101, 50}, {105, 20}, {110, 30}};
        fwrite(p1, sizeof(Producto), 3, depo1);
        fclose(depo1);
    }
    
    if (depo2 != NULL) {
        // Códigos en Depo 2: 105, 108, 110, 115
        // Notar que 105 y 110 están en AMBOS depósitos
        Producto p2[] = {{105, 15}, {108, 40}, {110, 10}, {115, 60}};
        fwrite(p2, sizeof(Producto), 4, depo2);
        fclose(depo2);
    }
}

void mostrarUnificado(const char* nombreArchivo) {
    FILE* f = fopen(nombreArchivo, "rb");
    if (f == NULL) return;

    Producto p;
    while (fread(&p, sizeof(Producto), 1, f) == 1) {
        cout << "Codigo: " << p.codigo << " | Cantidad total: " << p.cantidad << endl;
    }
    
    fclose(f);
}