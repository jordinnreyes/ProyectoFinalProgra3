//
// Created by Jordinn on 30/11/2024.
//

#include "arbolPeliculas.h"
#include <iostream>

// Constructor
ArbolPeliculas::ArbolPeliculas() : raiz(nullptr) {}

// Destructor
ArbolPeliculas::~ArbolPeliculas() {
    // Liberar memoria de forma recursiva (pendiente si es necesario)
}

// Método para insertar nodos en el árbol
void ArbolPeliculas::insertar(const string& title, const string& plotSynopsis, const vector<string>& tags) {
    Nodo* nuevo = new Nodo(title, plotSynopsis, tags);
    if (raiz == nullptr) {
        raiz = nuevo;
    } else {
        Nodo* actual = raiz;
        Nodo* padre = nullptr;
        while (actual != nullptr) {
            padre = actual;
            if (title < actual->getTitle()) {
                actual = actual->getLeft();
            } else {
                actual = actual->getRight();
            }
        }
        if (title < padre->getTitle()) {
            padre->setLeft(nuevo);
        } else {
            padre->setRight(nuevo);
        }
    }
}

// Método para buscar un nodo por título
Nodo* ArbolPeliculas::buscar(const string& title) const {
    Nodo* actual = raiz;
    while (actual != nullptr) {
        if (title == actual->getTitle()) {
            return actual;
        } else if (title < actual->getTitle()) {
            actual = actual->getLeft();
        } else {
            actual = actual->getRight();
        }
    }
    return nullptr;
}

// Implementación del Iterator
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