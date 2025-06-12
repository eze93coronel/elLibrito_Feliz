#include <iostream>
#include "menuLibro.h"
#include "libroArchivo.h"

using namespace std ;
void menuLibro::mostrarMenuLibro() {
    libroArchivo aLibro;
    int opcion ;


    do {
    cout << "---------------------------------------" << endl;

    cout << " SUB MENU: LIBROS  " << endl;
    cout << "1. Alta libro " << endl;
    cout << "2. Buscar un libro " << endl;
    cout << "3. Modificar libro "  << endl;
    cout << "4. Prestar libro "  << endl;
    cout << "5. Devolver libro "  << endl;
    cout << "6. Consultar stock "  << endl;
    cout << "7. Volver al menu anterior "  << endl;
    cout << "8. Salir "  << endl;
    cout << "8. Salir "  << endl;


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
            aLibro.cargarLibro();
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
           /*Aca va una función que te pregunte qué queres modificar y de qué libro. Se pueden modificar todos los datos menos la columna de "prestados"*/
        break;

       case 4 :
            std::cout << "===============================" << std::endl;
            std::cout << "PRESTAMOS DE LIBROS" << std::endl;
            std::cout << "==============================="<< std::endl;
            aLibro.prestarLibro();
            system("pause");

        break;
       case 5:
        break;

       case 6:
            std::cout << "===============================" << std::endl;
            std::cout << "STOCK DE LIBROS" << std::endl;
            std::cout << "==============================="<< std::endl;
            aLibro.listarLibros();
            cout << endl;
            cout << "la cantidad de libros registrados es: " << aLibro.getCantidadRegistroLibro() << endl;
            system("pause");

        break;
       case 7:
           return;
       case 8:
        std::cout << "==================================================" << std::endl;
        std::cout << "USTED A DECIDIDO CERRAR EL PROGRAMA. ¡HASTA LUEGO!" << std::endl;
        std::cout << "==================================================" << std::endl;
        std::exit(0);
        break;
    }
    system("cls");
  } while(opcion!=8);


}
