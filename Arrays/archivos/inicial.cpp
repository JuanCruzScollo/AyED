// Ejercicio de clase: dado un archivo binario con registros de usuarios (código y pin), 
// solicitar al usuario que ingrese su código y pin, y verificar si existe en el archivo. 
// Si existe, mostrar un mensaje de bienvenida con el código del usuario.

#include <iostream>
#include <string>

using namespace std;

struct Usuario {
    int codigo;
    int pin;
};

int main() {

    // Creamos un archivo binario con algunos usuarios para probar
    Usuario usuarios[] = {
        {101, 1234},
        {102, 5678},
        {103, 9012}
    };
    FILE* archivo = fopen("usuarios.dat", "wb"); // esto nos crea un archivo llamado usuarios.dat
    fwrite(usuarios, sizeof(Usuario), 3, archivo);
    fclose(archivo);

    // aca realizamos el ejercicio
    Usuario userFile;
    Usuario usuario;
    bool encontrado = false;

    cout << "Ingrese codigo y pin del usuario: "<< endl;
    cin >> usuario.codigo >> usuario.pin;

    archivo = fopen("usuarios.dat", "rb");

    while (fread(&userFile, sizeof(Usuario), 1, archivo) == 1) {
        if (userFile.codigo == usuario.codigo && userFile.pin == usuario.pin) {
            cout << "Usuario encontrado: " << userFile.codigo << endl;
            encontrado = true;
            break;
        }
    }

    if (!encontrado) {
        cout << "Usuario no encontrado o pin incorrecto." << endl;
    }

    fclose(archivo);
    return 0;
}


