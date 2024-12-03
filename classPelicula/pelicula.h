//
// Created by Jordinn on 30/11/2024.
//

#ifndef PELICULA_H
#define PELICULA_H

#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <string>
using namespace std;


class pelicula {
private:
    string id;
    string titulo;
    string sinopsis;
    unordered_set<string> tags;
    string fuente;
    bool like = false;
    bool verMasTarde = false;
public:
    pelicula() = default;
    pelicula(string id_, string titulo_, string sinopsis_, unordered_set<string> tags_, string fuente_) : id(move(id_)),
    titulo(titulo_), sinopsis(sinopsis_), tags(tags_), fuente(fuente_) {}


    const string& getId() const { return id; }
    const string& getTitulo() const { return titulo; }
    const string& getSinopsis() const { return sinopsis; }
    const unordered_set<string>& getTags() const { return tags; }
    const string& getFuente() const { return fuente; }
    const bool& getLike() const {return like;}
    void mostrarDetallesPelicula() const;


    void configurarPropiedades(
        const string& id_,
        string titulo_,
        string sinopsis_,
        unordered_set<string> tags_,
        const string& fuente_
    ) {

        if (id_.empty()) {
            throw invalid_argument("El id de la pelicula  está vacio");
        }
        id = id_;


        if (titulo_.empty()) {
            throw invalid_argument("El titulo de la pelicula está vacio");
        } else { titulo_.erase(std::remove_if(titulo_.begin(), titulo_.end(),
                                   [](unsigned char c) { return std::isspace(c) && c != ' '; }), titulo_.end());}
        titulo = move(titulo_);

        // Asignación de sinopsis (sin validaciones adicionales)
        sinopsis = sinopsis_;

        for (auto& tag : tags_) {
            if (tag.empty()) {
                throw invalid_argument("El tag se encuentra vacio");
            }
        }
        tags = std::move(tags_);

        // Asignación de fuente (sin validaciones adicionales)
        fuente = fuente_;
    }
};



#endif //PELICULA_H
