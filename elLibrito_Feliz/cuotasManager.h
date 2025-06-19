#pragma once

class cuotasManager {
private:
    const char* archivo = "archivos/cuotas.dat";

public:
    void registrarPagoCuota();
    void listarCuotas();

};
