#include "servicios.h"
#include "util.h"

#include <iostream>
#include <fstream>
#include <cstdint>
#include <algorithm>

using namespace std;



void guardarUsuario(const Usuario& user, const string& filename){
    ofstream f(filename, ios::binary);

    //Deinfo el nombre del usuario

    uint32_t tamNombre = user.nombre.size();
    f.write(reinterpret_cast<const char*>(&tamNombre), sizeof(tamNombre));
    f.write(user.nombre.c_str(), tamNombre);

    //Defino la cantidad de servicios del usuario
    uint32_t cantEntradas = user.entradas.size();
    f.write(reinterpret_cast<const char*>(&cantEntradas), sizeof(cantEntradas));

    //Guardo los servicios y contrasenas
    for(const auto& entry : user.entradas){
        uint32_t servicioLen = entry.servicio.size();
        f.write(reinterpret_cast<const char*>(&servicioLen), sizeof(servicioLen));
        f.write(entry.servicio.c_str(), servicioLen);

        uint32_t contraLen = entry.contrasena.size();
        f.write(reinterpret_cast<const char*>(&contraLen), sizeof(contraLen));
        f.write(entry.contrasena.c_str(), contraLen);
    }
    f.close();
 } 


Usuario leerUsuario(const string& filename){
    Usuario user;
    ifstream f(filename, ios::binary);

    //Leo el nombre del usuario
    uint32_t tamNombre;
    f.read(reinterpret_cast<char*>(&tamNombre),sizeof(tamNombre));
    user.nombre.resize(tamNombre);
    f.read(&user.nombre[0],tamNombre);

    //Leo los servicios del usuario
    uint32_t cantEntradas;
    f.read(reinterpret_cast<char*>(&cantEntradas), sizeof(cantEntradas));
    user.entradas.resize(cantEntradas);

    //Leo el servicio y su contrasena
    for(auto& e:user.entradas){
        uint32_t servicioLen;
        f.read(reinterpret_cast<char*>(&servicioLen),sizeof(servicioLen));
        e.servicio.resize(servicioLen);
        f.read(&e.servicio[0],servicioLen);

        uint32_t contraLen;
        f.read(reinterpret_cast<char*>(&contraLen),sizeof(contraLen));
        e.contrasena.resize(contraLen);
        f.read(&e.contrasena[0],contraLen);
    }
    f.close();
    return user;
 }
 void borrarServicio(Usuario& user){
    Usuario updatedUser = user;
    auto& entries = updatedUser.entradas;
    string servicioBorrar;
    cout<<"Servicio a borrar: ";
    getline(cin,servicioBorrar);

    entries.erase(
        remove_if(entries.begin(), entries.end(),
                  [&servicioBorrar](const Entry& entry) {
                      return entry.servicio == servicioBorrar;
                  }),
        entries.end()
    );
    user = updatedUser;
}

void agregarServicio(Usuario& user){
    string servicio, contrasena;
    cout<<"Ingrese el nuevo servicio: ";
    getline(cin,servicio);
    cout<<"Ingrese la contrasena para "<<servicio<<": ";
    getline(cin,contrasena);

    user.entradas.push_back({servicio, contrasena});
}
void verServicios(Usuario& user){
    Usuario infoUsuario = leerUsuario("contrasenas.dat");
    cout<<"Usuario: "+infoUsuario.nombre<<endl;
    for(const auto& entry : infoUsuario.entradas){
        cout<<"Servicio: "+entry.servicio+" - Contrasena: "+entry.contrasena<<endl;
    }
}
