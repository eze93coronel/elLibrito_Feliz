#ifndef FUNCIONESAUXILIARES_H_INCLUDED
#define FUNCIONESAUXILIARES_H_INCLUDED
#pragma once
std::string toLower(const std::string& s);
int contarRegistros(const std::string& rutaArchivo, int tamanioRegistro);
bool leerRegistroBinario(void* destino, int tamanioRegistro, int pos, const std::string& rutaArchivo);

#endif // FUNCIONESAUXILIARES_H_INCLUDED
