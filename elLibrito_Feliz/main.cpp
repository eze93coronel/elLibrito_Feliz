#include <iostream>
#include "Socio.h"
#include "menuLibreria.h"
#include "socioManager.h"
#include "menuLibro.h"
#include "libroArchivo.h"
#include <windows.h>

using namespace std;

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    menuLibreria menu;
    menuLibro menuLibro;
    int opc;
    while(true){
        system("cls");
        cout << "****** BIBLIOTECA EL LIBRITO FELIZ ******" << endl;
        cout << "1. MENU SOCIOS " << endl;
        cout << "2. MENU LIBROS  " << endl;
        cout << "3. MENU REPORTES " << endl;
        cout << "4. SALIR  " << endl;
        cout << "************************" << endl;
        cout << "SELECCIONAR OPCION: ";
        cin>>opc;
        system("cls");
        switch(opc){
            case 1: menu.mostrarMenuPrincipal();
                    break;
            case 2:
                   menuLibro.mostrarMenuLibro();
                    break;
            case 3:
                    break;
            case 4:
                std::cout << "==================================================" << std::endl;
                std::cout << "USTED A DECIDIDO CERRAR EL PROGRAMA. ¡HASTA LUEGO!" << std::endl;
                std::cout << "==================================================" << std::endl;
                std::exit(0);
                break;

            default: cout<<"LA SELECCION NO ES CORRECTA"<<endl;

        }
        system("pause");
    }
    return 0;
}
