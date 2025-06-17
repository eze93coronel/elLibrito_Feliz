#ifndef PRESTAMOSMANAGER_H
#define PRESTAMOSMANAGER_H
#pragma once
#include <string>
#include "Prestamos.h"
#include "libroArchivo.h"

class prestamosManager {
private:
    std::string _prestamosArchivo;
    Fecha sumar15DiasAFechaPrestamo(Fecha& f);

public:
    prestamosManager();
    prestamosManager(std::string prestamosManager);

    void registrarPrestamo(libroArchivo& archivoLibros);
    void registrarDevolucion(libroArchivo& archivoLibros);
    int siguienteIdPrestamo();

    bool esFechaPasada(Fecha& f);



    // Prestamos buscarPorId(int id);
    // bool actualizarPrestamo(const Prestamos& p);
};

#endif // PRESTAMOSMANAGER_H

