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


};
