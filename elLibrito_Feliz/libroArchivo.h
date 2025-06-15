#pragma once
#include <string>
#include "libro.h"  // Asegurate de incluir tu clase libro
#include "autoresManager.h"
class libroArchivo {
private:
    std::string _libroArchivo; // Ruta al archivo de libros
public:
    libroArchivo();
    libroArchivo(std::string libroArchivo);

    bool guardarLibro(const libro& l);
    int getCantidadRegistroLibro();
    libro LeerLibro(int pos);
    void listarLibros();
    void buscarLibro();
    void NuevoLibro();
    bool guardarLibro(libroArchivo libro);
    void prestarLibro();
    bool elegirCriterioBusqueda(int& opc, std::string& criterio);
    void mostrarEncabezadoTablaLibros();
    void mostrarLibroEnTabla(libro& l, autoresManager& manager);
    bool existeIsbn(const std::string& isbnBuscado, libro& libroEncontrado);
    void modificarLibro();
    void devolverLibro();

};
