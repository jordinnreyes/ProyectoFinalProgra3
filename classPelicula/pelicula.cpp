#include "pelicula.h"
#include <iostream>
#include <algorithm>
#include <unordered_set>

using namespace std;

/*
void pelicula::mostrarDetallesPelicula() {
    cout << "\nDetalles de la película seleccionada:\n";
    cout << "Título: " << titulo << "\n";
    cout << "Sinopsis: " << sinopsis << "\n";
    cout << "Fuente: " << fuente << "\n";

    // Mostrar los tags
    cout << "Tags: ";
    for (const auto& tag : tags) {
        cout << tag << ", ";
    }
    cout << "\n\nOpciones disponibles:\n";
    cout << "1. Like\n";
    cout << "2. Ver más tarde\n";
    cout << "3. Volver al menú principal\n";

    int opcion;
    cin >> opcion;
    cin.ignore();

    switch (opcion) {
        case 1:
            self ->like = true;
            cout << "Has marcado la película como 'Like'.\n";
            break;
        case 2:
            verMasTarde = true;
            cout << "Has añadido la película a 'Ver más tarde'.\n";
            break;
        case 3:
            cout << "Regresando al menú principal...\n";
            break;
        default:
            cout << "Opción no válida. Intenta nuevamente.\n";
    }
}
 */

bool pelicula::tieneTagsComunes(const pelicula& otra) const {
    for (const auto& tag : tags) {
        if (otra.getTags().find(tag) != otra.getTags().end()) {
            return true;
        }
    }
    return false;
}
