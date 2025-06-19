#include <iostream>
#include <limits>
#include "menuLibreria.h"
#include "socioManager.h"
#include "cuotasManager.h"
using namespace std ;

void menuLibreria::mostrarMenuPrincipal(){
  socioManager socioManager;
  cuotasManager cM;
  int opcion ;
  do {
    cout << "****** BIBLIOTECA EL LIBRITO FELIZ ******" << endl;
    cout << "---------------------------------------" << endl;
    cout << " SUB MENU: SOCIOS  " << endl;
    cout << "         1. ALTA DE SOCIOS" << endl;
    cout << "         2. CONSULTAR SOCIOS " << endl;
    cout << "         3. MODIFICAR SOCIOS "  << endl;
    cout << "         4. RESUMEN DE SOCIOS "  << endl;
    cout << "         5. PAGAR CUOTAS "  << endl;
    cout << "         6. VOLVER AL MENU ANTERIOR "  << endl;
    cout << "         7. SALIR DEL PROGRAMA "  << endl;
    cout << "---------------------------------------" << endl;
    cout <<"INGRESE UNA OPCIÓN: ";
    cin >> opcion;
    cout << endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    system("cls");
    switch(opcion){
       case 1 :
            cout << "-------------------------------" << endl;
            cout << "INGRESE DATOS DEL SOCIO: " << endl;
            cout << "===============================" << endl;
            socioManager.cargarSocio();
            system("cls");
        break;

       case 2 :
          socioManager.buscarSocio();
          system("pause");
       break;
       case 3 :
            socioManager.modificarSocio();
            system("cls");
        break;
       case 4:
            socioManager.resumenSocios();
           system("pause");
           break;
        case 5:
            cM.registrarPagoCuota();
           system("pause");
           break;
       case 6 :
           return;
        break;
       case 7:
            cout << "==================================================" << endl;
            cout << "USTED A DECIDIDO CERRAR EL PROGRAMA. ¡HASTA LUEGO!" << endl;
            cout << "==================================================" << endl;
            exit(0);
        break;
    }

  }while(opcion!=8);



}
