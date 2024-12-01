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

    // Métodos para manejar el árbol
    void insertar(const pelicula& data);
    Nodo* buscar(const string& titulo) const;

    // Iterator para recorrer el árbol
    class Iterator {
    private:
        queue<Nodo*> nodos;

    public:
        explicit Iterator(Nodo* raiz);
        bool hasNext() const;
        Nodo* next();
    };

    Iterator crearIterator();
};




#endif //ARBOLPELICULAS_H
