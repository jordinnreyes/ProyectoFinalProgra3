//
// Created by Fernando on 3/12/2024.
//

#ifndef BUSQUEDA_H
#define BUSQUEDA_H

#include "../nodoYarbol/arbolPeliculas.h"
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>

using namespace std;

class Busqueda {
private:
    ArbolPeliculas* arbol;  // Referencia al árbol de prefijos

    // Métodos privados para búsquedas
    void dfs(Nodo* nodo, const string& termino, vector<pelicula>& resultados, bool buscarSubstring) const;
    void buscarEnTexto(const pelicula& peli, const string& termino, vector<pelicula>& resultados, bool buscarSubstring) const;

public:
    // Constructor
    explicit Busqueda(ArbolPeliculas* arbol);

    // Métodos públicos para búsquedas
    vector<pelicula> buscarPorPalabra(const string& palabra) const;
    vector<pelicula> buscarPorFrase(const string& frase) const;
    vector<pelicula> buscarPorString(const string& substring) const;
    vector<pelicula> buscarPorTag(const string& tag) const;

    // Mostrar resultados
    void mostrarResultados(const vector<pelicula>& resultados) const;
    int contarCoincidencias(const pelicula& peli, const string& termino)const;
    vector<pelicula> obtenerTop5PeliculasPorCoincidencias(vector<pelicula>& peliculas, const string& termino) const;
};

#endif // BUSQUEDA_H