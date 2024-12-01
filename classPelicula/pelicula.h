//
// Created by Jordinn on 30/11/2024.
//

#ifndef PELICULA_H
#define PELICULA_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;


class pelicula {
private:
    string id;
    string titulo;
    string sinopsis;
    unordered_set<string> tags;
public:
    pelicula() = default;
    pelicula(string id_, string titulo_, string sinopsis_, unordered_set<string> tags_) : id(move(id_)),
    titulo(titulo_), sinopsis(sinopsis_), tags(tags_) {}

    const string& getId() const {
        return id;
    }

    const string& getTitulo() const {
        return titulo;
    }

    const string& getSinopsis() const {
        return sinopsis;
    }

    const unordered_set<string>& getTags() const {
        return tags;
    }
};



#endif //PELICULA_H
