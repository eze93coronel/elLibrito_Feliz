#ifndef FUNCIONESAUXILIARES_H_INCLUDED
#define FUNCIONESAUXILIARES_H_INCLUDED
#pragma once
#include <string>
#include <algorithm>
#include <cctype>

#include "Fecha.h"
FILE* abrirArchivo(const std::string& rutaArchivo, const char* modo);
bool guardarRegistro(const std::string& rutaArchivo, const void* registro, size_t tamanio);
int contarRegistros(const std::string& rutaArchivo, int tamanioRegistro);
bool leerRegistroBinario(void* destino, int tamanioRegistro, int pos, const std::string& rutaArchivo);

std::string trim(const std::string& str);
std::string toLower(const std::string& s);
Fecha leerFechaValida();
bool esAnioBisiesto(int anio);
int diasEnMes(int mes, int anio);
int leerOpcionRango(int minimo, int maximo, const std::string& mensaje);

int compararFechas(Fecha& a, Fecha& b);
Fecha fechaActual();
#endif // FUNCIONESAUXILIARES_H_INCLUDED
