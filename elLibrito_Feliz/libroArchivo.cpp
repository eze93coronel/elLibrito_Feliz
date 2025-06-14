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
    Autores nuevoAutor;

    std::string isbn, titulo, nombreAutorInput;
    int cantidad;

    std::cout << "== ISBN ==: ";
    std::getline(std::cin, isbn);
    while (!l.setIsbn(isbn)) {
        std::cout << "== INGRESE UN ISBN ==: ";
        std::getline(std::cin, isbn);
    }

    std::cout << "== TITULO (max 50 caracteres) ==: ";
    std::getline(std::cin, titulo);
    while (!l.setTitulo(titulo)) {
        std::cout << "== INGRESE EL TITULO (max 50 caracteres) ==: ";
        std::getline(std::cin, titulo);
    }

    std::cout << "== INGRESE NOMBRE DEL AUTOR (o parte del nombre) ==: ";
    std::getline(std::cin, nombreAutorInput);

    std::vector<Autores> coincidencias;
    FILE* archivoAutores = fopen("archivos/autores.dat", "rb");
    Autores a;

    if (archivoAutores != nullptr) {
        while (fread(&a, sizeof(Autores), 1, archivoAutores) == 1) {
            std::string autorNombre = a.getNombreAutor();
            if (autorNombre.find(nombreAutorInput) != std::string::npos) {
                coincidencias.push_back(a);
            }
        }
        fclose(archivoAutores);
    }

    int id_Autor = 0;
    if (!coincidencias.empty()) {
        std::cout << "=== COINCIDENCIAS ENCONTRADAS ===" << std::endl;
        for (size_t i = 0; i < coincidencias.size(); ++i) {
            std::cout << "[" << i + 1 << "] " << coincidencias[i].getNombreAutor()
                      << " (ID: " << coincidencias[i].getIdAutor() << ")" << std::endl;
        }

        int seleccion;
        do {
            std::cout << "Seleccione una opción (1-" << coincidencias.size() << ") o 0 para crear nuevo autor: ";
            std::cin >> seleccion;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } while (seleccion < 0 || seleccion > static_cast<int>(coincidencias.size()));

        if (seleccion != 0) {
            id_Autor = coincidencias[seleccion - 1].getIdAutor();
        }
    }

    if (id_Autor == 0) {
        std::string nombreCompleto;
        std::cout << "No se encontraron coincidencias. Ingrese el nombre completo del nuevo autor: ";
        std::getline(std::cin, nombreCompleto);

        autoresManager managerAutores;
        int nuevoId = managerAutores.obtenerSiguienteIdAutor();
        nuevoAutor.setIdAutor(nuevoId);
        nuevoAutor.setNombreAutor(nombreCompleto);

        FILE* fa = fopen("archivos/autores.dat", "ab");
        if (fa != nullptr) {
            fwrite(&nuevoAutor, sizeof(Autores), 1, fa);
            fclose(fa);
            std::cout << "Nuevo autor guardado con ID: " << nuevoId << std::endl;
        } else {
            std::cout << "Error al guardar nuevo autor." << std::endl;
        }

        id_Autor = nuevoId;
    }

    l.setIdAutor(id_Autor);

    // === Cantidad de ejemplares ===
    std::cout << "== CANTIDAD DE EJEMPLARES ==: ";
    std::cin >> cantidad;
    l.setCantidadEjemplares(cantidad);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // === Fecha ===
    std::cout << "== FECHA DE PUBLICACION ==" << std::endl;
    Fecha fecha;
    fecha.cargarFecha();
    l.setFechaPublicacion(fecha);

    std::cout << "===============================" << std::endl;

    if (archivo.guardarLibro(l)) {
        std::cout << "=== EL LIBRO FUE GUARDADO CORRECTAMENTE ===" << std::endl;
    } else {
        std::cout << "=== ERROR, NO SE PUDO GUARDAR EL LIBRO ===" << std::endl;
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

    // Mostrar menú solo con los matches
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
         << std::setw(40) << "Titulo"
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
         << std::setw(40) << l.getTitulo().substr(0, 50)
         << std::setw(30) << manager.buscarNombrePorId(l.getIdAutor())
         << std::setw(22) << fechaStr
         << std::setw(15) << (l.getCantidadEjemplares() - l.getlibrosPrestados())
         << setw(15) << l.getlibrosPrestados()
         << std::setw(15) << l.getCantidadEjemplares()
         << std::endl;
}
