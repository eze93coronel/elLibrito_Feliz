#include <iostream>
#include "Socio.h"
#include "menuLibreria.h"
#include "socioManager.h"
using namespace std;

int main()
{
    menuLibreria menu;
    int opc;
    while(true){
        system("cls");
        cout << "****** BIBLIOTECA EL LIBRITO FELIZ ******" << endl;
        cout << "1. MENU SOCIOS " << endl;
        cout << "2. MENU REPORTES " << endl;
        cout << "3. MENU LIBROS " << endl;
        cout << "4. SALIR  " << endl;
        cout << "************************" << endl;
        cout << "SELECCIONAR OPCION " << endl;
        cin>>opc;
        system("cls");
        switch(opc){
            case 1: menu.mostrarMenuPrincipal();
                    break;
            case 2:
                    break;
            case 0: return 0;
                    break;
            default: cout<<"LA SELECCION NO ES CORRECTA"<<endl;

        }
        system("pause");
    }
    return 0;
}
