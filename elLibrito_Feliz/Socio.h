#pragma once
#include "Fecha.h"
class Socio
{
private :
    int _numeroSocio ;
    char _nombre[50];
    char _apellido[50];
    char _dni[50];
    char _telefono[50];
    char _direccion[50] ;
    char _email[50] ;
    Fecha fecha;
    bool _deudor;
public :
    Socio();
    Socio(int numeroSocio, std::string nombre, std::string apellido, std::string dni, std::string telefono, std::string direccion, std::string email, Fecha fecha, bool deudor);
    void setNumeroSocio(int numeroSocio);
    void setNombre(std::string nombre);
    void setApellido(std::string apellido);
    void setDni(std::string dni);
    void setTelefono(std::string telefono);
    void setDireccion (std::string direccion);
    void setEmail(std::string email);
    void setFecha(Fecha fecha);
    void setDeudor(bool deudor);
    int getNumeroSocio();
    std::string getNombre();
    std::string getApellido();
    std::string getDni();
    std::string getTelefono();
    std::string getDireccion();
    std::string getEmail();
    Fecha getFecha() const;
    bool getDeudor();
    void mostrarSocioPantalla();
    std::string mostrarDeudor();


};
