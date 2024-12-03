//
// Created by Jordinn on 30/11/2024.
//

#ifndef NODO_H
#define NODO_H

#include <unordered_map>
#include <vector>
#include "../classPelicula/pelicula.h"

using namespace std;

class Nodo {
private:
    char caracter;
    unordered_map<char, Nodo*> hijos;
    vector<pelicula> peliculas;

public:
    Nodo(char caracter) : caracter(caracter) {}

    char getCaracter() const;
    Nodo* getHijo(char c) const;
    void agregarHijo(char c);
    void agregarPelicula(const pelicula& peli);
    const vector<pelicula>& getPeliculas() const;

    // Destructor
    ~Nodo();
};

#endif //NODO_H