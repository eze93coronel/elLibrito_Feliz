#include <iostream>
#include <string>
#include <cstring>
#include <vector>
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

int autoresManager::buscarCoincidenciasPorNombre(const std::string& nombreParcial, Autores coincidencias[], int maxCoincidencias) {
    FILE* archivoAutores = fopen(_autoresManager.c_str(), "rb");
    if (!archivoAutores) return 0;

    Autores a;
    int encontrados = 0;

    while (fread(&a, sizeof(Autores), 1, archivoAutores) == 1 && encontrados < maxCoincidencias) {
        std::string nombre = a.getNombreAutor();
        if (nombre.find(nombreParcial) != std::string::npos) {
            coincidencias[encontrados] = a;
            encontrados++;
        }
    }

    fclose(archivoAutores);
    return encontrados;
}

int autoresManager::seleccionarOcrearAutorPorNombre() {
    std::string nombreAutorInput;
    Autores coincidencias[100];  // Hasta 100 coincidencias permitidas
    int total = 0;

    // Ingreso del nombre o parte del nombre con validación
    do {
        std::cout << "== INGRESE NOMBRE DEL AUTOR (o parte del nombre) ==: ";
        std::getline(std::cin, nombreAutorInput);
        nombreAutorInput = trim(nombreAutorInput);

        if (nombreAutorInput.empty()) {
            std::cout << "El nombre no puede estar vacio. Intente nuevamente." << std::endl;
            continue;
        }

        // Buscar coincidencias
        total = buscarCoincidenciasPorNombre(nombreAutorInput, coincidencias, 100);
        break;

    } while (true);

    // Si hay coincidencias, mostrar opciones
    if (total > 0) {
        std::cout << "=== COINCIDENCIAS ENCONTRADAS ===" << std::endl;
        for (int i = 0; i < total; ++i) {
            std::cout << "[" << i + 1 << "] " << coincidencias[i].getNombreAutor()
                      << " (ID: " << coincidencias[i].getIdAutor() << ")" << std::endl;
        }

        int seleccion;
        do {
            std::cout << "Seleccione una opción (1-" << total << ") o 0 para crear nuevo autor: ";
            std::cin >> seleccion;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } while (seleccion < 0 || seleccion > total);

        if (seleccion != 0) {
            return coincidencias[seleccion - 1].getIdAutor();
        }
    }

    // Crear nuevo autor si no hubo coincidencias o seleccionó 0
    std::string nombreCompleto;
    do {
        std::cout << "No se encontraron coincidencias. Ingrese el nombre completo del nuevo autor: ";
        std::getline(std::cin, nombreCompleto);
        nombreCompleto = trim(nombreCompleto);
    } while (nombreCompleto.empty());

    Autores nuevoAutor;
    int nuevoId = obtenerSiguienteIdAutor();
    nuevoAutor.setIdAutor(nuevoId);
    nuevoAutor.setNombreAutor(nombreCompleto);

    FILE* fa = fopen(_autoresManager.c_str(), "ab");
    if (fa != nullptr) {
        fwrite(&nuevoAutor, sizeof(Autores), 1, fa);
        fclose(fa);
        std::cout << "Nuevo autor guardado con ID: " << nuevoId << std::endl;
    } else {
        std::cout << "Error al guardar nuevo autor." << std::endl;
        return 0;
    }

    return nuevoId;
}

