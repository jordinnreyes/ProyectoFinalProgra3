
#include <iostream>
#include "pelicula.h"
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class LecturaDatos {
private:
    unordered_map<string, pelicula> peliculas;

public:


    void leerDatosDelCsv(const string& archivoCsv) {
        ifstream archivo(archivoCsv);
        string linea;

        if (!archivo.is_open()) {
            cerr << "No se pudo abrir el archivo: " << archivoCsv << endl;
            return;
        }

        // Leer la cabecera del archivo
        getline(archivo, linea);

        size_t peliculasExitosas = 0, peliculasFallidas = 0;



        while (getline(archivo, linea)) {
            if (linea.empty()) continue; // Ignorar líneas vacías

            istringstream stream(linea);
            string imdb_id, title, plot_synopsis, tagsStr, split, synopsis_source;

            try {
                // Procesar campos respetando las comillas
                getline(stream, imdb_id, '"');
                getline(stream, imdb_id, ',');

                // Leer title con la lógica que sugeriste
                if (stream.peek() == '"') {
                    stream.get(); // Consumir la comilla inicial
                    getline(stream, title, '"');
                    stream.get(); // Consumir la coma después de las comillas
                } else {
                    getline(stream, title, ',');
                }
                //title = limpiarComillasDobles(title);



                //plot_synopsis = limpiarComillasDobles(plot_synopsis);
                if (stream.peek() == '"') {

                    getline(stream, plot_synopsis, '"');
                    stream.get(); // Consumir la comilla inicial
                    getline(stream, plot_synopsis, '"');
                    //stream.get(); // Consumir la coma después de las comillas
                } else {
                    getline(stream, plot_synopsis, ',');
                }




                limpiarComillasDobles(tagsStr);
                // Leer tagsStr, que está entre comillas
                if (stream.peek() == '"') {
                    //getline(stream, tagsStr, '"');
                    stream.get();
                    getline(stream, tagsStr, '"'); // Leer hasta la siguiente comilla
                    stream.get(); // Consumir la coma después de la comilla
                    cout << "Tags con comillas: '" << tagsStr << "'" << endl;

                } else {
                    getline(stream, tagsStr, ',');// Leer hasta la coma si no está entre comillas
                    cout << "Tags sin comillas: '" << tagsStr << "'" << endl;
                }


                // Procesar los tags usando la nueva función dividirConComillas
                unordered_set<string> tags  = ExtraerTags(tagsStr);



                // Leer synopsis_source
                getline(stream, split, ',');
                getline(stream, split, ',');



                getline(stream, synopsis_source);
                getline(stream, synopsis_source, '"'); // Leer hasta la siguiente comilla
                if (stream.peek() == ',') {
                    stream.get(); // Consumir la coma después de las comillas
                }


                // Configurar la nueva película
                pelicula nuevaPelicula;
                nuevaPelicula.configurarPropiedades(imdb_id, title, plot_synopsis, tags, synopsis_source);

                // Guardar la película en el mapa
                peliculas[imdb_id] = move(nuevaPelicula);
                peliculasExitosas++;
            } catch (const exception& e) {
                cerr << "Error al procesar linea: " << linea << ". Detalles: " << e.what() << endl;
                peliculasFallidas++;
            }
        }

        archivo.close();

        cout << "Peliculas leidas correctamente: " << peliculasExitosas << endl;
        cout << "Peliculas fallidas: " << peliculasFallidas << endl;
    }

    const unordered_map<string, pelicula>& getPeliculas() const {
        return peliculas;
    }

    // Función para limpiar comillas dobles escapadas
    string limpiarComillasDobles(const string& input) {
        string resultado = input;
        // Reemplazar "" por "
        size_t pos = 0;
        while ((pos = resultado.find("\"\"", pos)) != string::npos) {
            resultado.replace(pos, 2, "\"");
            pos++;
        }
        // Eliminar las comillas al inicio y al final, si existen
        if (!resultado.empty() && resultado.front() == '"' && resultado.back() == '"') {
            resultado = resultado.substr(1, resultado.size() - 2);
        }
        return resultado;
    }

    unordered_set<string> ExtraerTags(const string& entrada) {

        unordered_set<string> conjuntoTags;

        // Validar entrada vacía
        if (entrada.empty()) {
            cout << "vacio ";
            return conjuntoTags; // Retorna vacío
        }
        // Si no contiene comillas ni comas, es un único tag
        if (entrada.find('"') == string::npos && entrada.find(',') == string::npos) {
            conjuntoTags.insert(entrada);
            return conjuntoTags; // Salir inmediatamente
        }


        istringstream flujoEntrada(entrada);
        string fragmentoActual;
        bool dentroDeComillas = false;
        string acumulador;
        char caracter;

        while (flujoEntrada.get(caracter)) {
            if (caracter == '"') {
                dentroDeComillas = !dentroDeComillas;
                if (!dentroDeComillas && !acumulador.empty()) {
                    conjuntoTags.insert(acumulador);
                    acumulador.clear();
                }
            } else if (caracter == ',' && !dentroDeComillas) {
                if (!acumulador.empty()) {
                    conjuntoTags.insert(acumulador);
                    acumulador.clear();
                }
            } else {
                acumulador += caracter;
            }
        }

        if (!acumulador.empty()) {
            conjuntoTags.insert(acumulador);
        }

        return conjuntoTags;
    }








};

