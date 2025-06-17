#include <iostream>
#include "menuLibro.h"
#include "libroArchivo.h"
#include "autoresManager.h"

using namespace std ;
void menuLibro::mostrarMenuLibro() {
    libroArchivo aLibro;
    autoresManager aAutores;
    int opcion ;


    do {
    cout << "---------------------------------------" << endl;

    cout << " SUB MENU: LIBROS  " << endl;
    cout << "1. Alta libro " << endl;
    cout << "2. Buscar un libro " << endl;
    cout << "3. Modificar libro "  << endl;
    cout << "4. Prestar libro "  << endl;
    cout << "5. Devolver libro "  << endl;
    cout << "6. Volver al menu anterior "  << endl;
    cout << "7. Salir "  << endl;


    cout << "---------------------------------------" << endl;

    cout <<"ingrese una opcion: ";
         cin >> opcion;
         cin.ignore();
         system("cls");

    switch(opcion){
       case 1 :
            std::cout << "===============================" << std::endl;
            std::cout << "         ALTA DE LIBROS" << std::endl;
            std::cout << "===============================" << std::endl;
            std::cout << std::endl;
            cout << "Ingrese los datos del nuevo libro: " << endl << endl;
            aLibro.NuevoLibro();
            system("pause");
        break;

       case 2 :
            std::cout << "===============================" << std::endl;
            std::cout << "       BUSQUEDA DE LIBROS"  << std::endl;
            std::cout << "===============================" << std::endl;
            std::cout << std::endl;
            cout << "INGRESE EL CRITERIO POR EL QUE QUIERE BUSCAR EL LIBRO: " << endl << endl;
            aLibro.buscarLibro();
            system("pause");
       break;

       case 3 :
            std::cout << "===============================" << std::endl;
            std::cout << "MODIFICAR LIBRO" << std::endl;
            std::cout << "==============================="<< std::endl;
           aLibro.modificarLibro();
           system("pause");
        break;

       case 4 :
            std::cout << "===============================" << std::endl;
            std::cout << "PRESTAMOS DE LIBROS" << std::endl;
            std::cout << "==============================="<< std::endl;
            aLibro.prestarLibro();
            system("pause");

        break;
       case 5:
            std::cout << "===============================" << std::endl;
            std::cout << "DEVOLVER LIBRO" << std::endl;
            std::cout << "==============================="<< std::endl;
            aLibro.devolverLibro();
            system("pause");
        break;

       case 6:
           return;
       case 7:
        std::cout << "==================================================" << std::endl;
        std::cout << "USTED A DECIDIDO CERRAR EL PROGRAMA. ¡HASTA LUEGO!" << std::endl;
        std::cout << "==================================================" << std::endl;
        std::exit(0);
        break;
    }
    system("cls");
  } while(opcion!=7);


}
