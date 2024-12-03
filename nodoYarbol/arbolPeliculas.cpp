//
// Created by Jordinn on 30/11/2024.
//

#include "arbolPeliculas.h"

// Constructor
ArbolPeliculas::ArbolPeliculas() : raiz(new Nodo('\0')) {}

// Metodo para insertar nodos en el árbol
void ArbolPeliculas::insertar(const pelicula& peli) {
    Nodo* actual = raiz;
    for (char c : peli.getTitulo()) {
        actual->agregarHijo(c);
        actual = actual->getHijo(c);
    }
    actual->agregarPelicula(peli);
}

// Metodo para buscar películas por título
vector<pelicula> ArbolPeliculas::buscar(const string& titulo) const {
    Nodo* actual = raiz;
    for (char c : titulo) {
        actual = actual->getHijo(c);
        if (actual == nullptr) {
            return {};
        }
    }
    return actual->getPeliculas();
}

// Metodo para devolver la raíz
Nodo* ArbolPeliculas::getRaiz() const {
    return raiz;
}

// Destructor
ArbolPeliculas::~ArbolPeliculas() {
    delete raiz;
}