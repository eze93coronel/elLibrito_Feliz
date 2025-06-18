#include <iostream>
#include <cstdio>
#include <vector>
#include <regex>
#include "funcionesAuxiliares.h"
#include "prestamosManager.h"
#include "prestamos.h"


///REVISAR PORQUE NO HACE BIEN LA DEVOLUCIÓN DE LIBROS. NO RESTA NI SUMA DE LA MANERA CORRECTA EN EL ARCHIVO DE LIRBOS.DAT
using namespace std;

prestamosManager::prestamosManager() {
    _prestamosArchivo = "archivos/prestamos.dat";
}

prestamosManager::prestamosManager(string prestamosArchivo) {
    this -> _prestamosArchivo = prestamosArchivo;
}

int prestamosManager::siguienteIdPrestamo() {
    FILE* f = abrirArchivo(_prestamosArchivo, "rb");
    Prestamos p;
    int maxId = 0;

    while (fread(&p, sizeof(Prestamos), 1, f) == 1) {
        if (p.getIdPrestamo() > maxId) {
            maxId = p.getIdPrestamo();
        }
    }

    fclose(f);
    return maxId + 1;
}

void prestamosManager::registrarPrestamo(libroArchivo& archivoLibros) {
    string nombreSocio;
    int idSocio;
    cout << "Nombre del socio: ";
    getline(cin, nombreSocio);
    cout << "ID del socio: ";
    cin >> idSocio;

    libro libroSeleccionado;
    long posicionLibro;
    bool libroValido = false;

    while (!libroValido) {
        int opcion;
        string criterio;
        if (!archivoLibros.elegirCriterioBusqueda(opcion, criterio)) return;

        FILE* archivo = abrirArchivo(archivoLibros.getRutaArchivo(), "rb");
        if (!archivo) return;

        vector<libro> librosCoincidentes;
        vector<long> posiciones;
        libro l;
        long pos = 0;
        string criterioLower = toLower(criterio);

        while (fread(&l, sizeof(libro), 1, archivo) == 1) {
            bool coincide = false;
            if (opcion == 1 && toLower(l.getTitulo()).find(criterioLower) != string::npos) coincide = true;
            if (opcion == 2 && l.getIsbn() == criterio) coincide = true;
            if (opcion == 3) {
                autoresManager manager;
                string autor = manager.buscarNombrePorId(l.getIdAutor());
                if (toLower(autor).find(criterioLower) != string::npos) coincide = true;
            }

            if (coincide) {
                librosCoincidentes.push_back(l);
                posiciones.push_back(pos);
            }
            ++pos;
        }
        fclose(archivo);

        if (librosCoincidentes.empty()) {
            cout << "No se encontraron libros." << endl;
            return;
        }

        archivoLibros.mostrarEncabezadoTablaLibros();
        autoresManager manager;
        for (size_t i = 0; i < librosCoincidentes.size(); ++i) {
            cout << "[" << (i + 1) << "] ";
            archivoLibros.mostrarLibroEnTabla(librosCoincidentes[i], manager);
        }

        size_t seleccion = 0;
        do {
            cout << "Seleccione el libro a prestar (1-" << librosCoincidentes.size() << "): ";
            cin >> seleccion;
        } while (seleccion < 1 || seleccion > librosCoincidentes.size());

        posicionLibro = posiciones[seleccion - 1];
        libroSeleccionado = librosCoincidentes[seleccion - 1];

        int stockDisponible = libroSeleccionado.getCantidadEjemplares() - libroSeleccionado.getlibrosPrestados();
        if (stockDisponible <= 0) {
            cout << "----------------------------------" << endl;
            cout << "No hay stock disponible para este libro." << endl;
            cout << "¿Desea buscar otro libro?" << endl;
            cout << "1) Sí" << endl;
            cout << "2) Cancelar" << endl;
            int opcion = leerOpcionRango(1, 2, "Seleccione: ");
            if (opcion == 2) return;
        }
        else {
            libroValido = true;
        }

    }

    cout << "===============================" << endl;
    cout << "FECHA DE PRÉSTAMO" << endl;
    cout << "===============================" << endl;
    Fecha fechaPrestamo = fechaActual();
    cout << "Fecha préstamo: " << fechaPrestamo.getDia() << "/" << fechaPrestamo.getMes() << "/" << fechaPrestamo.getAnio() << endl;
    Fecha fechaDevolucion = sumar15DiasAFechaPrestamo(fechaPrestamo);

    cout << "===============================" << endl;
    cout << "Resumen del préstamo" << endl;
    cout << "===============================" << endl;
    cout << "Socio: " << nombreSocio << " (ID " << idSocio << ")" << endl;
    cout << "Libro: " << libroSeleccionado.getTitulo() << " (ISBN " << libroSeleccionado.getIsbn() << ")" << endl;
    cout << "Fecha préstamo: " << fechaPrestamo.getDia() << "/" << fechaPrestamo.getMes() << "/" << fechaPrestamo.getAnio() << endl;
    cout << "Fecha devolución: " << fechaDevolucion.getDia() << "/" << fechaDevolucion.getMes() << "/" << fechaDevolucion.getAnio() << endl;

    cout << "¿Desea confirmar el préstamo?" << endl;
    cout << "1) Sí" << endl;
    cout << "2) No" << endl;
    int confirmar = leerOpcionRango(1, 2, "Seleccione: ");
    if (confirmar != 1) {
        cout << "Préstamo cancelado." << endl;
        return;
}

    if (!archivoLibros.registrarPrestamoLibro(posicionLibro)) {
        cout << "Error inesperado al actualizar el stock del libro." << endl;
        return;
    }

    Prestamos p;
    p.setIdPrestamo(siguienteIdPrestamo());
    p.setIdSocio(idSocio);
    p.setISBN(libroSeleccionado.getIsbn());
    p.setFechaPrestamo(fechaPrestamo);
    p.setFechaDevolucion(fechaDevolucion);
    p.setDevuelto(false);


    guardarRegistro(_prestamosArchivo, &p, sizeof(Prestamos));
    cout << "Préstamo registrado correctamente." << endl;
}

void prestamosManager::registrarDevolucion(libroArchivo& archivoLibros) {
    int idSocio;
    cout << "Ingrese el ID del socio: ";
    cin >> idSocio;

    FILE* archivo = abrirArchivo(_prestamosArchivo, "rb+");
    if (!archivo) return;

    vector<Prestamos> prestamosPendientes;
    vector<long> posiciones;
    Prestamos p;
    long pos = 0;

    while (fread(&p, sizeof(Prestamos), 1, archivo) == 1) {
        if (p.getIdSocio() == idSocio && !p.getDevuelto()) {
            prestamosPendientes.push_back(p);
            posiciones.push_back(pos);
        }
        ++pos;
    }

    if (prestamosPendientes.empty()) {
        cout << "No se encontraron préstamos pendientes para este socio." << endl;
        fclose(archivo);
        return;
    }

    cout << "===============================" << endl;
    cout << "PRÉSTAMOS PENDIENTES" << endl;
    cout << "===============================" << endl;

    for (size_t i = 0; i < prestamosPendientes.size(); ++i) {
        std::string isbn = prestamosPendientes[i].getISBN();
        std::string titulo = "Título no encontrado";

        FILE* fLibros = abrirArchivo(archivoLibros.getRutaArchivo(), "rb");
        libro l;
        while (fread(&l, sizeof(libro), 1, fLibros) == 1) {
            if (l.getIsbn() == isbn) {
                titulo = l.getTitulo();
                break;
            }
        }
        fclose(fLibros);

        cout << "[" << (i + 1) << "] ";
        cout << titulo << " | ISBN: " << isbn << " | Fecha préstamo: ";
        prestamosPendientes[i].getFechaPrestamo().mostrarFecha();
    }

    size_t seleccion = 0;
    do {
        cout << "Seleccione el préstamo a devolver (1-" << prestamosPendientes.size() << "): ";
        cin >> seleccion;
    } while (seleccion < 1 || seleccion > prestamosPendientes.size());

    long posSeleccionada = posiciones[seleccion - 1];
    Prestamos prestamoADevolver = prestamosPendientes[seleccion - 1];

    prestamoADevolver.setDevuelto(true);
    fseek(archivo, posSeleccionada * sizeof(Prestamos), SEEK_SET);
    fwrite(&prestamoADevolver, sizeof(Prestamos), 1, archivo);
    fflush(archivo);

    // Actualizar librosPrestados del libro correspondiente
    string isbn = prestamoADevolver.getISBN();
    long posLibro = -1;
    FILE* archLibros = abrirArchivo(archivoLibros.getRutaArchivo(), "rb+");
    libro l;
    long i = 0;

    while (fread(&l, sizeof(libro), 1, archLibros) == 1) {
        if (l.getIsbn() == isbn) {
            posLibro = i;
            break;
        }
        ++i;
    }

    if (posLibro != -1) {
        int prestados = l.getlibrosPrestados();
        if (prestados > 0) {
            l.setlibrosPrestados(prestados - 1);  // ✅ solo restamos si hay prestados
        }

        fseek(archLibros, posLibro * sizeof(libro), SEEK_SET);
        fwrite(&l, sizeof(libro), 1, archLibros);
        fflush(archLibros);

        cout << "Devolución registrada con éxito." << endl;
    } else {
        cout << "Error: no se encontró el libro para actualizar el stock." << endl;
    }

    fclose(archLibros);
    fclose(archivo);
}


Fecha prestamosManager::sumar15DiasAFechaPrestamo(Fecha& f) {
    Fecha nuevaFecha;
    int dia = f.getDia();
    int mes = f.getMes();
    int anio = f.getAnio();

    int diasDelMes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    dia += 15;

    while (dia > diasDelMes[mes - 1]) {
        dia -= diasDelMes[mes - 1];
        mes++;
        if (mes > 12) {
            mes = 1;
            anio++;
        }
    }

    nuevaFecha.setDia(dia);
    nuevaFecha.setMes(mes);
    nuevaFecha.setAnio(anio);

    return nuevaFecha;
}

bool prestamosManager::esFechaPasada(Fecha& f) {
    time_t t = time(nullptr);
    tm* ahora = localtime(&t);
    int diaActual = ahora->tm_mday;
    int mesActual = ahora->tm_mon + 1;
    int anioActual = ahora->tm_year + 1900;

    if (f.getAnio() < anioActual) return true;
    if (f.getAnio() == anioActual && f.getMes() < mesActual) return true;
    if (f.getAnio() == anioActual && f.getMes() == mesActual && f.getDia() < diaActual) return true;

    return false;
}
