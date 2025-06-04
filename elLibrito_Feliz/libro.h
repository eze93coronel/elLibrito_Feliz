#pragma once
#include "Fecha.h"
class libro
{
private :
    char _isbn[30];
    char _titulo[50];
    int Id_autor;
    int cantidadEjemplares;
    Fecha   fechaPublicacion;

public :
    libro();
    libro(std::string  isbn,std::string titulo,int IdAutor,int cantidadEjemplares,fechaPublicacion);

    void setIsbn(std::string isbn);
    void setTitulo(std::string titulo);
    void setIdAutor(int IdAutor);
    void setCantidadEjemplares(int cantidadEjemplares);


    std::string getIsbn();
    std::string getTitulo();
    int getIdAutor();
    int getCantidadEjemplares();

    std::string mostrarLIbro();





};
