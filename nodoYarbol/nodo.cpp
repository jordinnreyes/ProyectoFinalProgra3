//
// Created by Jordinn on 30/11/2024.
//

#include "nodo.h"

// Constructor
Nodo::Nodo(const string& title, const string& plotSynopsis, const vector<string>& tags)
    : title(title), plotSynopsis(plotSynopsis), tags(tags), left(nullptr), right(nullptr) {}

// Getters
string Nodo::getTitle() const {
    return title;
}

string Nodo::getPlotSynopsis() const {
    return plotSynopsis;
}

vector<string> Nodo::getTags() const {
    return tags;
}

Nodo* Nodo::getLeft() const {
    return left;
}

Nodo* Nodo::getRight() const {
    return right;
}

// Setters
void Nodo::setLeft(Nodo* left) {
    this->left = left;
}

void Nodo::setRight(Nodo* right) {
    this->right = right;
}