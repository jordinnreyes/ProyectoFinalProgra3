#include <iostream>
#include "classPelicula/procesarCsv.cpp"
#include "nodoYarbol/arbolPeliculas.h"
#include "classBusqueda/busqueda.h"

using namespace std;

int main() {
    cout << "Bienvenido!" << endl;
    cout << "Porfavor espera, estamos cargando el streaming!" << endl;

    // Crear una instancia de LecturaDatos para procesar el archivo CSV
    LecturaDatos lector;

    // Ruta del archivo CSV
    string archivoCsv = "C:/Users/Isaac/Downloads/mpst_full_data.csv";

    // Leer datos desde el CSV
    lector.leerDatosDelCsv2(archivoCsv);

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

        vector<pelicula> verMasTarde;
        vector<pelicula> peliculasLike;

        // Mostrar "Ver más tarde"
        cout << "\nPeliculas en 'Ver mas tarde':\n";
        for (const auto& peli : verMasTarde) {
            cout << "- " << peli.getTitulo() << endl;
        }

        cout << "\nPeliculas similares a las que te gustaron:\n";
        for (const auto& peliLike : peliculasLike) {
            for (const auto& [id, peli] : peliculas) {
                if (peliLike.tieneTagsComunes(peli) && peliLike.getId() != peli.getId()) {
                    cout << "- " << peli.getTitulo() << " (similar a " << peliLike.getTitulo() << ")" << endl;
                }
            }
        }

        cout << "\nSeleccione una opcion:\n";
        cout << "1. Buscar por palabra\n";
        cout << "2. Buscar por frase\n";
        cout << "3. Buscar por string\n";
        //cout << "4. Buscar por tag\n";a
        cout << "5. Salir\n";
        cout << "Opcion:";
        cin >> opcion;
        cin.ignore();  // Ignorar el salto de línea después del número

        string termino;
        string opcion2;
        vector<pelicula> resultados;
        vector<pelicula> resultados5primeros;


        switch (opcion) {
            case 1:
                cout << "Ingrese la palabra para buscar:";
                getline(cin, termino);
                resultados = busqueda.buscarPorPalabra(termino);
                resultados5primeros = busqueda.obtenerTop5PeliculasPorCoincidencias(resultados,termino);
                cout << "Esta son las 5 primeras peliculas recomendadas";
                busqueda.mostrarResultados(resultados5primeros);
                cout << "Desea ver mas resultados? (Si/No)";
                getline(cin,opcion2);
                if (opcion2 == "Si")
                    busqueda.mostrarResultados(resultados);
                else busqueda.mostrarResultados(resultados5primeros);
                break;

            case 2:
                cout << "Ingrese la frase para buscar:";
                getline(cin, termino);
                resultados = busqueda.buscarPorFrase(termino);
                resultados5primeros = busqueda.obtenerTop5PeliculasPorCoincidencias(resultados,termino);
                cout << "Esta son las 5 primeras peliculas recomendadas";
                busqueda.mostrarResultados(resultados5primeros);
                cout << "Desea ver mas resultados? (Si/No)";
                getline(cin,opcion2);
                if (opcion2 == "Si")
                busqueda.mostrarResultados(resultados);
                else busqueda.mostrarResultados(resultados5primeros);
                break;

            case 3:
                cout << "Ingrese el string para buscar:";
                getline(cin, termino);
                resultados = busqueda.buscarPorString(termino);
                resultados5primeros = busqueda.obtenerTop5PeliculasPorCoincidencias(resultados,termino);
                cout << "Esta son las 5 primeras peliculas recomendadas";
                busqueda.mostrarResultados(resultados5primeros);
                cout << "Desea ver mas resultados? (Si/No)";
                getline(cin,opcion2);
                if (opcion2 == "Si")
                    busqueda.mostrarResultados(resultados);
                else busqueda.mostrarResultados(resultados5primeros);
                break;
/*
            case 4:
                cout << "Ingrese el tag para buscar:";
                getline(cin, termino);
                resultados = busqueda.buscarPorTag(termino);
                busqueda.mostrarResultados(resultados);
                break;
*/
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