#include <iostream>
#include "sociosArchivos.h"
using namespace std;
sociosArchivos::sociosArchivos(){
     _nombreArchivoSocio = "socios.dat";


}

sociosArchivos::sociosArchivos(std::string nombreArchivoSocio){
       this -> _nombreArchivoSocio = nombreArchivoSocio;

}

bool sociosArchivos::guardarArchivoSocio(Socio registroSocio) {
  bool response ;
  FILE *punteroArchivoSocio;
  punteroArchivoSocio = fopen(_nombreArchivoSocio.c_str(),"ab");

  if(punteroArchivoSocio == nullptr){
      cout << " ===== NO SE PUDO ABRIR EL ARCHIVO DE SOCIOS ==== " << endl;
    return false;
  }
   response = fwrite(&registroSocio,sizeof(Socio),1,punteroArchivoSocio);

   fclose(punteroArchivoSocio);

   return response;
}
