// Ejercicio 2 — Edición in situ
// Sobre empleados.dat (legajo, nombre, sueldo), aplicá un aumento del 15% al sueldo del
// empleado cuyo legajo se ingresa por teclado. No regeneres el archivo: modificá solo ese
// registro.

// Preguntas guía:
// 1. ¿En qué modo abrís el archivo y por qué no sirve "rb"?
// Se abre en rb+ porque necesitamos leer y escribir en el archivo sin borrarlo. Si usamos rb normal
// podriamos leer pero no escribir, y si usamos wb+ se borraría el contenido existente.

// 2. Después de leer el registro con fread, ¿dónde quedó el puntero? ¿Cuántos bytes
// retrocedés antes de grabar?
// Cuando el fread lee un registro, el puntero avanza automáticamente al inicio del siguiente 
// registro. Queda posicionado justo después del empleado que acabamos de subir a la memoria RAM.
// Por eso, para sobreescribir a ese mismo empleado, tenés que ir "marcha atrás". ¿Cuánto? 
// Exactamente el peso en memoria de un registro completo. Por eso se usa fseek(..., -sizeof(Empleado), SEEK_CUR).

// 3. ¿Qué hacés (y qué le informás al usuario) si el legajo no existe?
// Si el bucle lee todo el archivo y nunca entra al if donde el legajo coincide, la variable booleana encontrado 
// va a seguir valiendo false. Al cerrar el archivo, verificás eso y le imprimís por 
// consola: "Error: El legajo [X] no existe"

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

struct Empleado {
    int legajo;
    char nombre[50]; // IMPORTANTE: Usar char array para archivos binarios
    float sueldo;
};

void inicializarArchivoHardcodeado();

int main() {
    inicializarArchivoHardcodeado();

    FILE* archivo = fopen("empleados.dat", "rb+");
    if (archivo == NULL) {
        cout << "No se pudo abrir el archivo." << endl;
        return 1;
    }

    int legajoBuscado;
    cout << "Ingrese el legajo del empleado a modificar: ";
    cin >> legajoBuscado;

    Empleado emp;
    bool encontrado = false;

    // Corta si llega al final del archivo o si 'encontrado' se vuelve true
    while (!encontrado && fread(&emp, sizeof(Empleado), 1, archivo) == 1) {
        
        if (emp.legajo == legajoBuscado) {
            encontrado = true; // Levantamos la bandera para salir del while

            // Calculamos el nuevo sueldo (+15%)
            emp.sueldo = emp.sueldo * 1.15;

            // Retrocedemos el puntero exactamente el tamaño de 1 registro
            fseek(archivo, -(sizeof(Empleado)), SEEK_CUR);

            // Sobreescribimos el registro actualizado
            fwrite(&emp, sizeof(Empleado), 1, archivo);

            cout << "-----------------------------------" << endl;
            cout << "Empleado modificado con exito." << endl;
            cout << "Nombre: " << emp.nombre << endl;
            cout << "Nuevo Sueldo: $" << emp.sueldo << endl;
            cout << "-----------------------------------" << endl;
        }
    }

    fclose(archivo);

    // Si el bucle terminó y nunca cambió la bandera, el legajo no estaba
    if (!encontrado) {
        cout << "Error: El legajo " << legajoBuscado << " no existe." << endl;
    }

    return 0;
}

// Implementación de la función para generar el archivo de prueba
void inicializarArchivoHardcodeado() {
    FILE* archivo = fopen("empleados.dat", "wb"); 
    
    if (archivo == NULL) {
        cout << "Error al crear el archivo inicial." << endl;
        return;
    }

    Empleado empleadosDePrueba[] = {
        {101, "Ana Gonzalez", 100000.0},
        {102, "Bruno Diaz",   150000.0},
        {103, "Carla Lopez",  120000.0}
    };

    fwrite(empleadosDePrueba, sizeof(Empleado), 3, archivo);
    
    fclose(archivo);
    cout << "[Sistema] Archivo 'empleados.dat' inicializado/reseteado con datos de prueba." << endl;
    cout << "Legajos disponibles: 101, 102, 103" << endl;
    cout << "=======================================================================" << endl;
}