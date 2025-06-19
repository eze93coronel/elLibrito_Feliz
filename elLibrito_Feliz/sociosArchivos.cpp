#include <iostream>
#include <cstring>
#include "sociosArchivos.h"
#include "funcionesAuxiliares.h"

using namespace std;
sociosArchivos::sociosArchivos(){
     _nombreArchivoSocio = "archivos/socios.dat";
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

int sociosArchivos::getCantidadRegistroSocio() {
       int tamanioRegistroSocio = sizeof(Socio);
      FILE *punteroSocioArchivo;
      punteroSocioArchivo = fopen(_nombreArchivoSocio.c_str(), "rb");

      if(punteroSocioArchivo == nullptr){
          return 0;
      }
      fseek(punteroSocioArchivo,0,SEEK_END);

      int totalDeRegistros = ftell(punteroSocioArchivo);
      int cantidadDeRegistros = totalDeRegistros / tamanioRegistroSocio;
      fclose(punteroSocioArchivo);

      return cantidadDeRegistros;
}

Socio sociosArchivos::LeerSocio(int pos) {
    FILE *punteroArchivoSocio;
    Socio registroSocio;

    punteroArchivoSocio = fopen(_nombreArchivoSocio.c_str(), "rb");
    if (punteroArchivoSocio == nullptr) {
        cout << "Error: No se pudo abrir el archivo de socios." << endl;
        return registroSocio;  // Devuelve un objeto vacío
    }

    // Verificar la cantidad de registros
   // fseek(punteroArchivoSocio, 0, SEEK_END);
    //int cantidadRegistros = ftell(punteroArchivoSocio) / sizeof(Socio);

   /* if (pos < 0 || pos >= cantidadRegistros) {
        cout << "Error: Posición fuera de rango." << endl;
        fclose(punteroArchivoSocio);
        return registroSocio;  // Devuelve un objeto vacío
    } */

    // Posicionar el puntero y leer el registro
    fseek(punteroArchivoSocio, sizeof(Socio) * pos, SEEK_SET);
    fread(&registroSocio, sizeof(Socio), 1, punteroArchivoSocio);

    fclose(punteroArchivoSocio);
    return registroSocio;
}

int sociosArchivos::buscarArchivoSocio(int numeroSocio) {
    FILE *punteroArchivosSocio;
    Socio objSocio;

    punteroArchivosSocio = fopen(_nombreArchivoSocio.c_str(), "rb");
    if (punteroArchivosSocio == nullptr) {
        cout << "Error: No se pudo abrir el archivo de socios." << endl;
        return -1;
    }

    int posicion = 0;
    while (fread(&objSocio, sizeof(Socio), 1, punteroArchivosSocio) == 1) {
        if (objSocio.getNumeroSocio() == numeroSocio) {  // Corrección aquí
            fclose(punteroArchivosSocio);
            return posicion;
        }
        posicion++;
    }

    fclose(punteroArchivosSocio);
    return -1;  // No se encontró el socio
}

int sociosArchivos::modificarSocio(Socio registroSocio, int pos)  {
  FILE *punteroARchivoSocio;
//  Socio registroSocio;
  int tamanioRegistroSocio = sizeof(Socio);
  punteroARchivoSocio = fopen(_nombreArchivoSocio.c_str(),"rb+");

  if(punteroARchivoSocio == nullptr){
         cout << "Error: No se pudo abrir el archivo de socios." << endl;
      return -1;
  }
   fseek(punteroARchivoSocio, sizeof(Socio) * pos, SEEK_SET);

  int modificar = fwrite(&registroSocio,tamanioRegistroSocio,1,punteroARchivoSocio) ;

  fclose(punteroARchivoSocio);

  return modificar;

}

bool sociosArchivos::buscarSocioPorId(int idBuscado, Socio& socioEncontrado) {
    FILE* f = abrirArchivo(_nombreArchivoSocio, "rb");
    if (f == nullptr) return false;

    Socio s;
    while (fread(&s, sizeof(Socio), 1, f) == 1) {
        if (s.getNumeroSocio() == idBuscado) {
            socioEncontrado = s;
            fclose(f);
            return true;
        }
    }

    fclose(f);
    return false;
}
