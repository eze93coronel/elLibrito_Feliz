#include <iostream>
#include <string>
#include <cstring>
#include "libro.h"
using namespace std ;
libro::libro() : fechaPublicacion() {
    strcpy(_isbn, "");
    strcpy(_titulo, "");
    Id_autor = 0;
    cantidadEjemplares = 0;
    librosPrestados = 0;
}

libro::libro(std::string isbn, std::string titulo, int IdAutor, int cantidadEjemplares, int librosPrestados, Fecha fechaPublicacion): fechaPublicacion(fechaPublicacion){
    setIsbn(isbn);
    setTitulo(titulo);
    setIdAutor(IdAutor);
    setCantidadEjemplares(cantidadEjemplares);
    setlibrosPrestados(librosPrestados);
}

bool libro::setIsbn(std::string isbn) {
    if (isbn.empty()) {
        std::cout << "El ISBN del libro no puede estar vac�o." << std::endl << std::endl;
        return false;
    }

    if (isbn.length() > 13) {
        std::cout << "Error: el ISBN no puede tener m�s de 13 caracteres." << std::endl;
        return false;
    }

    strcpy(_isbn, isbn.c_str());
    return true;
}

bool libro::setTitulo(std::string titulo) {
    if (titulo.empty()) {
        std::cout << "El t�tulo no puede estar vac�o." << std::endl;
        return false;
    }

    if (titulo.length() > 50) {
        std::cout << "Error: el t�tulo no puede tener m�s de 50 caracteres." << std::endl;
        return false;
    }

    strcpy(_titulo, titulo.c_str());
    return true;
}

void libro::setIdAutor(int IdAutor){
   if(IdAutor <= 0)
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

 void libro::setlibrosPrestados(int librosPrestados){
     if(librosPrestados < 0)
    {
            cout << "Aun no se han ingresado prestamos de este libro." << endl;
        return;
    }

    this -> librosPrestados= librosPrestados;
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
int libro::getlibrosPrestados(){
      return librosPrestados;
}

///PREGUNTAR A EZE PARA QU� EST� ESTA FUNCION AC� SI TAMBI�N LA TENEMOS EN LIBROARCHIVO.
std::string libro::mostrarLibro(){
std::string str = "";
    str += std::string(_isbn) + ",";
    str += std::string ( _titulo) + ",";
    str +=std::to_string( Id_autor) + ",";
    str += std::to_string(cantidadEjemplares) + ",";
    str += std::to_string(librosPrestados) + ",";
    fechaPublicacion.getDia();
    fechaPublicacion.getMes();
    fechaPublicacion.getAnio();
    return str;
}

void libro::setFechaPublicacion(const Fecha& f) {
    fechaPublicacion = f;
}

Fecha libro::getFechaPublicacion() const {
    return fechaPublicacion;
}
