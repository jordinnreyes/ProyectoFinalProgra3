

#include "nodo.h"

// Métodos existentes
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

// Metodo para devolver todos los hijos
const unordered_map<char, Nodo*>& Nodo::getHijos() const {
    return hijos;
}

// Destructor
Nodo::~Nodo() {
    for (auto& [_, hijo] : hijos) {
        delete hijo;
    }
}
