#ifndef PRESTAMOS_H
#define PRESTAMOS_H
#pragma once
#include "Fecha.h"
#include <string>

class Prestamos {
private:
    int _idPrestamo;
    int _idSocio;
    char _isbn[14];
    Fecha _fechaPrestamo;
    Fecha _fechaDevolucion;
    bool _devuelto;


public:
    Prestamos();
    Prestamos(int idPrestamo, int idSocio, std::string isbn, Fecha fPrestamo, Fecha fDevolucion, bool devuelto);

    void setIdPrestamo(int idPrestamo);
    void setIdSocio(int idSocio);
    void setISBN(std::string isbn);
    void setFechaPrestamo(Fecha fecha);
    void setFechaDevolucion(Fecha fecha);
    void setDevuelto(bool d);


    int getIdPrestamo();
    int getIdSocio();
    std::string getISBN();
    Fecha getFechaPrestamo();
    Fecha getFechaDevolucion();
    bool getDevuelto();


    std::string mostrarPrestamoPantalla();
    void getFechaPrestamoStr();
    void getFechaDevolucionStr();
    int contarPrestamosPorSocio(int idSocio);

};

#endif // PRESTAMOS_H
