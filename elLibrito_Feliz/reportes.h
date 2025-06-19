#ifndef REPORTES_H_INCLUDED
#define REPORTES_H_INCLUDED
#include <string>

class Reportes
{
private:
    std::string _libroArchivo;
    std::string _prestamosArchivo;
    std::string _socioArchivo
public:
    Reportes();
    Reportes(std::string libroArchivo);

    void stockActual();
    void recaudacion(int anio);
    void deudores();
    void prestamos();
};

#endif // REPORTES_H_INCLUDED
