#include <iostream>
#include <string>
#include <cstring>
#include "autores.h"
using namespace std;

Autores::Autores(){
    _idautor = 0;
    strcpy(nombreautor, "");
}

Autores::Autores(int IdAutor, std::string nombreAutor){
    setIdAutor(IdAutor);
    setNombreAutor(nombreAutor);
}

bool Autores::setNombreAutor(std::string nombreAutor){
    if(nombreAutor.empty() ) {
    std::cout << "el titulo del libro no puede estar vacio" << endl << std::endl;
    return false;
    }
    else{
        strcpy(this -> nombreautor,nombreAutor.c_str());
        return true;
    }

}

void Autores::setIdAutor(int IdAutor){
   if(IdAutor <= 0)
    {
        cout << " == EL NUMERO DE AUTOR NO PUEDE SER MENOR QUE 0 == "  << endl;
        return;
    }
    this ->  _idautor = IdAutor;
}

std::string Autores::getNombreAutor(){
     return nombreautor;
}

int Autores::getIdAutor(){
   return _idautor;
}
