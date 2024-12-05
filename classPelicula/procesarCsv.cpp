#include <iostream>
#include "pelicula.h"
#include <sstream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

class LecturaDatos {
private:
    unordered_map<string, pelicula> peliculas;

    // Función para eliminar espacios adicionales
    string trim(const string& str) {
        size_t first = str.find_first_not_of(" \t\r\n");
        size_t last = str.find_last_not_of(" \t\r\n");
        return (first == string::npos || last == string::npos) ? "" : str.substr(first, (last - first + 1));
    }

    // Función para separar un CSV correctamente manejando comas dentro de comillas
    vector<string> splitCSV(const string& line) {
        vector<string> columns;
        string currentField;
        bool inQuotes = false;

        for (size_t i = 0; i < line.size(); ++i) {
            char c = line[i];

            if (c == '\"') {
                inQuotes = !inQuotes;  // Cambiar estado dentro/fuera de comillas
            } else if (c == ',' && !inQuotes) {
                // Se encontró una coma fuera de las comillas
                columns.push_back(trim(currentField));  // Agregar el campo y recortar espacios extra
                currentField.clear();  // Limpiar el campo actual
            } else {
                currentField += c;  // Agregar el carácter al campo actual
            }
        }

        // Agregar el último campo
        if (!currentField.empty()) {
            columns.push_back(trim(currentField));
        }

        return columns;
    }

    // Función para convertir una cadena a mayúsculas
    string toUpperCase(const string& str) {
        string result;
        for (char c : str) {
            result += toupper(c);
        }
        return result;
    }

public:


    void leerDatosDelCsv1(const string& archivoCsv) {
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
                    getline(stream, tagsStr, '"');
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

    // Función para dividir tags que están entre comillas y separados por comas
    unordered_set<string> dividirConComillas2(const string& str) {
        unordered_set<string> tokens;
        string tagCompleto;
        bool enComillas = false;

        for (char c : str) {
            if (c == '"') {
                enComillas = !enComillas;
            } else if (c == ',' && !enComillas) {
                if (!tagCompleto.empty()) {
                    tokens.insert(tagCompleto);
                    tagCompleto.clear();
                }
            } else {
                tagCompleto += c;
            }
        }

        if (!tagCompleto.empty()) {
            tokens.insert(tagCompleto);
        }

        return tokens;
    }

    // Función para limpiar las comillas dobles escapadas en las cadenas
    string limpiarComillasDobles2(const string& input) {
        string resultado = input;
        size_t pos = 0;
        while ((pos = resultado.find("\"\"", pos)) != string::npos) {
            resultado.replace(pos, 2, "\"");
            pos++;
        }
        if (!resultado.empty() && resultado.front() == '"' && resultado.back() == '"') {
            resultado = resultado.substr(1, resultado.size() - 2);
        }
        return resultado;
    }

    // Función para leer datos del archivo CSV
    void leerDatosDelCsv2(const string& archivoCsv) {
        ifstream archivo(archivoCsv);
        string linea, completeLine;
        bool firstLine = true;  // Bandera para ignorar la primera línea (encabezados)
        vector<string> headers;  // Encabezados
        bool inQuotes = false;

        if (!archivo.is_open()) {
            cerr << "No se pudo abrir el archivo: " << archivoCsv << endl;
            return;
        }

        // Leer la cabecera del archivo
        getline(archivo, linea);

        // Leer cada línea del archivo
        while (getline(archivo, linea)) {
            completeLine += linea;

            // Contar comillas dobles para detectar si estamos dentro de un campo multilineal
            inQuotes ^= count(linea.begin(), linea.end(), '\"') % 2;

            if (inQuotes) {
                // Continuar acumulando la línea
                completeLine += '\n';
                continue;
            }

            // Separar la línea completa en columnas
            vector<string> columns = splitCSV(completeLine);
            completeLine.clear();  // Limpiar la línea acumulada

            // Si es la primera línea (encabezados), guardar los encabezados
            if (firstLine) {
                for (const string& header : columns) {
                    headers.push_back(toUpperCase(header));  // Convertir encabezados a mayúsculas
                }
                firstLine = false;
                continue;
            }

            // Procesar los datos y agregar las películas
            if (!columns.empty()) {
                string imdb_id = columns[0];
                string title = columns[1];
                string plot_synopsis = columns[2];
                string tagsStr = columns[3];
                string split = columns[4];
                string fuente = columns[5];
                unordered_set<string> tags = dividirConComillas2(tagsStr);

                // Configurar la nueva película
                pelicula nuevaPelicula;
                nuevaPelicula.configurarPropiedades(imdb_id, title, plot_synopsis, tags, fuente);  // Aquí no se usa el source de sinopsis en este ejemplo

                // Guardar la película en el mapa
                peliculas[imdb_id] = move(nuevaPelicula);
            }
        }

        archivo.close();
        cout << "Películas leídas correctamente." << endl;
    }




};


