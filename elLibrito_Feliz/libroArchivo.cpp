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

/// 1. GUARDAR UN NUEVO LIBRO
void libroArchivo::NuevoLibro() {
    libro l;
    autoresManager managerAutores;

    string isbn, titulo;
    int cantidad;

    libro libroExistente;
    do {
        cout << "== ISBN ==: ";
        getline(cin, isbn);
        isbn = trim(isbn);

        if (isbn.empty()) {
            cout << "El ISBN no puede estar vacío." << endl;
            continue;
        }

        if (existeIsbn(isbn, libroExistente)) {
            cout << "YA EXISTE UN LIBRO CON ESE ISBN." << endl;
            cout << "Título: " << libroExistente.getTitulo() << endl;
            return;
        }

        if (l.setIsbn(isbn)) break;

        cout << "ISBN inválido. Intente nuevamente." << endl;
    } while (true);

    do {
        cout << "== TITULO (max 50 caracteres) ==: ";
        getline(cin, titulo);
        titulo = trim(titulo);

        if (titulo.empty()) {
            cout << "El título no puede estar vacío." << endl;
            continue;
        }

        if (l.setTitulo(titulo)) break;

        cout << "Título inválido o demasiado largo." << endl;
    } while (true);

    // === Autor ===
    int idAutor = managerAutores.seleccionarOcrearAutorPorNombre();
    if (idAutor == 0) {
        cout << "Error al seleccionar o crear el autor. Cancelando." << endl;
        return;
    }
    l.setIdAutor(idAutor);

    do {
        cout << "== CANTIDAD DE EJEMPLARES ==: ";
        if (!(cin >> cantidad)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Debe ingresar un número." << endl;
            continue;
        }
        if (cantidad > 0) {
            l.setCantidadEjemplares(cantidad);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
        cout << "La cantidad debe ser mayor a cero." << endl;
    } while (true);

    cout << "== FECHA DE PUBLICACION ==" << endl;
    Fecha fecha = leerFechaValida();
    l.setFechaPublicacion(fecha);

    cout << "===============================" << endl;

    guardarRegistro(_libroArchivo, &l, sizeof(libro));
}
/// 2.  ESTA FUNCION SIRVE PARA MOSTRAR EL LIBRO EN LA POSICIÓN SELECCIONADA, A FUTURO DEBERÍA CAMBIARSE PARA QUE EN VEZ DE TOMAR LA POSICIÓN TOME EL TÍTULO, EL ISBN O EL AUTOR.
void libroArchivo::buscarLibro() {
    int opc;
    string criterio;

    if (!elegirCriterioBusqueda(opc, criterio)) {
        return;
    }

    FILE* f = abrirArchivo(_libroArchivo, "rb");
    if (f == nullptr) {
        cout << "No se pudo abrir el archivo de libros." << endl;
        return;
    }

    std::regex patron;
    string criterioLow = toLower(criterio);
    if (opc == 1 || opc == 3) {
        patron = std::regex(criterioLow, std::regex_constants::icase);
    }


    mostrarEncabezadoTablaLibros();


    libro l;
    autoresManager manager;
    bool encontrado = false;

    while (fread(&l, sizeof(libro), 1, f) == 1) {
        bool coincidencia = false;

        if (opc == 1) {
            coincidencia = std::regex_search(toLower(l.getTitulo()), patron);
        } else if (opc == 2) {
            coincidencia = (l.getIsbn() == criterio);
        } else if (opc == 3) {
            string nombreAutor = manager.buscarNombrePorId(l.getIdAutor());
            coincidencia = std::regex_search(toLower(nombreAutor), patron);
        }

        if (coincidencia) {
            mostrarLibroEnTabla(l, manager);
            encontrado = true;
        }
    }

    fclose(f);

    if (!encontrado) {
        cout << "No se encontraron libros para esos criterios." << endl;
    }
    system("pause");
}

/// 3. MODIFICAR LIBRO
void libroArchivo::modificarLibro() {
    autoresManager manager;
    int continuar = 2;

    do {
        string criterio;
        cout << "¿Qué libro desea modificar? Ingrese el TITULO o parte de él: ";
        getline(cin, criterio);

        FILE* f = abrirArchivo(_libroArchivo, "rb+");
        if (f == nullptr) {
            cout << "No se pudo abrir el archivo." << endl;
            return;
        }

        fseek(f, 0, SEEK_END);
        long totalRegistros = ftell(f) / sizeof(libro);
        rewind(f);

        libro* coincidencias = new libro[totalRegistros];
        long* posiciones = new long[totalRegistros];
        int encontrados = 0;
        long pos = 0;
        libro l;

        std::regex patron(criterio, std::regex_constants::icase);

        while (fread(&l, sizeof(libro), 1, f) == 1) {
            if (std::regex_search(l.getTitulo(), patron)) {
                coincidencias[encontrados] = l;
                posiciones[encontrados] = pos;
                encontrados++;
            }
            pos++;
        }

        if (encontrados == 0) {
            cout << "No se encontraron libros con ese criterio." << endl;
            fclose(f);
            delete[] coincidencias;
            delete[] posiciones;
            continue;
        }

        cout << endl << "=== COINCIDENCIAS ENCONTRADAS ===" << endl;
        mostrarEncabezadoTablaLibros();
        for (int i = 0; i < encontrados; i++) {
            cout << "[" << i + 1 << "] ";
            mostrarLibroEnTabla(coincidencias[i], manager);
        }

        int seleccion;
        do {
            cout << endl << "Seleccione el número del libro a modificar (1-" << encontrados << "): ";
            cin >> seleccion;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } while (seleccion < 1 || seleccion > encontrados);

        libro& libroSeleccionado = coincidencias[seleccion - 1];
        long indice = posiciones[seleccion - 1];

        do {
            int opcion;
            cout << endl << "¿Qué dato desea modificar?" << endl;
            cout << "1 - ISBN" << endl;
            cout << "2 - Titulo" << endl;
            cout << "3 - Autor" << endl;
            cout << "4 - Cantidad de ejemplares" << endl;
            cout << "Ingrese opción: ";
            cin >> opcion;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (opcion) {
                case 1: {
                    string nuevoIsbn;
                    do {
                        cout << "Nuevo ISBN: ";
                        getline(cin, nuevoIsbn);
                        nuevoIsbn = trim(nuevoIsbn);
                    } while (!libroSeleccionado.setIsbn(nuevoIsbn));
                    break;
                }
                case 2: {
                    string nuevoTitulo;
                    do {
                        cout << "Nuevo TITULO: ";
                        getline(cin, nuevoTitulo);
                        nuevoTitulo = trim(nuevoTitulo);
                    } while (!libroSeleccionado.setTitulo(nuevoTitulo));
                    break;
                }
                case 3: {
                    int nuevoIdAutor = manager.seleccionarOcrearAutorPorNombre();
                    if (nuevoIdAutor > 0) {
                        libroSeleccionado.setIdAutor(nuevoIdAutor);
                    }
                    break;
                }
                case 4: {
                    int cantidad;
                    do {
                        cout << "Nueva cantidad de ejemplares (actual: "
                             << libroSeleccionado.getCantidadEjemplares() << "): ";
                        if (!(cin >> cantidad)) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "Debe ingresar un número válido." << endl;
                            continue;
                        }
                        if (cantidad >= libroSeleccionado.getlibrosPrestados()) {
                            libroSeleccionado.setCantidadEjemplares(cantidad);
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            break;
                        } else {
                            cout << "No puede ser menor a la cantidad de libros prestados ("
                                 << libroSeleccionado.getlibrosPrestados() << ")." << endl;
                        }
                    } while (true);
                    break;
                }
                default:
                    cout << "Opción inválida." << endl;
                    break;
            }

            fseek(f, indice * sizeof(libro), SEEK_SET);
            fwrite(&libroSeleccionado, sizeof(libro), 1, f);
            fflush(f);

            continuar = leerOpcionRango(0, 2,
                "\n¿Desea seguir modificando este libro?\n"
                " 0 = Finalizar y volver al menú\n"
                " 1 = Seguir modificando este libro\n"
                " 2 = Modificar otro libro\n"
                "Ingrese opción: ");
        } while (continuar == 1);

        fclose(f);
        delete[] coincidencias;
        delete[] posiciones;

    } while (continuar == 2);
}

/// Este metodo se comunica con Prestamos Manager para registrar los libros prestados en el archivo libros.dat
bool libroArchivo::registrarPrestamoLibro(int posRegistro) {
    FILE* f = abrirArchivo(_libroArchivo, "rb+");
    if (!f) return false;

    libro l;
    std::fseek(f, posRegistro * sizeof(libro), SEEK_SET);
    std::fread(&l, sizeof(libro), 1, f);

    int nuevosPrestados = l.getlibrosPrestados() + 1;
    if (nuevosPrestados > l.getCantidadEjemplares()) {
        fclose(f);
        return false;
    }

    l.setlibrosPrestados(nuevosPrestados);
    std::fseek(f, -static_cast<long>(sizeof(libro)), SEEK_CUR);
    std::fwrite(&l, sizeof(libro), 1, f);
    fclose(f);
    return true;
}

///6. STOCK DE LIBROS
void libroArchivo::listarLibros() {
    int stockActual = 0;
    int totalRegistrosLibro = contarRegistros(_libroArchivo, sizeof(libro));
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
bool libroArchivo::elegirCriterioBusqueda(int& opc, string& criterio) {
    do {
        cout << "1) Buscar por TITULO" << endl;
        cout << "2) Buscar por ISBN" << endl;
        cout << "3) Buscar por AUTOR" << endl;
        cout << "4) Volver al menu anterior" << endl;
        cout << endl;
        cout << "Elija opcion: ";

        if (!(cin >> opc)) {
            cout << endl << "Por favor ingrese una opcion valida." << endl << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (opc < 1 || opc > 4) {
            cout << "Opcion invalida. Debe ser 1, 2, 3 o 4." << endl;
            continue;
        }

        switch (opc) {
            case 1:
                cout << "Ingrese el TITULO o parte de el: ";
                getline(cin, criterio);
                return true;
            case 2:
                cout << "Ingrese el ISBN completo: ";
                getline(cin, criterio);
                return true;
            case 3:
                cout << "Ingrese el nombre (o parte) del AUTOR: ";
                getline(cin, criterio);
                return true;
            case 4:
                return false;
        }
    } while (true);
}

/// Lee un libro de la posición indicada
libro libroArchivo::LeerLibro(int pos) {
    libro l;

    if (!leerRegistroBinario(&l, sizeof(libro), pos, _libroArchivo)) {
        cout << "Error al leer libro en posicion " << pos << endl;
    }
    return l;
}

void libroArchivo::mostrarEncabezadoTablaLibros() {
    system("cls");
    cout << left
         << setw(15) << "ISBN"
         << setw(35) << "TITULO"
         << setw(25) << "AUTOR"
         << setw(18) << "F. PUBLICACION"
         << setw(15) << "STOCK ACTUAL"
         << setw(12) << "PRESTADOS"
         << endl;
    cout << setfill('-') << setw(110) << "-" << setfill(' ') << endl;
}

void libroArchivo::mostrarLibroEnTabla(libro& l, autoresManager& manager) {
    Fecha f = l.getFechaPublicacion();
    string fechaStr = to_string(f.getDia()) + "/" + to_string(f.getMes()) + "/" + to_string(f.getAnio());
    cout << left
         << setw(15) << l.getIsbn()
         << setw(38) << l.getTitulo().substr(0, 35)
         << setw(25) << manager.buscarNombrePorId(l.getIdAutor()).substr(0, 20)
         << setw(20) << fechaStr
         << setw(12) << (l.getCantidadEjemplares() - l.getlibrosPrestados())
         << setw(12) << l.getlibrosPrestados()
         << endl;

}

///Estoy casi segura que esta función se debería hacer reutilizable .. porque se podría buscar ID de Socio o de prestamo..
bool libroArchivo::existeIsbn(const std::string& isbnBuscado, libro& libroEncontrado) {
    FILE* f = abrirArchivo(_libroArchivo, "rb");

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


