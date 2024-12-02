#include "pelicula.h"

void pelicula::mostrarDetallesPelicula() const {
    cout << "Detalles de la película:" << endl;
    cout << "Título: " << titulo << endl;
    cout << "Sinopsis: " << sinopsis << endl;

    cout << "Opciones disponibles:" << endl;
    cout << "1. Like" << endl;
    cout << "2. Ver más tarde" << endl;

    int opcion;
    cout << "Seleccione una opción (1 o 2, o cualquier otra tecla para salir): ";
    cin >> opcion;

    auto self = const_cast<pelicula*>(this);

    if (opcion == 1) {
        self->like = true;
        cout << "Has marcado esta película con Like." << endl;
    } else if (opcion == 2) {
        self->verMasTarde = true;
        cout << "Has añadido esta película a Ver más tarde." << endl;
    } else {
        cout << "No se realizó ninguna acción." << endl;
    }
}
