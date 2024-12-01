//
// Created by Jordinn on 30/11/2024.
//

#ifndef ARBOLPELICULAS_H
#define ARBOLPELICULAS_H

#include "nodo.h"
#include <queue>

class ArbolPeliculas {
private:
    Nodo* raiz;

public:
    // Constructor
    ArbolPeliculas();

    // Destructor
    ~ArbolPeliculas();

    // Métodos para el manejo del árbol
    void insertar(const string& title, const string& plotSynopsis, const vector<string>& tags);
    Nodo* buscar(const string& title) const;

    // Método para recorrer el árbol usando Iterator
    class Iterator {
    private:
        queue<Nodo*> nodos;
    public:
        Iterator(Nodo* raiz);
        bool hasNext() const;
        Nodo* next();
    };

    Iterator crearIterator();
};

#endif //ARBOLPELICULAS_H