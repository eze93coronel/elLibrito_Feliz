#include <iostream>
#include <cstdio>
#include "cuotas.h"
#include "Fecha.h"
#include "funcionesAuxiliares.h"
#include "cuotasManager.h"
#include "sociosArchivos.h"  // te faltaba incluir esto
using namespace std;

void cuotasManager::registrarPagoCuota() {
    sociosArchivos archivoSocios;
    Cuotas nuevaCuota;
    Fecha fechaPago;
    int idSocio, mes, anio;
    float importe;

    cout << "== REGISTRO DE PAGO DE CUOTA ==" << endl;
    cout << "Ingrese el ID del socio: ";
    cin >> idSocio;

    int pos = archivoSocios.buscarArchivoSocio(idSocio);
    if (pos == -1) {
        cout << "No existe un socio con ese ID." << endl;
        return;
    }

    cout << "Mes de la cuota (1-12): ";
    cin >> mes;

    cout << "Año de la cuota (hasta 2030): ";
    cin >> anio;

    cout << "Importe abonado: ";
    cin >> importe;

    cout << "== FECHA DE PAGO ==" << endl;
    fechaPago.cargarFecha();

    // Validaciones
    if (!nuevaCuota.setIdSocio(idSocio) ||
        !nuevaCuota.setMes(mes) ||
        !nuevaCuota.setAnio(anio) ||
        !nuevaCuota.setImporte(importe)) {
        cout << "Error en los datos ingresados. No se registrará la cuota." << endl;
        return;
    }

    nuevaCuota.setFechaPago(fechaPago);

    FILE* f = fopen("archivos/cuotas.dat", "ab");
    if (f == nullptr) {
        cout << "No se pudo abrir el archivo para escritura." << endl;
        return;
    }

    fwrite(&nuevaCuota, sizeof(Cuotas), 1, f);
    fclose(f);

    cout << "Cuota registrada exitosamente." << endl;
}

void cuotasManager::listarCuotas() {
    Cuotas cuota;
    FILE* f = fopen(archivo, "rb");

    if (f == nullptr) {
        cout << "No se pudo abrir el archivo de cuotas." << endl;
        return;
    }

    cout << "=== LISTADO DE CUOTAS ===" << endl;
    while (fread(&cuota, sizeof(Cuotas), 1, f) == 1) {
        cout << "ID Socio: " << cuota.getIdSocio() << endl;
        cout << "Mes/Año de cuota: " << cuota.getMes() << "/" << cuota.getAnio() << endl;
        cout << "Importe: $" << cuota.getImporte() << endl;
        cout << "Fecha de pago: " << cuota.getFechaPago().toString() << endl;
        cout << "------------------------------" << endl;
    }

    fclose(f);
}
