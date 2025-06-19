#pragma once

class socioManager {
private :

public :
    void cargarSocio();
    void buscarSocio() ;
    void cargarCantidadRegistroSocio();
    void listarSocios();
    void modificarSocio();
    bool dniExiste(const char* rutaArchivo, const std::string& dni);
    void resumenSocios();

};
