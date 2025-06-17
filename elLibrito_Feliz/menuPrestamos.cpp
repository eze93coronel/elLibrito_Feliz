#include <iostream>
#include "menuPrestamos.h"
#include "libroArchivo.h"
#include "autoresManager.h"
#include "prestamosManager.h"
#include "prestamos.h"

using namespace std;

void menuPrestamos::mostrarMenuPrestamos() {
    libroArchivo archivoLibros;
    prestamosManager pm;
    Prestamos p;
    int opcion;
    do {
        cout << "---------------------------------------" << endl;
        cout << " SUB MENU: PRESTAMOS  " << endl;
        cout << "1. Prestar un libro " << endl;
        cout << "2. Devolver un libro " << endl;
        cout << "3. Volver al menu anterior "  << endl;
        cout << "4. Salir "  << endl;
        cout << "---------------------------------------" << endl;
        cout << "ingrese una opcion: ";
        cin >> opcion;
        cin.ignore();
        system("cls");

        switch(opcion){
            case 1:
                cout << "===============================" << endl;
                cout << "         PRESTAMOS" << endl;
                cout << "===============================" << endl;
                cout << endl;

                pm.registrarPrestamo(archivoLibros);
                break;

            case 2:
                cout << "===============================" << endl;
                cout << "       DEVOLUCIONES"  << endl;
                cout << "===============================" << endl;
                cout << endl;
                cout << "INGRESE EL NOMBRE DEL SOCIO O EL ID: " << endl << endl;
                pm.registrarDevolucion(archivoLibros);
                system("pause");
                break;

            case 3:
                return;

            case 4:
                cout << "==================================================" << endl;
                cout << "USTED A DECIDIDO CERRAR EL PROGRAMA. ¡HASTA LUEGO!" << endl;
                cout << "==================================================" << endl;
                exit(0);
                break;
        }
        system("cls");
    } while(opcion != 4);
}
