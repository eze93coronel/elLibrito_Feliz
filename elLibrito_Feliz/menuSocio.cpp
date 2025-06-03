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
    cout << "1. Cargar Socio  " << endl;
    cout << "2. Modificar socio "  << endl;
    cout << "3. Registrar pago "  << endl;
    cout << "4. Consultar socio"  << endl;
    cout << "5. salir "  << endl;

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
    }
  }while(opcion!=5);


}
