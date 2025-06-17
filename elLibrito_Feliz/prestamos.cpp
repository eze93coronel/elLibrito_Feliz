#include "Prestamos.h"
#include <iostream>
#include <cstring>
using namespace std;

Prestamos::Prestamos() {
    _idPrestamo = 0;
    _idSocio = 0;
    strcpy(_isbn, " ");
    _devuelto = false;
}

Prestamos::Prestamos(int idPrestamo, int idSocio, std::string isbn, Fecha fPrestamo, Fecha fDevolucion, bool devuelto) {
    setIdPrestamo(idPrestamo);
    setIdSocio(idSocio);
    setISBN(isbn);
    setFechaPrestamo(fPrestamo);
    setFechaDevolucion(fDevolucion);
    setDevuelto(devuelto);
}

void Prestamos::setIdPrestamo(int idPrestamo) {
    if (idPrestamo <= 0) {
        cout << "Error: El ID de préstamo debe ser mayor a 0." << endl;
        return;
    }
    _idPrestamo = idPrestamo;
}

void Prestamos::setIdSocio(int idSocio) {
    if (idSocio <= 0) {
        cout << "Error: El ID del socio debe ser mayor a 0." << endl;
        return;
    }
    _idSocio = idSocio;
}

void Prestamos::setISBN(std::string isbn) {
    if (isbn.empty() || isbn.length() >= sizeof(_isbn)) {
        std::cout << "Error: ISBN vacío o demasiado largo." << std::endl;
        return;
    }
    for (char c : isbn) {
        if (!isdigit(c) && c != '-') {
            std::cout << "Error: El ISBN sólo puede contener dígitos o guiones." << std::endl;
            return;
        }
    }
    std::strncpy(_isbn, isbn.c_str(), sizeof(_isbn));
    _isbn[sizeof(_isbn) - 1] = '\0'; // garantiza terminación nula
}

void Prestamos::setFechaPrestamo(Fecha fecha) {
    _fechaPrestamo = fecha;
}

void Prestamos::setFechaDevolucion(Fecha fecha) {
    if (fecha.getAnio() < _fechaPrestamo.getAnio() ||
        (fecha.getAnio() == _fechaPrestamo.getAnio() && fecha.getMes() < _fechaPrestamo.getMes()) ||
        (fecha.getAnio() == _fechaPrestamo.getAnio() && fecha.getMes() == _fechaPrestamo.getMes() && fecha.getDia() < _fechaPrestamo.getDia()))
    {
        cout << "Error: La fecha de devolución no puede ser anterior a la de préstamo." << endl;
        return;
    }
    _fechaDevolucion = fecha;
}

void Prestamos::setDevuelto(bool d) {
    _devuelto = d;
}



int Prestamos::getIdPrestamo() {
    return _idPrestamo;
}

int Prestamos::getIdSocio() {
    return _idSocio;
}

std::string Prestamos::getISBN() {
    return _isbn;
}

Fecha Prestamos::getFechaPrestamo() {
    return _fechaPrestamo;
}

Fecha Prestamos::getFechaDevolucion() {
    return _fechaDevolucion;
}

void Prestamos::getFechaPrestamoStr() {
    _fechaPrestamo.mostrarFecha();
}

void Prestamos::getFechaDevolucionStr() {
    _fechaDevolucion.mostrarFecha();
}

std::string Prestamos::mostrarPrestamoPantalla() {
    std::string str = "";
    str += "ID Préstamo: " + std::to_string(_idPrestamo) + " - ";
    str += "ID Socio: " + std::to_string(_idSocio) + " - ";
    str += "ISBN: " + std::string(_isbn) + " - ";
    str += "Fecha préstamo: ";
    str += std::to_string(_fechaPrestamo.getDia()) + "/";
    str += std::to_string(_fechaPrestamo.getMes()) + "/";
    str += std::to_string(_fechaPrestamo.getAnio()) + " - ";
    str += "Fecha devolución: ";
    str += std::to_string(_fechaDevolucion.getDia()) + "/";
    str += std::to_string(_fechaDevolucion.getMes()) + "/";
    str += std::to_string(_fechaDevolucion.getAnio()) + " - ";
    str += (_devuelto ? "DEVUELTO" : "PENDIENTE");

    std::cout << str << std::endl;
    return str;
}


bool Prestamos::getDevuelto() {
    return _devuelto;
}



