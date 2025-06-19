#include <iostream>
#include <regex>
#include <algorithm>
#include <cctype>
#include <string>
#include <cstdio>
#include <limits>
#include "Fecha.h"
#include "funcionesAuxiliares.h"
#include <ctime>

using namespace std;

/****FUNCIONES COMUNES A TODOS LOS ARCHIVOS****/
FILE* abrirArchivo(const std::string& rutaArchivo, const char* modo) {
    FILE* f = std::fopen(rutaArchivo.c_str(), modo);
    if (!f) {
        std::cerr << "No se pudo abrir el archivo: " << rutaArchivo << std::endl;
        return nullptr;
    }
    return f;
}

bool guardarRegistro(const std::string& rutaArchivo, const void* registro, size_t tamanio) {
    FILE* f = abrirArchivo(rutaArchivo, "ab");
    if (!f) return false;

    bool exito = fwrite(registro, tamanio, 1, f) == 1;
    fclose(f);
    if (exito) {
    std::cout << "EL REGISTRO FUE GUARDADO CORRECTAMENTE" << std::endl;}
    else {
    std::cout << "ERROR: NO SE PUDO GUARDAR EL REGISTRO" << std::endl;}
    return exito;
}

int contarRegistros(const std::string& rutaArchivo, int tamanioRegistro) {
        FILE* f = abrirArchivo(rutaArchivo, "rb");
        fseek(f, 0, SEEK_END);
        int totalBytes = ftell(f);
        fclose(f);

    return totalBytes / tamanioRegistro;
}

bool leerRegistroBinario(void* destino, int tamanioRegistro, int pos, const std::string& rutaArchivo) {
    FILE* archivo = abrirArchivo(rutaArchivo, "rb");

    fseek(archivo, tamanioRegistro * pos, SEEK_SET);
    bool exito = fread(destino, tamanioRegistro, 1, archivo) == 1;
    fclose(archivo);
    return exito;
}

/***FUNCIONES COMUNES PARA MANEJO DE FECHAS Y BUSQUEDAS DE STRINGS***/
std::string toLower(const std::string& s) {
        std::string s_lower = s;
        std::transform(s_lower.begin(), s_lower.end(), s_lower.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        return s_lower;
}

std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (first == std::string::npos) return "";  // Todo espacios

    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(first, (last - first + 1));
}

bool esAnioBisiesto(int anio) {
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}

int diasEnMes(int mes, int anio) {
    switch (mes) {
        case 2: return esAnioBisiesto(anio) ? 29 : 28;
        case 4: case 6: case 9: case 11: return 30;
        default: return 31;
    }
}

Fecha leerFechaValida() {
    int dia, mes, anio;

    // DÍA (se valida después de conocer mes y año, así que por ahora solo se captura)
    while (true) {
        std::cout << "Ingrese DIA: ";
        if (std::cin >> dia && dia >= 1 && dia <= 31) {
            break;
        }
        std::cout << "Error: el día debe estar entre 1 y 31.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // MES
    while (true) {
        std::cout << "Ingrese MES (1-12): ";
        if (std::cin >> mes && mes >= 1 && mes <= 12) {
            break;
        }
        std::cout << "Error: el mes debe estar entre 1 y 12.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // AÑO
    while (true) {
        std::cout << "Ingrese AÑO (1-2030): ";
        if (std::cin >> anio && anio >= 1 && anio <= 2030) {
            break;
        }
        std::cout << "Error: el año debe estar entre 1 y 2030.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int maxDia = diasEnMes(mes, anio);
    if (dia > maxDia) {
        std::cout << "Error: el día " << dia << " no es válido para el mes " << mes << " y año " << anio << ".\n";
        return leerFechaValida();  // volver a pedir todo
    }

    Fecha fecha;
    fecha.setDia(dia);
    fecha.setMes(mes);
    fecha.setAnio(anio);
    return fecha;
}

bool esMayorFecha(const Fecha& a, const Fecha& b) {
    int anioA = const_cast<Fecha&>(a).getAnio();
    int anioB = const_cast<Fecha&>(b).getAnio();

    if (anioA > anioB) return true;
    if (anioA < anioB) return false;

    int mesA = const_cast<Fecha&>(a).getMes();
    int mesB = const_cast<Fecha&>(b).getMes();

    if (mesA > mesB) return true;
    if (mesA < mesB) return false;

    int diaA = const_cast<Fecha&>(a).getDia();
    int diaB = const_cast<Fecha&>(b).getDia();

    return diaA > diaB;
}

int leerOpcionRango(int minimo, int maximo, const std::string& mensaje) {
    int opcion;
    do {
        std::cout << mensaje;
        if (!(std::cin >> opcion)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Debe ingresar un número válido.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (opcion < minimo || opcion > maximo) {
            std::cout << "Opción fuera de rango. Intente nuevamente.\n";
        }
    } while (opcion < minimo || opcion > maximo);

    return opcion;
}

Fecha fechaActual() {
    time_t t = time(nullptr);
    tm* ahora = localtime(&t);

    Fecha f;
    f.setDia(ahora->tm_mday);
    f.setMes(ahora->tm_mon + 1);
    f.setAnio(ahora->tm_year + 1900);

    return f;
}

int compararFechas(Fecha& a, Fecha& b) {
    if (a.getAnio() < b.getAnio()) return -1;
    if (a.getAnio() > b.getAnio()) return 1;

    if (a.getMes() < b.getMes()) return -1;
    if (a.getMes() > b.getMes()) return 1;

    if (a.getDia() < b.getDia()) return -1;
    if (a.getDia() > b.getDia()) return 1;

    return 0; // Las fechas son iguales
}
