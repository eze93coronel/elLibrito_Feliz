#ifndef AUTORES_H_INCLUDED
#define AUTORES_H_INCLUDED
#pragma once
#include "Fecha.h"
#include <string>

class Autores{
private :
    int  _idautor;
    char nombreautor[50];

public :
    Autores();
    Autores(int IdAutor, std::string nombreAutor);
    void setIdAutor(int IdAutor);
    bool setNombreAutor(std::string nombreAutor);
    std::string getNombreAutor();
    int getIdAutor();
};


#endif // AUTORES_H_INCLUDED
