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
    ArbolPeliculas();

    void insertar(const pelicula& peli);
    vector<pelicula> buscar(const string& titulo) const;

    ~ArbolPeliculas();
};

#endif //ARBOLPELICULAS_H