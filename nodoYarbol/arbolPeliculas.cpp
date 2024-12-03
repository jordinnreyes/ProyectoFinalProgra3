//
// Created by Jordinn on 30/11/2024.
//

#include "arbolPeliculas.h"

// Constructor
ArbolPeliculas::ArbolPeliculas() : raiz(nullptr) {}

// Destructor
ArbolPeliculas::~ArbolPeliculas() {
    // Liberar memoria (pendiente si es necesario)
}

// Método para insertar nodos en el árbol
void ArbolPeliculas::insertar(const pelicula& data) {
    Nodo* nuevo = new Nodo(data);
    if (raiz == nullptr) {
        raiz = nuevo;
    } else {
        Nodo* actual = raiz;
        Nodo* padre = nullptr;
        while (actual != nullptr) {
            padre = actual;
            if (data.getTitulo() < actual->getData().getTitulo()) {
                actual = actual->getLeft();
            } else {
                actual = actual->getRight();
            }
        }
        if (data.getTitulo() < padre->getData().getTitulo()) {
            padre->setLeft(nuevo);
        } else {
            padre->setRight(nuevo);
        }
    }
}

// Método para buscar nodos por título
Nodo* ArbolPeliculas::buscar(const string& titulo) const {
    Nodo* actual = raiz;
    while (actual != nullptr) {
        if (titulo == actual->getData().getTitulo()) {
            return actual;
        } else if (titulo < actual->getData().getTitulo()) {
            actual = actual->getLeft();
        } else {
            actual = actual->getRight();
        }
    }
    return nullptr;
}

// Iterator
ArbolPeliculas::Iterator::Iterator(Nodo* raiz) {
    if (raiz) {
        nodos.push(raiz);
    }
}

bool ArbolPeliculas::Iterator::hasNext() const {
    return !nodos.empty();
}

Nodo* ArbolPeliculas::Iterator::next() {
    if (nodos.empty()) {
        return nullptr;
    }
    Nodo* actual = nodos.front();
    nodos.pop();
    if (actual->getLeft()) {
        nodos.push(actual->getLeft());
    }
    if (actual->getRight()) {
        nodos.push(actual->getRight());
    }
    return actual;
}

ArbolPeliculas::Iterator ArbolPeliculas::crearIterator() {
    return Iterator(raiz);
}
