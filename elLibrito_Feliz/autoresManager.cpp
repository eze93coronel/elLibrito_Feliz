#include <iostream>
#include <string>
#include <cstring>
#include "autores.h"
#include "autoresManager.h"
#include "funcionesAuxiliares.h"
#include <iomanip>
using namespace std ;

autoresManager::autoresManager() {
    _autoresManager = "archivos/autores.dat";
}

autoresManager::autoresManager(std::string autoresManager) {
    this->_autoresManager = autoresManager;
}

void autoresManager::listarAutores() {
    FILE* archivo = fopen(_autoresManager.c_str(), "rb");
    if (archivo == nullptr) {
        std::cout << "No se pudo abrir el archivo de autores." << std::endl;
        return;
    }

    Autores a;
    cout << sizeof(Autores) << endl;

    std::cout << left
              << std::setw(10) << "ID"
              << std::setw(40) << "Nombre del Autor"
              << std::endl;
    std::cout << std::setfill('-') << std::setw(50) << "-" << std::setfill(' ') << std::endl;

    while (fread(&a, sizeof(Autores), 1, archivo) == 1) {
        std::cout << left
                  << std::setw(10) << a.getIdAutor()
                  << std::setw(40) << a.getNombreAutor()
                  << std::endl;
    }

    fclose(archivo);
}

int autoresManager::obtenerSiguienteIdAutor() {
    FILE* f = fopen(_autoresManager.c_str(), "rb");
    if (!f) {
        return 1;  // Empezamos desde 1 si el archivo no existe
    }

    Autores a;
    int maxId = 0;
    while (fread(&a, sizeof(Autores), 1, f) == 1) {
        if (a.getIdAutor() > maxId) {
            maxId = a.getIdAutor();
        }
    }
    fclose(f);
    return maxId + 1;
}

Autores autoresManager::leerAutor(int pos) {
    Autores a;
    leerRegistroBinario(&a, sizeof(Autores), pos, _autoresManager);
    return a;
}

int autoresManager::getCantidadRegistros() {
    return contarRegistros(_autoresManager, sizeof(Autores)); }

    std::string autoresManager::buscarNombrePorId(int idBuscado) {
    int totalAutores = getCantidadRegistros();
    for (int i = 0; i < totalAutores; i++) {
        Autores a = leerAutor(i);
        if (a.getIdAutor() == idBuscado) {
            return a.getNombreAutor();
        }
    }
    return "Desconocido";
}
