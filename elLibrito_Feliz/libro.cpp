#include <iostream>
#include <string>
#include <cstring>
#include "libro.h"
using namespace std ;
libro::libro()
{
    strcpy(_isbn," ");
    strcpy(_titulo," ");
    Id_autor = 0;
    cantidadEjemplares = 0;
    Fecha   fechaPublicacion;

}

libro::libro(std::string isbn, std::string titulo, int IdAutor, int cantidadEjemplares,Fecha fechaPublicacion){
  setIsbn(isbn);
   setTitulo(titulo);
  setIdAutor(IdAutor);
  setCantidadEjemplares(cantidadEjemplares);


}

void libro::setIsbn(std::string isbn){
  if(isbn.empty()) {

    std::cout << "el isbn del libro no puede estar vacio ✌️✌️ " <<  endl;
    return;

  }
  strcpy(this -> _isbn,isbn.c_str());
}

void libro::setTitulo(std:: string titulo){
 if(titulo.empty() ) {

    std::cout << "el titulo del libro no puede estar vacio ✌️✌️ " <<  endl;
    return;

 }
   strcpy(this -> _titulo,titulo.c_str());
}

void libro::setIdAutor(int IdAutor){
   if(IdAutor <= 0  )
    {
        cout << " == EL NUMERO DE AUTOR NO PUEDE SER MENOR QUE 0 == "  << endl;
        return;
    }
    this ->  Id_autor = IdAutor;
}

 void libro::setCantidadEjemplares(int cantidadEjemplares){
   if(cantidadEjemplares < 0   )
    {
            cout << "Error: La cantidad de ejemplares no puede ser menor a 0." << endl;
        return;
    }
    this -> cantidadEjemplares= cantidadEjemplares;
}


std::string libro::getIsbn(){
    return _isbn;
}

std::string libro::getTitulo(){
     return _titulo;
}

int libro::getIdAutor(){
   return Id_autor;
}

int libro::getCantidadEjemplares(){
      return cantidadEjemplares;
}

std::string libro::mostrarLIbro(){

std::string str = "";

    str += std::string(_isbn) + ",";
    str += std::string ( _titulo) + ",";
    str +=std::to_string( Id_autor) + ",";
    str += std::to_string(cantidadEjemplares) + ",";
    fechaPublicacion.getDia();
    fechaPublicacion.getMes();
    fechaPublicacion.getAnio();



    return str;

}
