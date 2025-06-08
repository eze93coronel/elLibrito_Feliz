#pragma once
#include "Fecha.h"
class libro{
private :
    char  _isbn[14];
    char _titulo[50];
    int Id_autor;
    int cantidadEjemplares;
    int librosPrestados;
    Fecha fechaPublicacion;

public :
    libro();
    libro(std::string isbn,std::string titulo,int IdAutor,int cantidadEjemplares, int librosPrestados, Fecha fechaPublicacion);

    bool setIsbn(std::string isbn);
    bool setTitulo(std::string titulo);
    void setIdAutor(int IdAutor);
    void setCantidadEjemplares(int cantidadEjemplares);
    void setlibrosPrestados(int librosPrestados);

    std::string getIsbn();
    std::string getTitulo();
    int getIdAutor();
    int getCantidadEjemplares();
    int getlibrosPrestados();

    std::string mostrarLibro();

    void setFechaPublicacion(const Fecha& f);
    Fecha getFechaPublicacion() const;
};
