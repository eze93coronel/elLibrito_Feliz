/*#include <iostream>
using namespace std;
#include <cstdio>
#include <algorithm>
#include "libroArchivo.h"


/// por ahora esta funcion está adentro de libroArchivo, la idea es sacarla y pasarla acá cuando se construya la interacción con Autores.

int autoresManager::obtenerSiguienteIdAutor() {
    FILE* f = std::fopen(_nombreArchivoLibro.c_str(), "rb");
    if (!f) {
        // Si no existe el archivo o no se puede abrir, empezamos en 1
        return 1;
    }

    libro l;
    int maxId = 0;
    // Recorremos todos los libros y guardamos el mayor Id_autor que encontremos
    while (std::fread(&l, sizeof(libro), 1, f) == 1) {
        maxId = std::max(maxId, l.getIdAutor());
    }
    std::fclose(f);

    // El siguiente ID será el mayor + 1
    return maxId + 1;
}
*/
