#include <iostream>
#include <string>
#include <cstring>
#include "libro.h"
using namespace std ;
libro::libro()
{
    strcpy( _isbn,"");
    strcpy(   _titulo,"");
    Id_autor = 0;
    cantidadEjemplares = 0;
    Fecha   fechaPublicacion;

}

libro::libro(std::string isbn, std::string titulo, int IdAutor, int cantidadEjemplares, fechaPublicacion){
  setIsbn(isbn);
  setTitulo(titulo);
  setIdAutor(IdAutor);
  setCantidadEjemplares(cantidadEjemplares);


}

void libro::setIsbn(std::string isbn){
  if(isbn.empty()) {

    std::cout << "el isbn del libro no puede estar vacio ✌️✌️ " <<  endl;
  }

}
