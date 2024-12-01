//
// Created by Jordinn on 30/11/2024.
//

#include "nodo.h"

// Constructor
Nodo::Nodo(const pelicula& data) : data(data), left(nullptr), right(nullptr) {}

// Getters
const pelicula& Nodo::getData() const {
    return data;
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