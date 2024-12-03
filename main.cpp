#include <iostream>

#include "classUsuario/usuario.h"
#include "classPelicula/procesarCsv.cpp"
using namespace std;

int main()
{
    // Crear una instancia de LecturaDatos
    LecturaDatos lector;

    // Archivo de prueba
    string archivoPrueba = "C:/Users/Jordinn/Downloads/pruebaa.csv";

    // Leer datos desde el CSV
    lector.leerDatosDelCsv(archivoPrueba);


    // Obtener las películas leídas
    const auto& peliculas = lector.getPeliculas();


    cout << "\nBienvenido a nuestro servicio de Streaming!" << endl;
    cout << "Crea un Usuario!" << endl;


    usuario<string>* usuario1 = usuario<string>::getInstance();
    usuario1->login();

    if(usuario1->getaccesoAlServicio()){
        cout << "acceso al servicio correcto!";

    } else{cout << "ocurrio un error";}











    // Mostrar los datos de las películas

    /*cout << "Peliculas cargadas:" << endl;
    for (const auto& [id, pelicula] : peliculas) {
        cout << "ID: " << id << endl;
        cout << "Titulo: " << pelicula.getTitulo() << endl;
        cout << "Sinopsis: " << pelicula.getSinopsis() << endl;
        cout << "Fuente: " << pelicula.getFuente() << endl;

        // Mostrar los tags
        cout << "Tags: ";
        for (const auto& tag : pelicula.getTags()) {
            cout << tag << ", ";
        }
        cout << endl << "-----------------------" << endl;
    }
    */

    return 0;
}
