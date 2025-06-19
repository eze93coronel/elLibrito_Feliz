#include <iostream>
#include "cuotas.h"
using namespace std;

Cuotas::Cuotas() {
    _mes = 0;
    _anio = 0;
    _idSocio = 0;
    _importe = 0;
}

Cuotas::Cuotas(int mes, int anio, int idSocio, float importe, Fecha fechaPago) {
    setMes(mes);
    setAnio(anio);
    setIdSocio(idSocio);
    setImporte(importe);
    _fechaPago = fechaPago;
}

bool Cuotas::setMes(int mes) {
    if (mes < 1 || mes > 12) {
        cout << "Error: El mes debe estar entre 1 y 12." << endl;
        return false;
    }
    _mes = mes;
    return true;
}

bool Cuotas::setAnio(int anio) {
    if (anio < 1 || anio > 2030) {
        cout << "Error: El año debe estar entre 1 y 2030." << endl;
        return false;
    }
    _anio = anio;
    return true;
}

bool Cuotas::setIdSocio(int idSocio) {
    if (idSocio <= 0) {
        cout << "Error: El ID del socio debe ser mayor a 0." << endl;
        return false;
    }
    _idSocio = idSocio;
    return true;
}

bool Cuotas::setImporte(float importe) {
    if (importe < 0) {
        cout << "Error: El importe no puede ser negativo." << endl;
        return false;
    }
    _importe = importe;
    return true;
}

void Cuotas::setFechaPago(Fecha fecha) {
    _fechaPago = fecha;
}

int Cuotas::getMes() {
    return _mes;
}

int Cuotas::getAnio() {
    return _anio;
}

int Cuotas::getIdSocio() {
    return _idSocio;
}

float Cuotas::getImporte() {
    return _importe;
}
Fecha Cuotas::getFechaPago() {
    return _fechaPago;
}
