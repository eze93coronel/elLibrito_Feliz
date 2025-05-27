#include <iostream>
#include "Socio.h"
#include <string>
using namespace std;
Socio::Socio(){
     _numeroSocio = 0;
     _nombre = " ";
     _apellido = " ";
     _dni = "";


     _telefono = "";

    _direccion  = "";
     _email = "";

}

Socio::Socio(int numeroSocio,   std::string nombre,std::string apellido,std::string dni,std::string telefono,std::string direccion,std::string email){
    setNumeroSocio(numeroSocio);
    setNombre(nombre);
    setApellido(apellido);
    setDni(dni);
    setTelefono(telefono);
    setDireccion(direccion);
    setEmail(email);

}
void Socio::setNumeroSocio(int numeroSocio){
     this -> _numeroSocio = numeroSocio;
}

void Socio::setNombre(std::string nombre){
     this -> _nombre = nombre;
 }

 void Socio::setApellido(std::string apellido) {

      this -> _apellido = apellido;
 }
  void Socio::setDni(std::string dni) {

      this -> _dni = dni;
 }
 void Socio::setTelefono(std::string telefono) {
     this -> _telefono = telefono;
 }
  void Socio::setDireccion (std::string direccion) {

      this -> _direccion = direccion;
 }

 void Socio::setEmail(std::string email) {
     this -> _email = email;
 }

 int Socio::getNumeroSocio() {
    return _numeroSocio;
 }
 std::string Socio::getNombre() {
    return _nombre;
 }
 std::string Socio::getApellido() {
    return _apellido;
 }
 std::string Socio::getDni() {
    return _dni;
 }
  std::string Socio::getTelefono() {
    return _telefono;
 }
 std::string Socio::getDireccion() {
    return _direccion;
 }
 std::string Socio::getEmail() {
    return _email;
 }


 std::string Socio::mostrarSocioPantalla() {

     std::string str = "";
    str += std::to_string(_numeroSocio) + ",";
    str += std::string(_nombre) + ",";
    str += std::string ( _apellido) + ",";
    str +=std::string( _dni) + ",";
    str += std::string(_telefono) + ",";
    str += std::string(_direccion)+ ",";
    str += std::string(_email);

    return str;

 }
