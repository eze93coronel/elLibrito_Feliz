#ifndef FUNCIONESAUXILIARES_H_INCLUDED
#define FUNCIONESAUXILIARES_H_INCLUDED
#pragma once
#include <string>
#include <algorithm>
#include <cctype>

#include "Fecha.h"

std::string toLower(const std::string& s);
int contarRegistros(const std::string& rutaArchivo, int tamanioRegistro);
bool leerRegistroBinario(void* destino, int tamanioRegistro, int pos, const std::string& rutaArchivo);
std::string trim(const std::string& str);
Fecha leerFechaValida();
bool esAnioBisiesto(int anio);
int diasEnMes(int mes, int anio);
int leerOpcionRango(int minimo, int maximo, const std::string& mensaje);


#endif // FUNCIONESAUXILIARES_H_INCLUDED
