//
// Created by Jordinn on 30/11/2024.
//

#ifndef NODO_H
#define NODO_H



#include "../classPelicula/pelicula.h"

class Nodo {
private:
    pelicula data;  // Objeto de la clase pelicula
    Nodo* left;     // Nodo hijo izquierdo
    Nodo* right;    // Nodo hijo derecho

public:
    // Constructor
    explicit Nodo(const pelicula& data);

    // Getters
    const pelicula& getData() const;
    Nodo* getLeft() const;
    Nodo* getRight() const;

    // Setters
    void setLeft(Nodo* left);
    void setRight(Nodo* right);
};



#endif //NODO_H
