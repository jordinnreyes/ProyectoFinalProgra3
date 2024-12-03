#include <iostream>
#include "classPelicula/procesarCsv.cpp"  // Para leer y procesar el CSV
#include "nodoYarbol/arbolPeliculas.h"  // Para manejar el árbol de prefijos

using namespace std;

int main() {
    cout << "Bienvenido a nuestro servicio de Streaming!" << endl;

    // Crear una instancia de LecturaDatos para procesar el archivo CSV
    LecturaDatos lector;

    // Ruta del archivo CSV
    string archivoCsv = "C:/Users/Fernando/Downloads/mpst_full_data.csv";

    // Leer datos desde el CSV
    lector.leerDatosDelCsv(archivoCsv);

    // Crear el árbol de prefijos
    ArbolPeliculas arbol;

    // Insertar las películas en el árbol
    const auto& peliculas = lector.getPeliculas();  // Obtener las películas leídas
    for (const auto& [id, peli] : peliculas) {
        arbol.insertar(peli);  // Insertar cada película en el árbol
    }

    // Mostrar películas cargadas
    cout << "\nPeliculas cargadas en el arbol:\n";
    for (const auto& [id, peli] : peliculas) {
        cout << "ID: " << id << ", Título: " << peli.getTitulo() << endl;
    }

    // Probar búsqueda
    cout << "\nIngrese el titulo de una pelicula para buscar: ";
    string tituloBusqueda;
    getline(cin, tituloBusqueda);

    vector<pelicula> resultados = arbol.buscar(tituloBusqueda);
    if (!resultados.empty()) {
        cout << "\nPeliculas encontradas:\n";
        for (const auto& peli : resultados) {
            cout << "Titulo: " << peli.getTitulo() << endl;
            cout << "Sinopsis: " << peli.getSinopsis() << endl;
            cout << "-----------------------" << endl;
        }
    } else {
        cout << "\nNo se encontro ninguna pelicula con el título: " << tituloBusqueda << endl;
    }

    return 0;
}