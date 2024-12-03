//
// Created by Jordinn on 30/11/2024.
//

#include "nodo.h"

char Nodo::getCaracter() const {
    return caracter;
}

Nodo* Nodo::getHijo(char c) const {
    auto it = hijos.find(c);
    return it != hijos.end() ? it->second : nullptr;
}

void Nodo::agregarHijo(char c) {
    if (hijos.find(c) == hijos.end()) {
        hijos[c] = new Nodo(c);
    }
}

void Nodo::agregarPelicula(const pelicula& peli) {
    peliculas.push_back(peli);
}

const vector<pelicula>& Nodo::getPeliculas() const {
    return peliculas;
}

Nodo::~Nodo() {
    for (auto& [_, hijo] : hijos) {
        delete hijo;
    }
}