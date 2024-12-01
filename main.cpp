#include <iostream>

#include "classUsuario/usuario.h"
using namespace std;

int main()
{
    cout << "Bienvenido a nuestro servicio de Streaming!" << endl;
    cout << "Crea un Usuario!" << endl;


    usuario<string>* usuario1 = usuario<string>::getInstance();
    usuario1->login();

    if(usuario1->getaccesoAlServicio()){
        cout << "acceso al servicio correcto!";
    } else{cout << "nop";}



    return 0;
}
