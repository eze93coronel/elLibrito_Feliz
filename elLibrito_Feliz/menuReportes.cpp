#include "MenuReportes.h"
#include "Reportes.h"
#include <iostream>
using namespace std;

void menuReportes::mostrarMenuReportes()
{
    Reportes rep;
    int opcion;

    do
    {
        system("cls");
        cout << " SUBMENU DE REPORTES" << endl;
        cout << "1. STOCK ACTUAL DE LIBROS" << endl;
        cout << "2. PRESTAMOS" << endl;
        cout << "3. SOCIOS CON PRESTAMOS" << endl;
        cout << "0. VOLVER AL MENÚ PRINCIPAL" << endl;
        cout << "SELECCIONE UNA OPCION: ";
        cin >> opcion;

        system("cls");
        switch (opcion)
        {
        case 1:
            rep.stockActual();
            break;
        case 2:
            rep.prestamos();
            break;
        case 3:
            rep.deudores();
            break;
        }
    }
    while (opcion != 0);
}
