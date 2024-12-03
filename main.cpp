#include <iostream>
#include "classPelicula/procesarCsv.cpp"
#include "nodoYarbol/arbolPeliculas.h"
#include "classBusqueda/busqueda.h"

using namespace std;

int main() {
    cout << "Bienvenido!" << endl;

    // Crear una instancia de LecturaDatos para procesar el archivo CSV
    LecturaDatos lector;

    // Ruta del archivo CSV
    string archivoCsv = "C:/Users/Fernando/Downloads/pruebaa.csv";

    // Leer datos desde el CSV
    lector.leerDatosDelCsv(archivoCsv);

    // Crear el árbol de prefijos
    ArbolPeliculas arbol;

    // Insertar las películas en el árbol
    const auto& peliculas = lector.getPeliculas();
    for (const auto& [id, peli] : peliculas) {
        arbol.insertar(peli);
    }

    // Crear la instancia de Busqueda
    Busqueda busqueda(&arbol);

    // Menú interactivo
    int opcion;
    do {
        cout << "\nSeleccione una opcion:\n";
        cout << "1. Buscar por palabra\n";
        cout << "2. Buscar por frase\n";
        cout << "3. Buscar por string\n";
        cout << "4. Buscar por tag\n";
        cout << "5. Salir\n";
        cout << "Opcion:";
        cin >> opcion;
        cin.ignore();  // Ignorar el salto de línea después del número

        string termino;
        vector<pelicula> resultados;

        switch (opcion) {
            case 1:
                cout << "Ingrese la palabra para buscar:";
                getline(cin, termino);
                resultados = busqueda.buscarPorPalabra(termino);
                busqueda.mostrarResultados(resultados);
                break;

            case 2:
                cout << "Ingrese la frase para buscar:";
                getline(cin, termino);
                resultados = busqueda.buscarPorFrase(termino);
                busqueda.mostrarResultados(resultados);
                break;

            case 3:
                cout << "Ingrese el string para buscar:";
                getline(cin, termino);
                resultados = busqueda.buscarPorString(termino);
                busqueda.mostrarResultados(resultados);
                break;

            case 4:
                cout << "Ingrese el tag para buscar:";
                getline(cin, termino);
                resultados = busqueda.buscarPorTag(termino);
                busqueda.mostrarResultados(resultados);
                break;

            case 5:
                cout << "Gracias por usar la plataforma. ¡Hasta pronto!\n";
                break;

            default:
                cout << "Opcion no valida. Intentelo nuevamente.\n";
                break;
        }
    } while (opcion != 5);

    return 0;
}