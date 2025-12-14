#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <vector>

using namespace std;


struct Entry{
    string servicio;
    string contrasena;
    };
struct Usuario{
    string nombre;
    vector<Entry> entradas;
};

void guardarUsuario(const Usuario& user, const string& filename);
Usuario leerUsuario(const string& filename);

void agregarServicio(Usuario& user);
void verServicios(Usuario& user);


#endif // USUARIO_H