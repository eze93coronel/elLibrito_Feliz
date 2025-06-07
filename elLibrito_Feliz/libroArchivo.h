#pragma once
#include "libro.h"

class libroArchivo {
  private :
    std::string _libroArchivo;
  public :
     libroArchivo();
      libroArchivo(std::string libroArchivo);
     bool guardarLIbro(libroArchivo libro);




};
