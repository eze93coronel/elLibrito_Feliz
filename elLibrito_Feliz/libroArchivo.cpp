#include <iostream>
#include "libroArchivo.h"
 using namespace std;
libroArchivo::libroArchivo(){
     _libroArchivo = "libros.dat";


}

libroArchivo::libroArchivo(std::string libroArchivo){
       this -> _libroArchivo = libroArchivo;

}

bool libroArchivo::guardarLIbro(libroArchivo libro) {
  bool response ;
  FILE *punteroArchivoLibro;
  punteroArchivoLibro= fopen(_libroArchivo.c_str(),"ab");

  if(punteroArchivoLibro == nullptr){
      cout << " ===== NO SE PUDO ABRIR EL ARCHIVO DE LIBROS  ==== " << endl;
    return false;
  }
   response = fwrite(&libro,sizeof(libro),1,punteroArchivoLibro);

   fclose(punteroArchivoLibro);

   return response;
}
