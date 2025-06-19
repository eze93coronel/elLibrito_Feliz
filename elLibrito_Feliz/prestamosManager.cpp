#include <iostream>
#include <cstdio>
#include <vector>
#include <regex>
#include "funcionesAuxiliares.h"
#include "prestamosManager.h"
#include "prestamos.h"
#include "sociosArchivos.h"
#include "Socio.h"
using namespace std;

prestamosManager::prestamosManager() {
    _prestamosArchivo = "archivos/prestamos.dat";
}

prestamosManager::prestamosManager(string prestamosArchivo) {
    this -> _prestamosArchivo = prestamosArchivo;
}

void prestamosManager::registrarPrestamo(libroArchivo& archivoLibros) {
    int idSocio;
    cout << "Ingrese el ID del socio: ";
    cin >> idSocio;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    sociosArchivos archivoSocios;
    Socio socioBuscado;
    if (!archivoSocios.buscarSocioPorId(idSocio, socioBuscado)) {
        cout << "No existe un socio con ese ID. Debe ingresar un ID válido." << endl;
        return;
    }
    cout << "----------------------------------" << endl;
    cout << "SOCIO ENCONTRADO:" << endl;
    cout << "----------------------------------" << endl;
    socioBuscado.mostrarSocioPantalla();
    int librosEnPrestamo = contarPrestamosActivosPorSocio(idSocio);
    cout << "----------------------------------" << endl;
    cout << "Libros actualmente en préstamo: " << librosEnPrestamo << endl;
    cout << "----------------------------------" << endl;

    cout << endl;

    libro libroSeleccionado;
    long posicionLibro;
    bool libroValido = false;

    while (!libroValido) {
        int opcion;
        string criterio;
        if (!archivoLibros.elegirCriterioBusqueda(opcion, criterio)) return;

        FILE* archivo = abrirArchivo(archivoLibros.getRutaArchivo(), "rb");
        if (archivo == nullptr) return;

        fseek(archivo, 0, SEEK_END);
        long totalRegistros = ftell(archivo) / sizeof(libro);
        rewind(archivo);

        libro* coincidencias = new libro[totalRegistros];
        long* posiciones = new long[totalRegistros];
        int encontrados = 0;
        long pos = 0;
        libro l;

        std::regex patron(criterio, std::regex_constants::icase);

        while (fread(&l, sizeof(libro), 1, archivo) == 1) {
            bool coincide = false;
            if (opcion == 1 && std::regex_search(l.getTitulo(), patron)) coincide = true;
            if (opcion == 2 && l.getIsbn() == criterio) coincide = true;
            if (opcion == 3) {
                autoresManager manager;
                string autor = manager.buscarNombrePorId(l.getIdAutor());
                if (std::regex_search(autor, patron)) coincide = true;
            }

            if (coincide) {
                coincidencias[encontrados] = l;
                posiciones[encontrados] = pos;
                encontrados++;
            }
            pos++;
        }
        fclose(archivo);

        if (encontrados == 0) {
            cout << "No se encontraron libros." << endl;
            delete[] coincidencias;
            delete[] posiciones;
            return;
        }

        archivoLibros.mostrarEncabezadoTablaLibros();
        autoresManager manager;
        for (int i = 0; i < encontrados; i++) {
            cout << "[" << (i + 1) << "] ";
            archivoLibros.mostrarLibroEnTabla(coincidencias[i], manager);
        }

        int seleccion = 0;
        do {
            cout << "Seleccione el libro a prestar (1-" << encontrados << "): ";
            cin >> seleccion;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } while (seleccion < 1 || seleccion > encontrados);

        posicionLibro = posiciones[seleccion - 1];
        libroSeleccionado = coincidencias[seleccion - 1];

        delete[] coincidencias;
        delete[] posiciones;

        int stockDisponible = libroSeleccionado.getCantidadEjemplares() - libroSeleccionado.getlibrosPrestados();
        if (stockDisponible <= 0) {
            cout << "----------------------------------" << endl;
            cout << "No hay stock disponible para este libro." << endl;
            cout << "¿Desea buscar otro libro?" << endl;
            cout << "1) Sí" << endl;
            cout << "2) No" << endl;
            int confirmar = leerOpcionRango(1, 2, "Seleccione: ");
            if (opcion == 2) return;
        }
        else {
            libroValido = true;
        }
    }
    Fecha fechaPrestamo = fechaActual();
    Fecha fechaDevolucion = sumar15DiasAFechaPrestamo(fechaPrestamo);

    cout << "===============================" << endl;
    cout << "Resumen del préstamo" << endl;
    cout << "===============================" << endl;
    cout << "Socio: " << socioBuscado.getNombre() << " " << socioBuscado.getApellido()
         << " (ID " << idSocio << ")" << endl;
    cout << "Libro: " << libroSeleccionado.getTitulo() << " (ISBN " << libroSeleccionado.getIsbn() << ")" << endl;
    cout << "Fecha préstamo: " << fechaPrestamo.getDia() << "/" << fechaPrestamo.getMes() << "/" << fechaPrestamo.getAnio() << endl;
    cout << "Fecha devolución: " << fechaDevolucion.getDia() << "/" << fechaDevolucion.getMes() << "/" << fechaDevolucion.getAnio() << endl;

    cout << "----------------------------------" << endl;
    cout << "¿Desea confirmar el prestamos? " << endl;
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
    p.setIdPrestamo(contarRegistros("archivos/prestamos.dat", sizeof(p)) + 1);
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

int prestamosManager::contarPrestamosActivosPorSocio(int idSocio) {
    FILE* f = abrirArchivo(_prestamosArchivo, "rb");
    if (f == nullptr) return 0;

    Prestamos p;
    int contador = 0;

    while (fread(&p, sizeof(Prestamos), 1, f) == 1) {
        if (p.getIdSocio() == idSocio && !p.getDevuelto()) {
            contador++;
        }
    }

    fclose(f);
    return contador;
}

///
/*int prestamosManager::siguienteIdPrestamo() {
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
*/
