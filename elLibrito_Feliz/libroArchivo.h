#pragma once
#include <string>
#include "libro.h"  // Asegurate de incluir tu clase libro

class libroArchivo {
private:
    std::string _libroArchivo; // Ruta al archivo de libros
public:
    libroArchivo(); // Constructor por defecto (usa la ruta por defecto)
    libroArchivo(std::string libroArchivo); // Constructor parametrizado

    bool guardarLibro(const libro& l);
    int getCantidadRegistroLibro();
    libro LeerLibro(int pos);
    void listarLibros();
    void buscarLibro(); //esta funcion es para buscar libros
    void cargarLibro();
    bool guardarLibro(libroArchivo libro);
    void prestarLibro();
    bool elegirCriterioBusqueda(int& opc, std::string& criterio);
    int obtenerSiguienteIdAutor();
};
