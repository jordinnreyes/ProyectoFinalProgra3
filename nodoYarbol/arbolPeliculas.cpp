//
// Created by Jordinn on 30/11/2024.
//

#include "arbolPeliculas.h"

using namespace std;

ArbolPeliculas::ArbolPeliculas() : raiz(new Nodo('\0')) {}

void ArbolPeliculas::insertar(const pelicula& peli) {
    Nodo* actual = raiz;
    for (char c : peli.getTitulo()) {
        actual->agregarHijo(c);
        actual = actual->getHijo(c);
    }
    actual->agregarPelicula(peli);
}

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

ArbolPeliculas::~ArbolPeliculas() {
    delete raiz;
}