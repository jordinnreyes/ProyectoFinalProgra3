//
// Created by Jordinn on 30/11/2024.
//

#ifndef NODO_H
#define NODO_H

#include <string>
#include <vector>

using namespace std;

class Nodo {
private:
    string title;          // Título de la película
    string plotSynopsis;   // Sinopsis de la película
    vector<string> tags;   // Tags asociados a la película
    Nodo* left;            // Nodo hijo izquierdo
    Nodo* right;           // Nodo hijo derecho

public:
    // Constructor
    Nodo(const string& title, const string& plotSynopsis, const vector<string>& tags);

    // Getters
    string getTitle() const;
    string getPlotSynopsis() const;
    vector<string> getTags() const;
    Nodo* getLeft() const;
    Nodo* getRight() const;

    // Setters
    void setLeft(Nodo* left);
    void setRight(Nodo* right);
};

#endif //NODO_H