#include <iostream>
#include "menuLibro.h"
using namespace std ;
void menuLibro::mostrarMenuLibro() {
  int opcion ;

    do {
    cout << "---------------------------------------" << endl;

    cout << " SUB MENU SOCIO  " << endl;
    cout << "1. Alta libro " << endl;
    cout << "2.	Modificar libro "  << endl;
    cout << "3.	Prestar libro "  << endl;
    cout << "4.	Devolver libro "  << endl;
    cout << "5.	Consultar stock "  << endl;
    cout << "6.	Salir "  << endl;

    cout << "---------------------------------------" << endl;

    cout <<"ingrese una opcion " << endl;
         cin >> opcion;
    switch(opcion){
       case 1 :

        break;

       case 2 :

       break;
       case 3 :

        break;
       case 4 :

        break;
       case 5:

        break;
    }
  }while(opcion!=6);


}
