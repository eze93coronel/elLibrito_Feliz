#pragma once

class Socio
{
private :
    int _numeroSocio ;
    std::string _nombre;
    std::string _apellido;
    std::string _dni;

    std::string _telefono;

    std::string _direccion ;

    std::string _email ;

public :
    Socio();
    Socio(int numeroSocio,   std::string nombre,std::string apellido,std::string dni,std::string telefono,std::string direccion,std::string email)  ;

    void setNumeroSocio(int numeroSocio);
    void setNombre(std::string nombre);
    void setApellido(std::string apellido);
    void setDni(std::string dni);
    void setTelefono(std::string telefono);
    void setDireccion (std::string direccion);
    void setEmail(std::string email);

    int getNumeroSocio();
    std::string getNombre();
    std::string getApellido();
    std::string getDni();
    std::string getTelefono();
    std::string getDireccion();
    std::string getEmail();

    std::string mostrarSocioPantalla();

};
