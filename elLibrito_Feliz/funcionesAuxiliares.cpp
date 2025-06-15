#include <iostream>
#include <regex>
#include <algorithm>
#include <cctype>
#include <string>
#include <cstdio>
#include <limits>
#include "Fecha.h"

using namespace std;

std::string toLower(const std::string& s) {
        std::string s_lower = s;
        std::transform(s_lower.begin(), s_lower.end(), s_lower.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        return s_lower;
}

int contarRegistros(const std::string& rutaArchivo, int tamanioRegistro) {
    FILE* archivo = fopen(rutaArchivo.c_str(), "rb");
    if (!archivo) return 0;

    fseek(archivo, 0, SEEK_END);
    int totalBytes = ftell(archivo);
    fclose(archivo);

    return totalBytes / tamanioRegistro;
}

bool leerRegistroBinario(void* destino, int tamanioRegistro, int pos, const std::string& rutaArchivo) {
    FILE* archivo = fopen(rutaArchivo.c_str(), "rb");
    if (!archivo) {
        std::cout << "Error: No se pudo abrir el archivo: " << rutaArchivo << std::endl;
        return false;
    }

    fseek(archivo, tamanioRegistro * pos, SEEK_SET);
    bool exito = fread(destino, tamanioRegistro, 1, archivo) == 1;
    fclose(archivo);
    return exito;
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
        std::cout << "Ingrese ANIO (1-2030): ";
        if (std::cin >> anio && anio >= 1 && anio <= 2030) {
            break;
        }
        std::cout << "Error: el año debe estar entre 1 y 2030.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Validación final del día con el mes y año ya conocidos
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

