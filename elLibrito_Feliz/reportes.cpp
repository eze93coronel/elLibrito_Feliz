#include "reportes.h"
#include "libro.h"
#include "Socio.h"
#include "prestamos.h"
#include "funcionesAuxiliares.h"
#include "Fecha.h"
#include <iostream>
#include <iomanip>
#include <map>

using namespace std;

Reportes::Reportes()
{
    _libroArchivo = "archivos/libros.dat";
    _prestamosArchivo = "archivos/prestamos.dat";
    _socioArchivo = "archivos/socios.dat";
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
    cout << left  << setw(55) << "TITULO"
         << right << setw(10) << "STOCK"
         << setw(12) << "PRESTADOS"
         << setw(15) << "DISPONIBLES" << endl;
    cout << string(72, '-') << endl;
    cout << "===================================================================================" << endl;
    for(int i=0; i<totalRegistrosLibro; i++)
    {
        if(leerRegistroBinario(&l, sizeof(libro), i, "archivos/libros.dat"))
        {
            cout << left  << setw(55) << l.getTitulo()
                 << right << setw(10) << l.getCantidadEjemplares()
                 << setw(12) << l.getlibrosPrestados()
                 << setw(15) << (l.getCantidadEjemplares() - l.getlibrosPrestados())
                 << endl;
        }
    }
    fclose(f);
    system("pause");

}

void Reportes::deudores()
{
    Socio so;
    Prestamos pres;

    FILE* s = abrirArchivo(_socioArchivo, "rb");
    FILE* p = abrirArchivo(_prestamosArchivo, "rb");

    map<int, pair<int, Fecha>> prestamosPendientes;

    int totalRegSocios = contarRegistros(_socioArchivo, sizeof(Socio));
    int totalRegPrestamos = contarRegistros(_prestamosArchivo, sizeof(Prestamos));

    for(int i = 0; i < totalRegPrestamos; i++)
    {
        if(leerRegistroBinario(&pres, sizeof(Prestamos), i, "archivos/prestamos.dat"))
        {
            int id = pres.getIdSocio();
            Fecha f = pres.getFechaDevolucion();

            if (prestamosPendientes.count(id))
            {
                prestamosPendientes[id].first++;  // aumenta la cantidad
                prestamosPendientes[id].second = f;
            }
            else
            {
                prestamosPendientes[id] = std::make_pair(1, f);  // nuevo socio
            }
        }
    }

    cout << "===================================================================================" << endl;
    cout << left
         << setw(12) << "APELLIDO"
         << setw(12) << "NOMBRE"
         << setw(12) << "LIBROS"
         << setw(20) << "FECHA LIMITE" << endl;

    cout << string(56, '-') << endl;
    cout << "===================================================================================" << endl;


    for(int i = 0; i < totalRegSocios; i++)
    {
        if (leerRegistroBinario(&so, sizeof(Socio), i, "archivos/socios.dat"))
        {
            int idSocio = so.getNumeroSocio();

            // Revisar si este socio figura en el map de prestamosPendientes
            if (prestamosPendientes.count(idSocio))
            {
                int cantidadLibros = prestamosPendientes[idSocio].first;
                Fecha fechaLimite = prestamosPendientes[idSocio].second;

                cout << std::left
                     << std::setw(12) << so.getApellido()
                     << std::setw(12) << so.getNombre()
                     << std::setw(12) << cantidadLibros;

                fechaLimite.mostrarFecha();

                cout << std::endl;

            }
        }
    }
    fclose(s);
    fclose(p);
    system("pause");

}

void Reportes::prestamos()
{
    Prestamos pres;

    FILE* p = abrirArchivo(_prestamosArchivo, "rb");
    int totalRegPrestamos = contarRegistros(_prestamosArchivo, sizeof(Prestamos));

    cout << "===================================================================================" << endl;
    std::cout << std::left
              << std::setw(15) << "ISBN"
              << std::setw(12) << "N°SOCIO"
              << std::setw(12) << "ESTADO"
              << std::setw(20) << "FECHA PRESTAMO"
              << std::setw(20) << "FECHA DEVOLUCION"
              << std::endl;

    std::cout << std::string(79, '-') << std::endl;
    cout << "===================================================================================" << endl;

    for (int i = 0; i < totalRegPrestamos; i++)
    {
        if (leerRegistroBinario(&pres, sizeof(Prestamos), i, _prestamosArchivo))
        {
            Fecha fp = pres.getFechaPrestamo();
            Fecha fd = pres.getFechaDevolucion();

            std::string estado = pres.getDevuelto() ? "DEVUELTO" : "EN OSESION";

            cout << left
                 << setw(15) << pres.getISBN()
                 << setw(12) << pres.getIdSocio()
                 << setw(12) << estado
                 << setw(20) << to_string(fp.getDia()) + "/" +
                 to_string(fp.getMes()) + "/" +
                 to_string(fp.getAnio())
                 << setw(20) << to_string(fd.getDia()) + "/" +
                 to_string(fd.getMes()) + "/" +
                 to_string(fd.getAnio())
                 << endl;

        }
    }
    fclose(p);
    system("pause");
}
