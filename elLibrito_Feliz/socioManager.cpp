#include <iostream>
#include "socioManager.h"
#include "Socio.h"
#include "sociosArchivos.h"
#include "Fecha.h"
#include "funcionesAuxiliares.h"
#include "cuotasManager.h"
#include "cuotas.h"
#include "prestamosManager.h"

using namespace std ;

void socioManager::cargarSocio() {
    sociosArchivos archivoSocio;
    Socio socio;
    Fecha nacimiento;
    string nombre, apellido, dni, telefono, direccion, email;

    cout << "== NOMBRE ==: ";
    getline(cin, nombre);

    cout << "== APELLIDO ==: ";
    getline(cin, apellido);

    // Validar que no se repita el DNI
    do {
        cout << "== DNI ==: ";
        getline(cin, dni);

        if (!dniExiste("archivos/socios.dat", dni)) break;

        cout << "Ya existe un socio con ese DNI." << endl;
        cout << "1) Ingresar otro DNI" << endl;
        cout << "2) Cancelar y volver al menú" << endl;
        int opcion = leerOpcionRango(1, 2, "Seleccione: ");
        if (opcion == 2) return;
    } while (true);

    cout << "== TELEFONO ==: ";
    getline(cin, telefono);

    cout << "== DIRECCION ==: ";
    getline(cin, direccion);

    cout << "== EMAIL ==: ";
    getline(cin, email);

    cout << "== FECHA DE NACIMIENTO ==" << endl;
    nacimiento = leerFechaValida();


    int nuevoID = archivoSocio.getCantidadRegistroSocio() + 1;

    socio.setNumeroSocio(nuevoID);
    socio.setNombre(nombre);
    socio.setApellido(apellido);
    socio.setDni(dni);
    socio.setTelefono(telefono);
    socio.setDireccion(direccion);
    socio.setEmail(email);
    socio.setFecha(nacimiento);
    socio.setDeudor(false);

    if (archivoSocio.guardarArchivoSocio(socio)) {
        cout << endl;
        cout << "******************************" << endl;
        cout << "Socio registrado exitosamente." << endl;
        cout << "******************************" << endl << endl;
    } else {
        cout << "- - - - - - - - - - - - - -" << endl << endl;
        cout << "Error al guardar el socio." << endl;
        cout << "- - - - - - - - - - - - - -" << endl << endl;
    }

    cout << endl;
    cout << "DATOS DEL SOCIO REGISTRADO: " << endl;
    cout << "===============================" << endl;
    socio.mostrarSocioPantalla();

}

void socioManager::listarSocios(){
    sociosArchivos archivoSocio;
    Socio socio;
    int totalRegistrosSocio = archivoSocio.getCantidadRegistroSocio();
    for (int i = 0; i<totalRegistrosSocio; i++){
        socio = archivoSocio.LeerSocio(i);
        cout << "=== LISTA DE SOCIOS DE LA BIBLIOTECA FELIZ == " << endl;
        cout << " NOMBRE : " << socio.getNombre() << endl;
        cout << " APELLIDO : "<< socio.getApellido() << endl;
        cout << " N° DE SOCIO : "<< socio.getNumeroSocio() << endl;
        cout << " DNI : " << socio.getDni()<< endl;
        cout << " DIRECCION : " << socio.getDireccion()<< endl;
        cout << " EMAIL : " << socio.getEmail() << endl;
        cout << " FECHA : " ;
        socio.getFecha(); cout << endl;
        cout << "=============================================" << endl;
    }
}

void socioManager::buscarSocio() {
    sociosArchivos archivoSocio;
    Socio socio;
    int numeroSocio;
    char repetir;

    do {
        cout << "Ingrese un número de socio: ";
        cin >> numeroSocio;

        int pos = archivoSocio.buscarArchivoSocio(numeroSocio);

        if (pos >= 0) {
            socio = archivoSocio.LeerSocio(pos);
            cout << "== DATOS DEL SOCIO ==" << endl;
            socio.mostrarSocioPantalla();
            system("pause");
            return;
        } else {
            cout << "No se encontró un socio con ese número." << endl;
            cout << "¿Desea intentar con otro ID? (s/n): ";
            cin >> repetir;
            repetir = tolower(repetir);
        }
    } while (repetir == 's');
}

void socioManager::modificarSocio() {
    sociosArchivos archivoSocio;
    Socio socio;
    int numeroSocio;

    cout << "Ingrese el número de socio a modificar: ";
    cin >> numeroSocio;

    int pos = archivoSocio.buscarArchivoSocio(numeroSocio);
    if (pos == -1) {
        cout << "No existe socio con ese número." << endl;
        return;
    }

    socio = archivoSocio.LeerSocio(pos);
    cout << "== DATOS ACTUALES DEL SOCIO ==" << endl;
    socio.mostrarSocioPantalla();

    string nuevoValor;
    char opcionContinuar;
    int opcion;

    do {
        cout << "===============================" << endl;
        cout << "¿QUÉ DATO DESEA MODIFICAR?" << endl;
        cout << "1) Nombre" << endl;
        cout << "2) Apellido" << endl;
        cout << "3) DNI" << endl;
        cout << "4) Teléfono" << endl;
        cout << "5) Dirección" << endl;
        cout << "6) Email" << endl;
        cout << "7) Fecha de alta" << endl;
        cout << "8) Deudor (si/no)" << endl;
        cout << "0) Volver al menú" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1:
                cout << "Ingrese nuevo NOMBRE: ";
                getline(cin, nuevoValor);
                socio.setNombre(nuevoValor);
                break;
            case 2:
                cout << "Ingrese nuevo APELLIDO: ";
                getline(cin, nuevoValor);
                socio.setApellido(nuevoValor);
                break;
            case 3:
                cout << "Ingrese nuevo DNI: ";
                getline(cin, nuevoValor);
                socio.setDni(nuevoValor);
                break;
            case 4:
                cout << "Ingrese nuevo TELÉFONO: ";
                getline(cin, nuevoValor);
                socio.setTelefono(nuevoValor);
                break;
            case 5:
                cout << "Ingrese nueva DIRECCIÓN: ";
                getline(cin, nuevoValor);
                socio.setDireccion(nuevoValor);
                break;
            case 6:
                cout << "Ingrese nuevo EMAIL: ";
                getline(cin, nuevoValor);
                socio.setEmail(nuevoValor);
                break;
            case 7: {
                cout << "Ingrese nueva FECHA DE ALTA:" << endl;
                Fecha nuevaFecha = leerFechaValida();
                socio.setFecha(nuevaFecha);
                break;
            }
            case 8: {
                string deudorInput;
                cout << "¿Es deudor? (si/no): ";
                getline(cin, deudorInput);
                bool deudor = (deudorInput == "si" || deudorInput == "SI");
                socio.setDeudor(deudor);
                break;
            }
            case 0:
                cout << "Volviendo al menú anterior..." << endl;
                return;
            default:
                cout << "Opción inválida." << endl;
                continue;
        }

        // Guardar el cambio
        int resultado = archivoSocio.modificarSocio(socio, pos);
        if (resultado > 0) {
            cout << "Dato modificado correctamente." << endl;
        } else {
            cout << "Error al modificar el dato." << endl;
        }

        cout << "¿Desea modificar otro dato de este socio? (s/n): ";
        cin >> opcionContinuar;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    } while (tolower(opcionContinuar) == 's');
}


bool socioManager::dniExiste(const char* rutaArchivo, const std::string& dni) {
    FILE* f = abrirArchivo(rutaArchivo, "rb");
    if (!f) return false;

    Socio s;
    while (fread(&s, sizeof(Socio), 1, f) == 1) {
        if (dni == s.getDni()) {
            fclose(f);
            return true;
        }
    }

    fclose(f);
    return false;
}

void socioManager::resumenSocios() {
    sociosArchivos archivoSocio;
    prestamosManager pManager;
    Cuotas cuota;
    Socio socio;
    FILE* fCuotas = fopen("archivos/cuotas.dat", "rb");
    if (fCuotas == nullptr) {
        cout << "Error al abrir el archivo de cuotas." << endl;
        return;
    }

    int totalSocios = archivoSocio.getCantidadRegistroSocio();

    for (int i = 0; i < totalSocios; i++) {
        socio = archivoSocio.LeerSocio(i);
        int id = socio.getNumeroSocio();

        // Contar préstamos
        int prestamosActivos = pManager.contarPrestamosActivosPorSocio(id);

        // Buscar la fecha del último pago
        Fecha ultimaFecha;
        Cuotas c;
        while (fread(&c, sizeof(Cuotas), 1, fCuotas) == 1) {
            if (c.getIdSocio() == id && esMayorFecha(c.getFechaPago(), ultimaFecha)) {
                ultimaFecha = c.getFechaPago();
            }
        }
        rewind(fCuotas);  // volver a empezar para el siguiente socio

        // Mostrar resumen
        cout << "===============================" << endl;
        cout << "ID SOCIO: " << id << endl;
        cout << "NOMBRE: " << socio.getNombre() << " " << socio.getApellido() << endl;
        if (prestamosActivos == 0) {
            cout << "LIBROS PRESTADOS: Ninguno" << endl;
        } else {
            cout << "LIBROS PRESTADOS: " << prestamosActivos << endl;
        }
        cout << "ES DEUDOR: " << socio.mostrarDeudor() << endl;
        cout << "ULTIMO PAGO: " << ultimaFecha.toString() << endl;
    }

    fclose(fCuotas);
}


/// METODOS CREADOS POR EZE
/*
void socioManager::cargarCantidadRegistroSocio()
{
    sociosArchivos archivoSocio;

    int cantidadDeRegistros = archivoSocio.getCantidadRegistroSocio();

    cout << "la cantidad de registros que tiene el archivo son : " << cantidadDeRegistros << endl;
}

*/
