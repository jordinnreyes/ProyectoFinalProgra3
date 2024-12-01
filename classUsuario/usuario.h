#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <string>
#include <type_traits>

using namespace std;

template <typename T>
class usuario {
private:
    string nombre;
    T contraseña;
    static usuario<T>* instance;
    bool accesoAlServicio = false;

    usuario() {
        cout << "Ingrese su nombre: ";
        cin >> nombre;
        cout << "Ingrese su contrasenia: ";
        cin >> contraseña;

        if constexpr (is_arithmetic<T>::value) {
            while (nombre == to_string(contraseña)) {
                cout << "Por seguridad, cree un Usuario con una contrasenia diferente a su nombre: ";
                cin >> contraseña;
            }
        } else {
            while (nombre == contraseña) {
                cout << "Por seguridad, cree un Usuario con una contraseniaa diferente a su nombre: ";
                cin >> contraseña;
            }
        }

        cout << "\nusuario creado y loggeado correctamente" << endl;
    }

public:
    void login() {
        string nombree;
        T contraseñaa;

        cout << "\nInicie sesion" << endl;
        cout << "Nombre: ";
        cin >> nombree;
        cout << "Contrasenia: ";
        cin >> contraseñaa;

        if (nombre == nombree && contraseña == contraseñaa) {
            cout << "Iniciaste sesion correctamente!!" << endl;
            accesoAlServicio = true;
        } else {
            cout << "Contrasenia o nombre incorrecto" << endl;
        }
    }

    bool getaccesoAlServicio() const {
        return accesoAlServicio;
    }

    static usuario* getInstance() {
        if (instance == nullptr) {
            instance = new usuario();
        }
        return instance;
    }
};

// Inicialización de la instancia estática
template <typename T>
usuario<T>* usuario<T>::instance = nullptr;

#endif // USUARIO_H
