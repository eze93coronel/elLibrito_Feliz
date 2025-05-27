#include <iostream>
#include "menuLibreria.h"
#include "socioManager.h"
using namespace std ;

void menuLibreria::mostrarMenuPrincipal(){
  socioManager socioManager;
  int opcion ;
  do {
    cout << "---------------------------------------" << endl;

    cout << "MENU PRINCIPAL - SISTEMA DE LIBRERIA " << endl;
    cout << "1. SOCIOS " << endl;
    cout << "2. REPORTES "  << endl;
    cout << "3. LIBROS "  << endl;
    cout << "4. SALIR  "  << endl;

    cout << "---------------------------------------" << endl;

    cout <<"ingrese una opcion " << endl;
         cin >> opcion;
    switch(opcion){
       case 1 :
          socioManager.cargarSocio();

    }

  }while(opcion!=4);


}
