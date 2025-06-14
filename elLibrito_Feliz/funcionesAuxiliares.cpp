#include <iostream>
#include <regex>
#include <algorithm>
#include <cctype>
#include <string>
#include <cstdio>

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
