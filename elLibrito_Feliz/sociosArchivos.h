#pragma once
#include "Socio.h"
#include <string>

class sociosArchivos {
  private :
      std:: string _nombreArchivoSocio;
  public :

    sociosArchivos();
    sociosArchivos(std:: string nombreArchivoSocio);
    bool guardarArchivoSocio( Socio registroSocio);
    int getCantidadRegistroSocio();
    Socio LeerSocio(int posicion);
    int modificarSocio(Socio registroSocio, int pos);
    int buscarArchivoSocio(int numeroSocio);
    bool buscarSocioPorId(int idBuscado, Socio& socioEncontrado);
};
