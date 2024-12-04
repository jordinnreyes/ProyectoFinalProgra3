//
// Created by Fernando on 3/12/2024.
//

#include "busqueda.h"
#include <iostream>

// Constructor
Busqueda::Busqueda(ArbolPeliculas* arbol) : arbol(arbol) {}

// Metodo para buscar en el texto (título y sinopsis)
void Busqueda::buscarEnTexto(const pelicula& peli, const string& termino, vector<pelicula>& resultados, bool buscarSubstring) const {
    string titulo = peli.getTitulo();
    string sinopsis = peli.getSinopsis();

    int coincidencias = 0;

    if (buscarSubstring) {
        if (titulo.find(termino) != string::npos || sinopsis.find(termino) != string::npos) {
            resultados.push_back(peli);
        }
    } else {
        size_t posTitulo = titulo.find(termino);
        size_t posSinopsis = sinopsis.find(termino);
        if ((posTitulo != string::npos && (posTitulo == 0 || titulo[posTitulo - 1] == ' ')) ||
            (posSinopsis != string::npos && (posSinopsis == 0 || sinopsis[posSinopsis - 1] == ' '))) {
            resultados.push_back(peli);
        }
    }
}

// Metodo DFS para buscar por palabra, frase o string
void Busqueda::dfs(Nodo* nodo, const string& termino, vector<pelicula>& resultados, bool buscarSubstring) const {
    if (nodo == nullptr) return;

    // Revisar películas en el nodo actual
    const vector<pelicula>& peliculasNodo = nodo->getPeliculas();
    for (const auto& peli : peliculasNodo) {
        buscarEnTexto(peli, termino, resultados, buscarSubstring);
    }

    // Continuar DFS con los hijos
    for (auto& [_, hijo] : nodo->getHijos()) {
        dfs(hijo, termino, resultados, buscarSubstring);
    }
}

// Búsqueda por palabra
vector<pelicula> Busqueda::buscarPorPalabra(const string& palabra) const {
    vector<pelicula> resultados;
    dfs(arbol->getRaiz(), palabra, resultados, false);
    return resultados;
}


// contarCoincidencias: Cuenta la cantidad de coincidencias de un término en el título, sinopsis y tags de una película
int Busqueda::contarCoincidencias(const pelicula& peli, const string& termino)const {
    int coincidencias = 0;
    string titulo = peli.getTitulo();
    string sinopsis = peli.getSinopsis();
    unordered_set<string> tags = peli.getTags(); // Suponiendo que los tags están en un unordered_set

    // Contamos las coincidencias en el título
    size_t pos = 0;
    while ((pos = titulo.find(termino, pos)) != string::npos) {
        coincidencias++;
        pos += termino.length();
    }

    // Contamos las coincidencias en la sinopsis
    pos = 0;
    while ((pos = sinopsis.find(termino, pos)) != string::npos) {
        coincidencias++;
        pos += termino.length();
    }

    // Contamos las coincidencias en los tags
    for (const string& tag : tags) {
        pos = 0;
        while ((pos = tag.find(termino, pos)) != string::npos) {
            coincidencias++;
            pos += termino.length();
        }
    }

    return coincidencias;
}


vector<pelicula> Busqueda::obtenerTop5PeliculasPorCoincidencias(vector<pelicula>& peliculas, const string& termino) const {
    // Si el vector tiene menos de 5 películas, no hacemos nada
    if (peliculas.size() <= 5) {
        return peliculas;
    }

    // Ordenamos el vector por la cantidad de coincidencias (de mayor a menor)
    sort(peliculas.begin(), peliculas.end(), [this, &termino](const pelicula& a, const pelicula& b) {
        // Capturamos 'this' para poder acceder a la función miembro contarCoincidencias
        return contarCoincidencias(a, termino) > contarCoincidencias(b, termino);
    });

    // Devolvemos solo las 5 primeras películas con más coincidencias
    peliculas.resize(5);

    return peliculas;
}





// Búsqueda por frase
vector<pelicula> Busqueda::buscarPorFrase(const string& frase) const {
    vector<pelicula> resultados;
    dfs(arbol->getRaiz(), frase, resultados, false);
    return resultados;
}

// Búsqueda por string
vector<pelicula> Busqueda::buscarPorString(const string& substring) const {
    vector<pelicula> resultados;
    dfs(arbol->getRaiz(), substring, resultados, true);
    return resultados;
}

// Búsqueda por tag (BFS)
vector<pelicula> Busqueda::buscarPorTag(const string& tag) const {
    vector<pelicula> resultados;
    queue<Nodo*> nodos;
    nodos.push(arbol->getRaiz());

    while (!nodos.empty()) {
        Nodo* nodo = nodos.front();
        nodos.pop();

        // Revisar películas en el nodo actual
        const vector<pelicula>& peliculasNodo = nodo->getPeliculas();
        for (const auto& peli : peliculasNodo) {
            const unordered_set<string>& tags = peli.getTags();
            if (tags.find(tag) != tags.end()) {
                resultados.push_back(peli);
            }
        }

        // Agregar hijos a la cola
        for (auto& [_, hijo] : nodo->getHijos()) {
            nodos.push(hijo);
        }
    }

    return resultados;
}





// Mostrar resultados
void Busqueda::mostrarResultados(const vector<pelicula>& resultados) const {
    if (resultados.empty()) {
        cout << "No se encontraron películas." << endl;
        return;
    }

    cout << "\nResultados de la busqueda:\n";
    for (const auto& peli : resultados) {
        cout << "Titulo: " << peli.getTitulo() << endl;
        cout << "Sinopsis: " << peli.getSinopsis() << endl;
        cout << "Tags: ";
        for (const auto& tag : peli.getTags()) {
            cout << tag << " ";
        }
        cout << "\n-----------------------" << endl;
    }
}