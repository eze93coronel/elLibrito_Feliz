#include <iostream>
#include "socioManager.h"
#include "Socio.h"
#include "sociosArchivos.h"
using namespace std ;

void socioManager::cargarSocio()
{
    Socio socio;
    sociosArchivos socioArchivo;
    int numeroSocio;
    string nombre,apellido,dni,telefono,direccion,email;
cout <<"===============================" << endl;
    cout <<"INGRESE DATOS DEL SOCIO : " << endl;
    cout << "== NUMERO DEL SOCIO  ==" << endl;
    cin >> numeroSocio;
      cin.ignore();
    cout << "== NOMBRE ==" << endl;
    getline(cin,nombre);
    cout << "== APELLIDO ==" << endl;

    getline(cin,apellido);
    cout << "== DNI ==" << endl;
    getline(cin,dni);
    cout << "== TELEFONO ==" << endl;

    getline(cin,telefono);
    cout << "== DIRECCION ==" << endl;
    getline(cin,direccion);
    cout << "== EMAIL ==" << endl;

    getline(cin,email);
cout <<"===============================" << endl;

  socio = Socio(numeroSocio,nombre,apellido,dni,telefono,direccion,email);
   cout << socio.mostrarSocioPantalla() << endl;

   if(socioArchivo.guardarArchivoSocio(socio)) {

      cout << " === EL ARCHIVO DEL SOCIO FUE GUARDADO CORRECTAMENTE === " << endl;
   }
   else{
            cout << " ===  ERROR, NO SE PUDO GUARDAR  EL ARCHIVO DEL SOCIO  === " << endl;

   }
}
