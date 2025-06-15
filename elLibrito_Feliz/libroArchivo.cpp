#include <limits>
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <regex>
#include <vector>
#include <algorithm>
#include "libroArchivo.h"
#include "libro.h"
#include "funcionesAuxiliares.h"
#include "autores.h"
#include "autoresManager.h"
using namespace std;

libroArchivo::libroArchivo() {
    _libroArchivo = "archivos/libros.dat";
}

libroArchivo::libroArchivo(std::string libroArchivo){
       this -> _libroArchivo = libroArchivo;
}

///1. GUARDAR UN NUEVO LIBRO
void libroArchivo::NuevoLibro() {
    libroArchivo archivo;
    libro l;
    autoresManager managerAutores;

    std::string isbn, titulo;
    int cantidad;

    // === ISBN ===
    libro libroExistente;
    do {
        std::cout << "== ISBN ==: ";
        std::getline(std::cin, isbn);
        isbn = trim(isbn);

        if (isbn.empty()) {
            std::cout << "El ISBN no puede estar vacío.\n";
            continue;
        }

        if (existeIsbn(isbn, libroExistente)) {
            std::cout << "YA EXISTE UN LIBRO CON ESE ISBN.\n"
                      << "Título: " << libroExistente.getTitulo() << "\n";
            return;  // Cancelar carga
        }

        if (l.setIsbn(isbn)) break;

        std::cout << "ISBN inválido. Intente nuevamente.\n";
    } while (true);

    // === Título ===
    do {
        std::cout << "== TITULO (max 50 caracteres) ==: ";
        std::getline(std::cin, titulo);
        titulo = trim(titulo);
        if (titulo.empty()) {
            std::cout << "El título no puede estar vacío.\n";
            continue;
        }
        if (l.setTitulo(titulo)) break;

        std::cout << "Título inválido o demasiado largo.\n";
    } while (true);

    // === Autor ===
    int id_Autor = managerAutores.seleccionarOcrearAutorPorNombre();
    if (id_Autor == 0) {
        std::cout << "Error al seleccionar o crear el autor. Cancelando.\n";
        return;
    }
    l.setIdAutor(id_Autor);

    // === Cantidad de ejemplares ===
    do {
        std::cout << "== CANTIDAD DE EJEMPLARES ==: ";
        if (!(std::cin >> cantidad)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Debe ingresar un numero.\n";
            continue;
        }
        if (cantidad > 0) {
            l.setCantidadEjemplares(cantidad);
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        std::cout << "La cantidad debe ser mayor a cero.\n";
    } while (true);

    // === Fecha ===
    std::cout << "== FECHA DE PUBLICACION ==" << std::endl;
    Fecha fecha = leerFechaValida();
    l.setFechaPublicacion(fecha);
    std::cout << "===============================" << std::endl;

    if (archivo.guardarLibro(l)) {
        std::cout << "EL LIBRO FUE GUARDADO CORRECTAMENTE" << std::endl;
    } else {
        std::cout << "ERROR: NO SE PUDO GUARDAR EL LIBRO" << std::endl;
    }
}

///2.  ESTA FUNCION SIRVE PARA MOSTRAR EL LIBRO EN LA POSICIÓN SELECCIONADA, A FUTURO DEBERÍA CAMBIARSE PARA QUE EN VEZ DE TOMAR LA POSICIÓN TOME EL TÍTULO, EL ISBN O EL AUTOR.
void libroArchivo::buscarLibro() {
    int opc;
    std::string criterio;

    if (!elegirCriterioBusqueda(opc, criterio)) {
        return;
    }

    FILE* f = std::fopen(_libroArchivo.c_str(), "rb");
    if (!f) {
        std::cout << "No se pudo abrir el archivo de libros." << std::endl;
        return;
    }

    std::regex patron;
    std::string criterioLow = toLower(criterio);
    if (opc == 1 || opc == 3) {
        patron = std::regex(criterioLow, std::regex_constants::icase);
    }

    system("cls");
    mostrarEncabezadoTablaLibros();

    libro l;
    autoresManager manager;
    bool noEncontrado = false;

    while (std::fread(&l, sizeof(libro), 1, f) == 1) {
        bool coincidencia = false;
        if (opc == 1) {
            coincidencia = std::regex_search(toLower(l.getTitulo()), patron);
        } else if (opc == 2) {
            coincidencia = (l.getIsbn() == criterio);
        } else if (opc == 3) {
            std::string nombreAutor = manager.buscarNombrePorId(l.getIdAutor());
            coincidencia = std::regex_search(toLower(nombreAutor), patron);
        }

        if (coincidencia) {
            mostrarLibroEnTabla(l, manager);
            noEncontrado = true;
        }
    }

    std::fclose(f);

    if (!noEncontrado) {
        std::cout << "No se encontraron libros para esos criterios" << std::endl;
    }
}

///3. PRESTAR LIBROS
void libroArchivo::prestarLibro(){
    int opc = 0;
    std::string criterio;
    if (!elegirCriterioBusqueda(opc, criterio)) {
        return;
    }
    FILE* f = std::fopen(_libroArchivo.c_str(), "rb");
    if (!f) {
        std::cerr << "No se pudo abrir el archivo de libros." << std:: endl;
        return;
    }

    std::vector<std::pair<libro, long>> matches;
    libro l;
    long pos = 0;
    std::regex patron;
    std::string criterioLow = toLower(criterio);
    if (opc == 1) {
        patron = std::regex(criterioLow, std::regex_constants::icase);
    }

    while (std::fread(&l, sizeof(libro), 1, f) == 1) {
        bool coincide = (opc == 1)
            ? std::regex_search(toLower(l.getTitulo()), patron)  ///if
            : (l.getIsbn() == criterio); ///else
        if (coincide) {
            matches.emplace_back(l, pos);
        }
        ++pos;
    }
    std::fclose(f);

    if (matches.empty()) {
        std::cout << "No se encontraron libros para \"" << criterio << "\".\n";
        return;
    }

    // Mostrar menú solo con las coincidencias
    std::cout << "Libros encontrados: " << std::endl;
    for (size_t i = 0; i < matches.size(); ++i) {
        libro lb = matches[i].first;
        std::cout << " [" << (i+1) << "] " << lb.getTitulo() << " (Prestados: " << lb.getlibrosPrestados() << " / " << lb.getCantidadEjemplares() << ")\n";
    }
    size_t sel = 0;     // Leer selección válida
    do {
        std::cout << "Seleccione un numero (1-" << matches.size() << "): ";
        std::cin >> sel;
    } while (sel < 1 || sel > matches.size());

    // Datos del socio // esta parte todavía no modifica el archivo de socios ni de prestamos solo pide los datos.
    std::string nombreSocio;
    int idSocio;
    std::cin.ignore();
    std::cout << "Nombre del socio: ";
    std::getline(std::cin, nombreSocio);
    std::cout << "ID del socio: ";
    std::cin >> idSocio;

    // 2ª pasada: reabrir en lectura/escritura y actualizar ese registro
    long index = matches[sel-1].second;
    f = std::fopen(_libroArchivo.c_str(), "rb+");
    if (!f) {
        std::cout << "No se pudo reabrir el archivo.\n";
        return;
    }
    std::fseek(f, index * sizeof(libro), SEEK_SET); // Movernos al registro exacto
    std::fread(&l, sizeof(libro), 1, f); // Leer la última versión

    // Control de stock
    int nuevosPrestados = l.getlibrosPrestados() + 1;
    if (nuevosPrestados > l.getCantidadEjemplares()) {
        std::cout << "No quedan ejemplares disponibles para prestar.\n";
        std::fclose(f);
        return;
    }
    l.setlibrosPrestados(nuevosPrestados);

    // Volver atrás y escribir
    std::fseek(f, -static_cast<long>(sizeof(libro)), SEEK_CUR);
    std::fwrite(&l, sizeof(libro), 1, f);
    std::fflush(f);
    std::fclose(f);

    // Confirmación final
    std::cout << "\nPrestamo registrado con exito:\n"
              << " Titulo: " << l.getTitulo() << "\n"
              << " Total prestados de ese título: " << l.getlibrosPrestados() << "\n"
              << " Socio: " << nombreSocio
              << " (ID " << idSocio << ")\n";
}

/// 4. MODIFICAR LIBRO
void libroArchivo::modificarLibro() {
    autoresManager manager;
    int continuar = 2;

    do {
        std::string criterio;
        std::cout << "¿Qué libro desea modificar? Ingrese el TÍTULO o parte de él: ";
        std::getline(std::cin, criterio);
        std::string criterioLower = toLower(criterio);
        std::regex patron(criterioLower, std::regex_constants::icase);

        FILE* f = fopen(_libroArchivo.c_str(), "rb+");
        if (!f) {
            std::cout << "No se pudo abrir el archivo de libros.\n";
            return;
        }

        std::vector<std::pair<libro, long>> coincidencias;
        libro l;
        long pos = 0;

        while (fread(&l, sizeof(libro), 1, f) == 1) {
            if (std::regex_search(toLower(l.getTitulo()), patron)) {
                coincidencias.emplace_back(l, pos);
            }
            ++pos;
        }

        if (coincidencias.empty()) {
            std::cout << "No se encontraron libros con ese criterio.\n";
            fclose(f);
            continue;
        }

        std::cout << "\n=== COINCIDENCIAS ENCONTRADAS ===\n";
        mostrarEncabezadoTablaLibros();
        for (size_t i = 0; i < coincidencias.size(); ++i) {
            std::cout << "[" << i + 1 << "] ";
            mostrarLibroEnTabla(coincidencias[i].first, manager);
        }

        size_t seleccion;
        do {
            std::cout << "\nSeleccione el número del libro a modificar (1-" << coincidencias.size() << "): ";
            std::cin >> seleccion;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } while (seleccion < 1 || seleccion > coincidencias.size());

        libro& libroSeleccionado = coincidencias[seleccion - 1].first;
        long indice = coincidencias[seleccion - 1].second;

        do {
            int opcion;
            std::cout << "\n¿Qué dato desea modificar?\n";
            std::cout << "1 - ISBN\n";
            std::cout << "2 - Título\n";
            std::cout << "3 - Autor\n";
            std::cout << "4 - Cantidad de ejemplares\n";
            std::cout << "Ingrese opción: ";
            std::cin >> opcion;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (opcion) {
                case 1: {
                    std::string nuevoIsbn;
                    do {
                        std::cout << "Nuevo ISBN: ";
                        std::getline(std::cin, nuevoIsbn);
                        nuevoIsbn = trim(nuevoIsbn);
                    } while (!libroSeleccionado.setIsbn(nuevoIsbn));
                    break;
                }
                case 2: {
                    std::string nuevoTitulo;
                    do {
                        std::cout << "Nuevo TÍTULO: ";
                        std::getline(std::cin, nuevoTitulo);
                        nuevoTitulo = trim(nuevoTitulo);
                    } while (!libroSeleccionado.setTitulo(nuevoTitulo));
                    break;
                }
                case 3: {
                    int nuevoIdAutor = manager.seleccionarOcrearAutorPorNombre();
                    libroSeleccionado.setIdAutor(nuevoIdAutor);
                    break;
                }
                case 4: {
                    int cantidad;
                    do {
                        std::cout << "Nueva cantidad de ejemplares (actual: " << libroSeleccionado.getCantidadEjemplares() << "): ";
                        if (!(std::cin >> cantidad)) {
                            std::cin.clear();
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cout << "Debe ingresar un número válido.\n";
                            continue;
                        }
                        if (cantidad >= libroSeleccionado.getlibrosPrestados()) {
                            libroSeleccionado.setCantidadEjemplares(cantidad);
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            break;
                        } else {
                            std::cout << "No puede ser menor a la cantidad de libros prestados (" << libroSeleccionado.getlibrosPrestados() << ").\n";
                        }
                    } while (true);
                    break;
                }
                default:
                    std::cout << "Opción inválida.\n";
                    break;
            }

            // Volver a escribir el libro en la posición original
            fseek(f, indice * sizeof(libro), SEEK_SET);
            fwrite(&libroSeleccionado, sizeof(libro), 1, f);
            fflush(f);

            continuar = leerOpcionRango(0, 2,
                "\n¿Desea seguir modificando este libro?\n"
                " 0 = Finalizar y salir\n"
                " 1 = Seguir modificando este libro\n"
                " 2 = Modificar otro libro\n"
                "Ingrese opción: ");

        } while (continuar == 1);

        fclose(f);
    } while (continuar == 2);
}


/// 5. DEVOLVER LIBRO: esto debe contemplar primero al socio, qué libros tiene en su haber y seleccionar el que quiere devolver.
void libroArchivo::devolverLibro() {
    int opc = 0;
    std::string criterio;
    if (!elegirCriterioBusqueda(opc, criterio)) {
        return;
    }

    FILE* f = std::fopen(_libroArchivo.c_str(), "rb");
    if (!f) {
        std::cerr << "No se pudo abrir el archivo de libros.\n";
        return;
    }

    std::vector<std::pair<libro, long>> matches;
    libro l;
    long pos = 0;
    std::regex patron;
    std::string criterioLow = toLower(criterio);
    if (opc == 1 || opc == 3) {
        patron = std::regex(criterioLow, std::regex_constants::icase);
    }

    while (std::fread(&l, sizeof(libro), 1, f) == 1) {
        bool coincide = false;
        if (opc == 1)
            coincide = std::regex_search(toLower(l.getTitulo()), patron);
        else if (opc == 2)
            coincide = l.getIsbn() == criterio;
        else if (opc == 3) {
            autoresManager manager;
            std::string nombreAutor = manager.buscarNombrePorId(l.getIdAutor());
            coincide = std::regex_search(toLower(nombreAutor), patron);
        }

        if (coincide) {
            matches.emplace_back(l, pos);
        }
        ++pos;
    }
    std::fclose(f);

    if (matches.empty()) {
        std::cout << "No se encontraron libros para \"" << criterio << "\".\n";
        return;
    }

    // Mostrar coincidencias
    std::cout << "Libros encontrados:\n";
    for (size_t i = 0; i < matches.size(); ++i) {
        libro lb = matches[i].first;
        std::cout << " [" << (i + 1) << "] " << lb.getTitulo()
                  << " (Prestados: " << lb.getlibrosPrestados()
                  << " / " << lb.getCantidadEjemplares() << ")\n";
    }

    size_t sel = 0;
    do {
        std::cout << "Seleccione un número (1-" << matches.size() << "): ";
        std::cin >> sel;
    } while (sel < 1 || sel > matches.size());

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Reabrir el archivo en modo lectura/escritura
    long index = matches[sel - 1].second;
    f = std::fopen(_libroArchivo.c_str(), "rb+");
    if (!f) {
        std::cout << "No se pudo reabrir el archivo.\n";
        return;
    }

    std::fseek(f, index * sizeof(libro), SEEK_SET);
    std::fread(&l, sizeof(libro), 1, f);

    if (l.getlibrosPrestados() == 0) {
        std::cout << "Este libro no tiene ejemplares prestados actualmente.\n";
        std::fclose(f);
        return;
    }

    l.setlibrosPrestados(l.getlibrosPrestados() - 1);

    std::fseek(f, -static_cast<long>(sizeof(libro)), SEEK_CUR);
    std::fwrite(&l, sizeof(libro), 1, f);
    std::fflush(f);
    std::fclose(f);

    std::cout << "\nDevolución registrada con éxito:\n"
              << " Título: " << l.getTitulo() << "\n"
              << " Prestados restantes: " << l.getlibrosPrestados() << "\n";
}

///6. STOCK DE LIBROS
void libroArchivo::listarLibros() {
    int stockActual = 0;
    int totalRegistrosLibro = getCantidadRegistroLibro();
    if (totalRegistrosLibro == 0) {
        cout << "No hay libros para mostrar." << endl;
        return;
    }

    autoresManager manager;
    mostrarEncabezadoTablaLibros(); /// función reutilizable para mostrar encabezados

    for (int i = 0; i < totalRegistrosLibro; i++) {
        libro l = LeerLibro(i);
        stockActual = l.getCantidadEjemplares() - l.getlibrosPrestados();

        if (stockActual > 0) {
            mostrarLibroEnTabla(l, manager); /// función reutilizable para mostrar resultados
        }
    }
}

///########### AUXILIARES #########////
///Esta función se podría hacer genérica para todas las clases.
bool libroArchivo::guardarLibro(const libro& l) {
    FILE* punteroArchivoLibro = fopen(_libroArchivo.c_str(), "ab");

    if (punteroArchivoLibro == nullptr) {
        std::cout << " ===== NO SE PUDO ABRIR EL ARCHIVO DE LIBROS ==== " << std::endl;
        return false;
    }

    bool exito = fwrite(&l, sizeof(libro), 1, punteroArchivoLibro);
    fclose(punteroArchivoLibro);

    return exito;
}

///Esta función se podría hacer genérica para todas las clases.
int libroArchivo::getCantidadRegistroLibro() {
    return contarRegistros(_libroArchivo, sizeof(libro));
}

bool libroArchivo::elegirCriterioBusqueda(int& opc, std::string& criterio) {
    do {
        std::cout << "1) Buscar por TITULO" << std::endl;
        std::cout << "2) Buscar por ISBN" << std::endl;
        std::cout << "3) Buscar por AUTOR" << std::endl;
        std::cout << "4) Volver al menu anterior" << std::endl;
        std::cout << std::endl;
        std::cout << "Elija opcion: ";

        if (!(std::cin >> opc)) {
            std::cout << std::endl;
            std::cout << "Por favor ingrese una opcion valida." << std::endl;
            std::cout << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (opc < 1 || opc > 4) {
            std::cout << "Opcion invalida. Debe ser 1, 2, 3 o 4." << std::endl;
            continue;
        }

        switch (opc) {
            case 1:
                std::cout << "Ingrese el TITULO o parte de el: ";
                std::getline(std::cin, criterio);
                return true;
            case 2:
                std::cout << "Ingrese el ISBN completo: ";
                std::getline(std::cin, criterio);
                return true;
            case 3:
                std::cout << "Ingrese el nombre (o parte) del AUTOR: ";
                std::getline(std::cin, criterio);
                return true;
            case 4:
                return false;
            default:
                std::cout << "Opcion invalida. Intente de nuevo.";
                break;
        }
    } while (true);
}

// Lee un libro de la posición indicada
libro libroArchivo::LeerLibro(int pos) {
    libro l;
    if (!leerRegistroBinario(&l, sizeof(libro), pos, _libroArchivo)) {
        std::cout << "Error al leer libro en posición " << pos << std::endl;
    }
    return l;
}

void libroArchivo::mostrarEncabezadoTablaLibros() {
    system("cls");
    std::cout << left
         << std::setw(15) << "ISBN"
         << std::setw(50) << "Titulo"
         << std::setw(30) << "Autor"
         << std::setw(18) << "F. Publicacion"
         << std::setw(15) << "Stock actual"
         << setw(15) << "Prestados"
         << setw(15) << "Stock total"
         << std::endl;
    std::cout << setfill('-') << std::setw(143) << "-" << setfill(' ') << std::endl;
}

void libroArchivo::mostrarLibroEnTabla(libro& l, autoresManager& manager) {
    Fecha f = l.getFechaPublicacion();
    std::string fechaStr = to_string(f.getDia()) + "/" + to_string(f.getMes()) + "/" + to_string(f.getAnio());
    std::cout << left
         << std::setw(15) << l.getIsbn()
         << std::setw(50) << l.getTitulo().substr(0, 50)
         << std::setw(30) << manager.buscarNombrePorId(l.getIdAutor())
         << std::setw(22) << fechaStr
         << std::setw(15) << (l.getCantidadEjemplares() - l.getlibrosPrestados())
         << setw(15) << l.getlibrosPrestados()
         << std::setw(15) << l.getCantidadEjemplares()
         << std::endl;
}

bool libroArchivo::existeIsbn(const std::string& isbnBuscado, libro& libroEncontrado) {
    FILE* f = fopen(_libroArchivo.c_str(), "rb");
    if (!f) return false;

    libro l;
    while (fread(&l, sizeof(libro), 1, f) == 1) {
        if (l.getIsbn() == isbnBuscado) {
            libroEncontrado = l;
            fclose(f);
            return true;
        }
    }
    fclose(f);
    return false;
}


