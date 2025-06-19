#pragma once
#include "Fecha.h"
class Cuotas {
    private :
        int _mes;
        int _anio;
        int _idSocio;
        float _importe;
        Fecha _fechaPago;

    public :
        Cuotas();
        Cuotas(int mes,int anio, int idSocio, float importe, Fecha FechaPago);

        bool setMes(int mes);
        bool setAnio(int anio);
        bool setIdSocio(int idSocio);
        bool setImporte(float importe);
        void setFechaPago(Fecha fecha);

        int getMes();
        int getAnio();
        int getIdSocio();
        float getImporte();
        Fecha getFechaPago();
};
