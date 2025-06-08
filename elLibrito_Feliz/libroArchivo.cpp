#include <limits>
#include <iostream>
#include <cstdio>
#include <iomanip>
#include "libroArchivo.h"
#include "libro.h"
#include "funcionesAuxiliares.h"
#include <regex>
#include <vector>
#include <algorithm>

using namespace std;

libroArchivo::libroArchivo() {
    _libroArchivo = "archivos/libros.dat";
}

libroArchivo::libroArchivo(std::string libroArchivo){
       this -> _libroArchivo = libroArchivo;
}


int libroArchivo::getCantidadRegistroLibro() {
    int tamanioRegistroLibro = sizeof(libro);
    FILE* punteroLibroArchivo = fopen(_libroArchivo.c_str(), "rb");

    if (punteroLibroArchivo == nullptr) {
        return 0;
    }
    fseek(punteroLibroArchivo, 0, SEEK_END);

    int totalDeRegistros = ftell(punteroLibroArchivo);
    int cantidadDeRegistros = totalDeRegistros / tamanioRegistroLibro;
    fclose(punteroLibroArchivo);

    return cantidadDeRegistros;
}

///GUARDAR UN NUEVO LIBRO
bool libroArchivo::guardarLibro(const libro& libro) {
    FILE* punteroArchivoLibro = fopen(_libroArchivo.c_str(), "ab");  // append binario

    if (punteroArchivoLibro == nullptr) {
        std::cout << " ===== NO SE PUDO ABRIR EL ARCHIVO DE LIBROS ==== " << std::endl;
        return false;
    }

    size_t escritos = fwrite(&libro, sizeof(libro), 1, punteroArchivoLibro);
    fclose(punteroArchivoLibro);

    return escritos == 1;
}

void libroArchivo::cargarLibro() {
    libroArchivo archivo;
    libro l;
    int id_Autor = 0;

    std::string isbn, titulo;
    int idAutor, cantidad;
    std::cout << "== ISBN ==: ";
    std::getline(std::cin, isbn);
    while (l.setIsbn(isbn)!= true){
        std::cout << "== INGRESE UN ISBN ==: ";
        std::getline(std::cin, isbn);
        std::cout << std::endl;
    };

    std::cout << "== TITULO (max 50 caracteres) ==: ";
    std::getline(std::cin, titulo);
    while( !l.setTitulo(titulo)){
        std::cout << "== INGRESE EL TITULO (max 50 caracteres) ==: ";
        std::getline(std::cin, titulo);
        std::cout << std::endl;
    }

    std::cout << "== ID AUTOR ==: ";
    id_Autor = obtenerSiguienteIdAutor();
    l.setIdAutor(id_Autor);
    std::cout << "ID de autor asignado automaticamente: " << id_Autor << std:: endl;

    std::cout << "== CANTIDAD DE EJEMPLARES ==: ";
    std::cin >> cantidad;
    l.setCantidadEjemplares(cantidad);

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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

///STOCK DE LIBROS
void libroArchivo::listarLibros() {
    int stockActual = 0;
    int totalRegistrosLibro = getCantidadRegistroLibro();
    if (totalRegistrosLibro == 0) {
        cout << "No hay libros para mostrar." << endl;
        return;
    }
    cout << left
         << setw(15) << "ISBN"
         << setw(50) << "Titulo"
         << setw(10) << "IdAutor"
         << setw(15) << "F. Publicacion"
         << setw(10) << "Stock actual"
         << setw(10) << "Prestados"
         << setw(13) << "Stock total"
         << endl;
    cout << setfill('-') << setw(110) << "-" << setfill(' ') << endl;
    for (int i = 0; i < totalRegistrosLibro; i++) {
        libro l = LeerLibro(i);
        Fecha f = l.getFechaPublicacion();
        string fechaStr = to_string(f.getDia()) + "/" + to_string(f.getMes()) + "/" + to_string(f.getAnio());
        stockActual = (l.getCantidadEjemplares() - l.getlibrosPrestados());
        if(stockActual> 0){  /// Esto debe cambiarse por el stock actual cuando se tenga
                cout << left
                 << setw(15) << l.getIsbn()
                 << setw(50) << l.getTitulo()
                 << setw(10) << l.getIdAutor()
                 << setw(15) << fechaStr
                 << setw(10) << stockActual
                 << setw(10) << l.getlibrosPrestados()
                 << setw(13) << l.getCantidadEjemplares()
                 << endl;
        }
    }

}

///ESTA FUNCION SIRVE PARA MOSTRAR EL LIBRO EN LA POSICIÓN SELECCIONADA, A FUTURO DEBERÍA CAMBIARSE PARA QUE EN VEZ DE TOMAR LA POSICIÓN TOME EL TÍTULO, EL ISBN O EL AUTOR.
void libroArchivo::buscarLibro() {
    int opc;
    std::string criterio;

    if(!elegirCriterioBusqueda(opc, criterio)){
        return;
    }
    FILE* f = std::fopen(_libroArchivo.c_str(), "rb");
    if(!f){
        std::cout << "No se pudo abrir el archivo de libros. " << std:: endl;
        return;
    }

    std::regex patron;
    std:: string criterioLow = toLower(criterio);
    if(opc == 1){
        patron = std::regex(criterioLow, std::regex_constants::icase);
    }

    ///Construimos las columnas de la tabla:
    system("cls");
    std::cout << left
         << std::setw(15) << "ISBN"
         << std::setw(50) << "Titulo"
         << std::setw(15) << "IdAutor"
         << std::setw(20) << "F de Publicacion"
         << std::setw(10) << "Stock actual"

         << std::endl;
    std::cout << setfill('-') << std::setw(110) << "-" << setfill(' ') << std::endl;

    libro l;
    bool noEncontrado = false;
    while(std::fread(&l, sizeof(libro), 1, f) == 1){
        bool coincidencia = (opc == 1)
        ? std::regex_search(toLower(l.getTitulo()), patron)
        :(l.getIsbn()== criterio);
        if (coincidencia){
            Fecha f = l.getFechaPublicacion();
            string fechaStr = to_string(f.getDia()) + "/" + to_string(f.getMes()) + "/" + to_string(f.getAnio());
            std::cout << left
                 << std::setw(15) << l.getIsbn()
                 << std::setw(50) << l.getTitulo().substr(0, 50)
                 << std::setw(15) << l.getIdAutor()
                 << std::setw(20) << fechaStr
                 << std::setw(10) << (l.getCantidadEjemplares() - l.getlibrosPrestados())
                 << std::endl;
            noEncontrado = true;

        }
    }
    std::fclose(f);
    if(!noEncontrado){
        std::cout << "No se encontraron libros para esos criterios" << std:: endl;
    }
}

bool libroArchivo::elegirCriterioBusqueda(int& opc, std::string& criterio) {
    do {
        std::cout << "1) Buscar por TITULO" << std::endl;
        std::cout << "2) Buscar por ISBN"<< std::endl;
        std::cout << "3) Volver al menu anterior"<< std::endl;
        std::cout << std::endl;
        std::cout << "Elija opcion: ";

        // VALIDAMOS QUE LO QUE INGRESA EL USUARIO SEA CORRECTO PARA QUE EL CODIGO NO CAIGA EN UN BUCLE.
        if (!(std::cin >> opc)) {
            std::cout << std::endl;
            std::cout << "Por favor ingrese una opcion valida." << std::endl;
            std::cout << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // descartamos el resto de la línea (por si meten espacios, etc.)

        // 2) Validamos el rango 1–3
        if (opc < 1 || opc > 3) {
            std::cout << "Opcion invalida. Debe ser 1, 2 o 3."<< std::endl;
            continue;  // repregunta
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
                return false;
            default:
                std::cout << "Opcion invalida. Intente de nuevo.";
                break;
        }
    } while (true);
}


void libroArchivo::prestarLibro(){
    int opc = 0;
    std::string criterio;
    if (!elegirCriterioBusqueda(opc, criterio)) {
        return;
    }


    // --- aquí continua el resto de tu lógica de búsqueda y préstamo ---
    // 1ª pasada: abrir en modo lectura y recopilar coincidencias...
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

// Lee un libro de la posición indicada
libro libroArchivo::LeerLibro(int pos) {
    FILE* punteroArchivoLibro;
    libro registroLibro;

    punteroArchivoLibro = fopen(_libroArchivo.c_str(), "rb");
    if (punteroArchivoLibro == nullptr) {
        cout << "Error: No se pudo abrir el archivo de libros." << endl;
        return registroLibro;  // Devuelve un objeto vacío
    }

    fseek(punteroArchivoLibro, sizeof(libro) * pos, SEEK_SET);
    fread(&registroLibro, sizeof(libro), 1, punteroArchivoLibro);

    fclose(punteroArchivoLibro);
    return registroLibro;
}


///AUTORES////

int libroArchivo::obtenerSiguienteIdAutor() {
    FILE* f = std::fopen(_libroArchivo.c_str(), "rb");
    if (!f) {
        // Si no existe el archivo o no se puede abrir, empezamos en 1
        return 1;
    }

    libro l;
    int maxId = 0;
    // Recorremos todos los libros y guardamos el mayor Id_autor que encontremos
    while (std::fread(&l, sizeof(libro), 1, f) == 1) {
        maxId = std::max(maxId, l.getIdAutor());
    }
    std::fclose(f);

    // El siguiente ID será el mayor + 1
    return maxId + 1;
}

///cosas que pueden servir
/*libro libroArchivo::LeerLibro(int pos) {
    libro registroLibro{};  // Inicializa todo a cero/"" por defecto

    int total = getCantidadRegistroLibro();
    if (pos < 0 || pos >= total) {
        std::cerr << "Error: posición fuera de rango (" << pos << " / " << total << ")" << std::endl;
        return registroLibro;
    }

    FILE* f = fopen(_libroArchivo.c_str(), "rb");
    if (!f) {
        std::cerr << "Error: no se pudo abrir " << _libroArchivo << std::endl;
        return registroLibro;
    }

    // Posiciona
    if (fseek(f, pos * sizeof(libro), SEEK_SET) != 0) {
        std::cerr << "Error: fseek falló al mover al registro " << pos << std::endl;
        fclose(f);
        return registroLibro;
    }

    // Lee todo el struct de una vez
    size_t leidos = fread(&registroLibro, sizeof(libro), 1, f);
    if (leidos != 1) {
        std::cerr << "Error: fread leyó " << leidos << " registros en vez de 1" << std::endl;
        // registroLibro seguirá en su estado por defecto
    }

    fclose(f);
    return registroLibro;
}*/
