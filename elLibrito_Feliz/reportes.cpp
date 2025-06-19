#include "reportes.h"
#include "libroArchivo.h"
#include "libro.h"
#include "funcionesAuxiliares.h"
#include <iostream>
#include <iomanip>

using namespace std;

Reportes::Reportes()
{
    _libroArchivo = "archivos/libros.dat";
    _prestamosArchivo = "archivos/prestamos.dat";
    _sociosArchivo = "archivos/socios.dat";
}

Reportes::Reportes(std::string libroArchivo)
{
    _libroArchivo = libroArchivo;
}

void Reportes::stockActual()
{
    libro l;
    FILE* f = abrirArchivo(_libroArchivo, "rb");
    int totalRegistrosLibro = contarRegistros(_libroArchivo, sizeof(libro));

    cout << "===================================================================================" << endl;
    cout << left  << setw(35) << "TITULO"
         << right << setw(10) << "STOCK"
         << setw(12) << "PRESTADOS"
         << setw(15) << "DISPONIBLES" << endl;
    cout << string(72, '-') << endl;
    cout << "===================================================================================" << endl;
    for(int i=0; i<totalRegistrosLibro;i++)
    {
        if(leerRegistroBinario(&l, sizeof(libro), i, "archivos/libros.dat"))
           {
               cout << left  << setw(35) << l.getTitulo()
                << right << setw(10) << l.getCantidadEjemplares()
                << setw(12) << l.getlibrosPrestados()
                << setw(15) << (l.getCantidadEjemplares() - l.getlibrosPrestados())
                << endl;
           }
    }
    fclose(f);
}

void Reportes::deudores()
{
    socio so;
    prestamo pres;

    FILE* s = abrirArchivo(_sociosArchivo, "rb");
    FILE* p = abrirArchivo(_prestamosArchivo, "rb");

    std::map<int, int> prestamosPendientes;

    int totalRegSocios = contarRegistros(_sociosArchivo, sizeof(socio));
    int totalRegPrestamos = contarRegistros(_prestamosArchivo, sizeof(prestamos));



    for(int i=0; i<totalRegPrestamos;i++)
    {
        if(leerRegistroBinario(&pres, sizeof(prestamo), i, "archivos/prestamos.dat"))
        {
            prestamosPendientes[pres.getIdSocio()]++;
        }
    }

     cout << std::left
              << std::setw(12) << "APELLIDO"
              << std::setw(12) << "NOMBRE"
              << std::setw(12) << "DNI"
              << std::setw(14) << "TELEFONO"
              << " -> PRESTAMOS PENDIENTES"  << std::endl;
    cout << std::string(70, '-') << std::endl;


    for(int i=0;i<totalRegSocios;i++)
    {
        if(leerRegistroBinario(&so, sizeof(socio), i, "archivos/socios.dat"))
        {
            int idSocio = so.getNumeroSocio();

            // Revisar si este socio figura en el map de prestamosPendientes
            if (prestamosPendientes.count(idSocio))
            {
                // Si existe, se obtiene la cantidad acumulada
                int cantidad = prestamosPendientes[idSocio];

                // Imprime los datos del socio y la cantidad de préstamos pendientes
                std::cout << std::left
                          << std::setw(12) << so.getApellido()
                          << std::setw(12) << so.getNombre()
                          << std::setw(12) << so.getDni()
                          << std::setw(14) << so.getTelefono()
                          << " -> " << cantidad << " pr\u00e9stamo(s) pendiente(s)"
                          << std::endl;
            }

        }

    }
}
