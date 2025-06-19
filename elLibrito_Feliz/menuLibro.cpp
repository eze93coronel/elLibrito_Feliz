#include <iostream>
#include <limits>
#include "menuLibro.h"
#include "libroArchivo.h"
#include "autoresManager.h"

using namespace std ;
void menuLibro::mostrarMenuLibro() {
    libroArchivo aLibro;
    autoresManager aAutores;
    int opcion ;


    do {
    cout << "****** BIBLIOTECA EL LIBRITO FELIZ ******" << endl;
    cout << "-----------------------------------------" << endl;
    cout << "   SUB MENU: LIBROS  " << endl;
    cout << "           1. ALTA DE LIBROS" << endl;
    cout << "           2. BUSCAR LIBROS " << endl;
    cout << "           3. MODIFICAR LIBROS "  << endl;
    cout << "           4. VOLVER AL MENU ANTERIOR "  << endl;
    cout << "           5. SALIR DEL PROGRAMA "  << endl;
    cout << "-----------------------------------------" << endl;
    cout <<"INGRESE UNA OPCIÓN: ";
    cin >> opcion;
    cout << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    system("cls");

    switch(opcion){
       case 1 :
            cout << "===============================" << endl;
            cout << "         ALTA DE LIBROS" << endl;
            cout << "===============================" << endl;
            cout << endl;
            cout << "INGRESE LOS DATOS DEL NUEVO LIBRO: " << endl << endl;
            aLibro.NuevoLibro();
            system("pause");
            system("cls");
        break;

       case 2 :
            cout << "===============================" << endl;
            cout << "       BUSQUEDA DE LIBROS"  << endl;
            cout << "===============================" << endl;
            cout << endl;
            cout << "INGRESE EL CRITERIO POR EL QUE QUIERE BUSCAR EL LIBRO: " << endl << endl;
            aLibro.buscarLibro();
            system("cls");
       break;

       case 3 :
            cout << "===============================" << endl;
            cout << "MODIFICAR LIBRO" << endl;
            cout << "==============================="<< endl;
           aLibro.modificarLibro();
           system("pause");
           system("cls");
        break;

       case 4 :
           return;
       case 5:
        cout << "==================================================" << endl;
        cout << "USTED A DECIDIDO CERRAR EL PROGRAMA. ¡HASTA LUEGO!" << endl;
        cout << "==================================================" << endl;
        exit(0);
        break;
    }
    system("cls");
  } while(opcion!=5);


}
