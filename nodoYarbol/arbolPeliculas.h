//
// Created by Jordinn on 30/11/2024.
//

#ifndef ARBOLPELICULAS_H
#define ARBOLPELICULAS_H

#include "nodo.h"

using namespace std;

class ArbolPeliculas {
private:
    Nodo* raiz;

public:
    // Constructor
    ArbolPeliculas();

    // Métodos
    void insertar(const pelicula& peli);
    vector<pelicula> buscar(const string& titulo) const;

    // Metodo para devolver la raíz
    Nodo* getRaiz() const;

    // Destructor
    ~ArbolPeliculas();
};

#endif // ARBOLPELICULAS_H