#ifndef AUTORESMANAGER_H
#define AUTORESMANAGER_H

#pragma once
#include <string>
#include "autores.h"

class autoresManager {
private:
    std::string _autoresManager; // Ruta al archivo de libros
public:
    autoresManager(); // Constructor por defecto (usa la ruta por defecto)
    autoresManager(std::string autoresManager); // Constructor parametrizado
    Autores leerAutor(int pos);
    int getCantidadRegistros();
    int obtenerSiguienteIdAutor();
    void listarAutores();
    std::string buscarNombrePorId(int idBuscado);
    int seleccionarOcrearAutorPorNombre();
    int buscarCoincidenciasPorNombre(const std::string& nombreParcial, Autores coincidencias[], int maxCoincidencias);




};


#endif
