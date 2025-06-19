#include <iostream>
#include "Socio.h"
#include <string>
#include <cstring>
using namespace std;
Socio::Socio(){
    _numeroSocio = 0;
    strcpy( _nombre," ");
    strcpy( _apellido," ");
    strcpy( _dni," ");
    strcpy( _telefono," ");
    strcpy( _direccion," ");
    strcpy( _email," ");
    Fecha fecha;
    _deudor = false;
}

Socio::Socio(int numeroSocio,   std::string nombre,std::string apellido,std::string dni,std::string telefono,std::string direccion,std::string email, Fecha fecha, bool deudor){
    setNumeroSocio(numeroSocio);
    setNombre(nombre);
    setApellido(apellido);
    setDni(dni);
    setTelefono(telefono);
    setDireccion(direccion);
    setEmail(email);
    setFecha(fecha);
    setDeudor(deudor);
}
void Socio::setNumeroSocio(int numeroSocio){

    if(numeroSocio <= 0  )
    {
        cout << " == EL NUMERO DE SOCIO NO PUEDE SER MENOR QUE 0 == "  << endl;
        return;
    }
    this -> _numeroSocio = numeroSocio;
}

void Socio::setNombre(std::string nombre){
    // Verificar que el nombre no est� vac�o
    if (nombre.empty())
    {
        std::cout << "Error: El nombre no puede estar vac�o." << std::endl;
        return;
    }
 for (size_t i = 0; i < nombre.length(); i++) {
    char c = nombre[i]; // Obtener el car�cter actual
    if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ')) {
        std::cout << "Error: El nombre solo puede contener letras y espacios." << std::endl;
        return;
    }
}
    // Asignar el nombre v�lido
    strcpy(this -> _nombre,nombre.c_str());
}

void Socio::setApellido(std::string apellido){
    if(apellido.empty())
    {
        std::cout << "Error: El Apellido no puede estar vac�o." << std::endl;
    }
    for(char v : apellido)
    {
        if(!((v >= 'A' && v <= 'Z')|| (v >= 'a' && v <= 'z')||  v == ' '))
        {
            std::cout << "Error: El Apellido solo puede contener letras y espacios." << std::endl;
            return;
        }
    }
    strcpy ( this -> _apellido,apellido.c_str()) ;
}

void Socio::setDni(std::string dni){
    if(dni.empty())
    {
        cout << "Error: El n�mero de Dni no puede estar vac�o " << endl;
        return;
    }
    strcpy ( this -> _dni,dni.c_str()) ;
}

void Socio::setTelefono(std::string telefono){
    if (telefono.empty()){
        std::cout << "Error: El n�mero de tel�fono no puede estar vac�o." << std::endl;
        return;
    }

    // Validar que solo contenga n�meros
    for (char c : telefono){
        if (c < '0' || c > '9')
        {
            std::cout << "Error: El n�mero de tel�fono solo debe contener d�gitos." << std::endl;
            return;
        }
    }

    // Validar longitud m�nima (puedes ajustarla seg�n necesidad)
    if (telefono.length() < 7 || telefono.length() > 15){
        std::cout << "Error: El n�mero de tel�fono debe tener entre 7 y 15 d�gitos." << std::endl;
        return;
    }

    strcpy ( this -> _telefono,telefono.c_str()) ;
}

void Socio::setDireccion(std::string direccion){
    // Verificar que la direcci�n no est� vac�a
    if (direccion.empty())
    {
        std::cout << "Error: La direcci�n no puede estar vac�a." << std::endl;
        return;
    }
    // Verificar que la direcci�n no tenga caracteres especiales inv�lidos
    for (char c : direccion)
    {
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == ' ' || c == ',' || c == '.' || c == '-' || c == '#'))
        {
            std::cout << "Error: La direcci�n contiene caracteres inv�lidos." << std::endl;
            return;
        }
    }
    strcpy ( this -> _direccion,direccion.c_str()) ;
}

void Socio::setEmail(std::string email){
    if (email.empty())
    {
        std::cout << "Error: El email no puede estar vac�o." << std::endl;
        return;
    }
    size_t atPos = email.find('@');
    size_t dotPos = email.find('.', atPos);
    // Verificar que haya un '@' y un '.' despu�s del '@'
    if (atPos == std::string::npos || dotPos == std::string::npos)
    {
        std::cout << "Error: El email debe contener un '@' y un '.' despu�s del '@'." << std::endl;
        return;
    }
    // Verificar que no haya espacios
    if (email.find(' ') != std::string::npos)
    {
        std::cout << "Error: El email no puede contener espacios." << std::endl;
        return;
    }
    strcpy ( this -> _email,email.c_str()) ;
}

void Socio::setFecha(Fecha f){
    fecha = f;
}

void Socio::setDeudor(bool deudor){
    _deudor = deudor;
}

int Socio::getNumeroSocio(){
    return _numeroSocio;
}

std::string Socio::getNombre(){
    return _nombre;
}

std::string Socio::getApellido(){
    return _apellido;
}

std::string Socio::getDni(){
    return _dni;
}

std::string Socio::getTelefono(){
    return _telefono;
}

std::string Socio::getDireccion(){
    return _direccion;
}

std::string Socio::getEmail(){
    return _email;
}

Fecha Socio::getFecha()const{
    return fecha;
}

bool Socio::getDeudor(){
    return _deudor;
}

void Socio::mostrarSocioPantalla() {
    cout << "ID SOCIO: " << _numeroSocio << endl;
    cout << "NOMBRE Y APELLIDO: " << _nombre << " " << _apellido << endl;
    cout << "DNI: " << _dni << endl;
    cout << "TELEFONO: " << _telefono << endl;
    cout << "DIRECCION: " << _direccion << endl;
    cout << "EMAIL: " << _email << endl;
    cout << "FECHA DE ALTA: " << fecha.toString() << endl;
    cout << "ES DEUDOR: " << mostrarDeudor() << endl;
}

string Socio::mostrarDeudor() {
    return _deudor ? "Si" : "No";
}
