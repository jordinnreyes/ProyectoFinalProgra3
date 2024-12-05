
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
    // Constructor
    Nodo(char caracter) : caracter(caracter) {}

    // Métodos
    char getCaracter() const;
    Nodo* getHijo(char c) const;
    void agregarHijo(char c);
    void agregarPelicula(const pelicula& peli);
    const vector<pelicula>& getPeliculas() const;

    // Nuevo método para devolver todos los hijos
    const unordered_map<char, Nodo*>& getHijos() const;

    // Destructor
    ~Nodo();
};

#endif // NODO_H
