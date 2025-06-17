#include <iostream>
#include "Fecha.h"
using namespace std ;

Fecha::Fecha() {
    _dia = 0;
    _mes = 0;
    _anio = 0;

}

Fecha::Fecha(int dia, int mes, int anio) {
    _dia = dia;
    _mes = mes;
    _anio = anio;
}
void Fecha::setDia(int dia) {
     if(dia < 1 || dia > 31  ) {
     std::cout << "Error : el dia debe ser entre 1 y 31 " << std::endl;
     return;
   }
      this -> _dia = dia;
}
void Fecha::setMes(int mes) {
     if(mes <1 || mes > 12) {
       std::cout << "Error : el mes de ser entre 1 y 12. " << std::endl;
       return;
  }
    this -> _mes = mes;
}

void Fecha::setAnio(int anio) {
     if (anio <= 0 || anio > 2030) {
        std::cout << "Error: El año debe estar entre 1 y 2030." << std::endl;
        return; // Salimos sin modificar _anio
    }

    this->_anio = anio; // Asignamos el año válido
}

int Fecha::getDia() {

   return _dia;
}

int Fecha::getMes(){
    return _mes;
}

int Fecha::getAnio(){
     return _anio;
}

void Fecha::cargarFecha() {
 int   dia , mes , anio;
  cout << "INGRESE UNA FECHA PARA EL DIA  ";
  cin >> dia;
  setDia(dia);
  cout << "INGRESE UN NUMERO DE MES " ;
  cin >> mes;
   setMes(mes);
  cout << "INGRESE UN ANIO " ;
  cin >> anio;
  setAnio(anio);
}

void Fecha::mostrarFecha(){
  std::cout <<_dia <<"/" <<_mes <<"/"<<_anio << std::endl;
}



/*std::string Fecha::toString() {
        return std::to_string(_dia) + "/" + std::to_string(_mes) + "/" + std::to_string(_anio) ;
    } */


