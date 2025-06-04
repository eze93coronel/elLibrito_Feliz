#include <iostream>
#include "menuLibreria.h"
#include "socioManager.h"
using namespace std ;

void menuLibreria::mostrarMenuPrincipal(){
  socioManager socioManager;
  int opcion ;
  do {
    cout << "---------------------------------------" << endl;

    cout << " SUB MENU SOCIO  " << endl;
    cout << "1. Alta Socio  " << endl;
    cout << "2. Listar Socios "  << endl;
    cout << "3. Consultar cantidad de registros  "  << endl;
    cout << "4. Consultar Socio "  << endl;
    cout << "5. Modificar Socio  "  << endl;
    cout << "6. salir "  << endl;

    cout << "---------------------------------------" << endl;

    cout <<"ingrese una opcion " << endl;
         cin >> opcion;
    switch(opcion){
       case 1 :
          socioManager.cargarSocio();
        break;

       case 2 :
          socioManager.listarSocios();
       break;
       case 3 :
            socioManager.cargarCantidadRegistroSocio();
        break;
       case 4 :
            socioManager.buscarSocio();
        break;
       case 5:
           socioManager.modificarSocio();
        break;
    }
  }while(opcion!=6);


}
