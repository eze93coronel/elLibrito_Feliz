#include <iostream>
#include "socioManager.h"
#include "Socio.h"
#include "sociosArchivos.h"
#include "Fecha.h"
using namespace std ;

void socioManager::cargarSocio()
{
    Fecha fecha;
    Socio socio;
    sociosArchivos socioArchivo;
    int numeroSocio;
    string nombre,apellido,dni,telefono,direccion,email;
    //   Fecha fecha;
    cout <<"===============================" << endl;
    cout <<"INGRESE DATOS DEL SOCIO : " << endl;
    cout << "== NUMERO DEL SOCIO  ==" << endl;
    cin >> numeroSocio;
    cin.ignore();
    cout << "== NOMBRE ==" << endl;
    getline(cin,nombre);
    cout << "== APELLIDO ==" << endl;

    getline(cin,apellido);
    cout << "== DNI ==" << endl;
    getline(cin,dni);
    cout << "== TELEFONO ==" << endl;

    getline(cin,telefono);
    cout << "== DIRECCION ==" << endl;
    getline(cin,direccion);
    cout << "== EMAIL ==" << endl;

    getline(cin,email);

    fecha.cargarFecha();
    fecha.mostrarFecha();
    cout <<"===============================" << endl;

    socio = Socio(numeroSocio,nombre,apellido,dni,telefono,direccion,email,fecha);
    cout << socio.mostrarSocioPantalla() << endl;

    if(socioArchivo.guardarArchivoSocio(socio))
    {

        cout << " === EL ARCHIVO DEL SOCIO FUE GUARDADO CORRECTAMENTE === " << endl;
    }
    else
    {
        cout << " ===  ERROR, NO SE PUDO GUARDAR  EL ARCHIVO DEL SOCIO  === " << endl;

    }
}
void socioManager::cargarCantidadRegistroSocio()
{
    sociosArchivos archivoSocio;

    int cantidadDeRegistros = archivoSocio.getCantidadRegistroSocio();

    cout << "la cantidad de registros que tiene el archivo son : " << cantidadDeRegistros << endl;
}
void socioManager::listarSocios()
{
    sociosArchivos archivoSocio;
    Socio socio;

    int totalRegistrosSocio = archivoSocio.getCantidadRegistroSocio();

    for (int i = 0; i<totalRegistrosSocio; i++)
    {
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
void socioManager::buscarSocio()
{
    sociosArchivos archivoSocio;
    Socio socio;
    int numeroSocio;

    cout << "Ingrese un número de socio: ";
    cin >> numeroSocio;
    cout << endl;
    int posicionSocioArchivo = archivoSocio.buscarArchivoSocio(numeroSocio);

    if (posicionSocioArchivo >= 0)
    {

        socio = archivoSocio.LeerSocio(posicionSocioArchivo);

        cout << " == LOS DATOS DEL SOCIO SON  == " << endl;
        cout << "============================================"  << endl;
        cout << "Numero de Socio : " << socio.getNumeroSocio() << endl;
        cout<< " Nombre del socio : " <<  socio.getNombre() << endl;
        cout << "Apellido del socio : " <<  socio.getApellido() << endl;
        cout << "Email del socio : " << socio.getEmail() << endl;
        cout << "============================================"  << endl;
    }
    else
    {
        cout << "No existe un asociado con ese numero de socio." << endl;
    }
}
void socioManager::modificarSocio() {
    sociosArchivos archivoSocio;
    Socio socio;
    int numeroSocio;


    cout << "INGRESE UN NUMERO DE SOCIO QUE QUIERA MODIFICAR : ";
    cin >> numeroSocio;


    int posicion = archivoSocio.buscarArchivoSocio(numeroSocio);
    if (posicion == -1) {
        cout << "NO EXISTE ASOCIADO CON ESE NUMERO DE SOCIO ." << endl;
        return;
    }


    socio = archivoSocio.LeerSocio(posicion);

    // Mostrar datos actuales del socio
    cout << "DATOS ACTUALES DEL SOCIO A MODIFICAR :" << endl;
    socio.mostrarSocioPantalla();

    // Solicitar nuevos datos
    string nombre, apellido, telefono, direccion, email,dni;


   cout <<"===============================" << endl;
    cout <<"INGRESE DATOS DEL SOCIO : " << endl;

    cout << "== NOMBRE ==" << endl;
      cin.ignore();
    getline(cin,nombre);
    cout << "== APELLIDO ==" << endl;

    getline(cin,apellido);
    cout << "== DNI ==" << endl;
    getline(cin,dni);
    cout << "== TELEFONO ==" << endl;

    getline(cin,telefono);
    cout << "== DIRECCION ==" << endl;
    getline(cin,direccion);
    cout << "== EMAIL ==" << endl;

    getline(cin,email);


    socio.setNumeroSocio(numeroSocio);
    socio.setNombre(nombre);
    socio.setApellido(apellido);
    socio.setTelefono(telefono);
    socio.setDireccion(direccion);
    socio.setEmail(email);
    //socio.setFechaNacimiento(fechaNacimiento);


    int resultado = archivoSocio.modificarSocio(socio, posicion);
    if (resultado > 0) {
        cout << "SOCIO MODIFICADO CORRECTAMENTE ." << endl;
    } else {
        cout << "ERROR NO SE PUDO MODIFICAR EL SOCIO ." << endl;
    }
}

