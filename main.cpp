#include <iostream>
#include "auth.h"
#include "util.h"

#include <fstream>
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

void agregarServicio(Usuario& user){
    string servicio, contrasena;
    cout<<"Ingrese el nuevo servicio: ";
    cin>>servicio;
    cout<<"Ingrese la contrasena para "<<servicio<<": ";
    cin>>contrasena;

    user.entradas.push_back({servicio, contrasena});
}
void verServicios(){
    Usuario infoUsuario = leerUsuario("contrasenas.dat");
    cout<<"Usuario: "+infoUsuario.nombre<<endl;
    for(const auto& entry : infoUsuario.entradas){
        cout<<"Servicio: "+entry.servicio+" - Contrasena: "+entry.contrasena<<endl;
    }
}

int main(){
    const string authPass = "authArchivo.dat";

    cout<<"----------GESTOR DE CONTRASENAS----------"<<endl;
    cout<<"Verifique su identidad."<<endl;


    Autenticador auth(authPass);
    if(!auth.autenticar()){
        std::cout<<"Limite de intentos. Saliendo del sistema"<<std::endl;
        return 1;
    }

    //Ya se verifico la contrasena
    Usuario user;

    if (fileExists("contrasenas.dat")) {
        user = leerUsuario("contrasenas.dat");
    } else {
        user.nombre = "user1";
    }

    int choice=0;
    char c='y';
    do{
    cout<<endl<<"Indique que desea hacer: "<<endl;
    cout<<"1. Agregar nuevo servicio "<<endl;
    cout<<"2. Ver servicios guardados "<<endl;
    cout<<"0. Salir "<<endl;
    
    cin>>choice;
    
    switch (choice)
    {
    case 1:
        do{ 
            agregarServicio(user);
            cout<<"Quiere agregar nuevos servicios? (y/n): ";
            cin>>c;
        }while(c=='y' || c=='Y');
        guardarUsuario(user, "contrasenas.dat");
        cout<<"Servicios guardados correctamente."<<endl;
        break;
    case 2:
        verServicios();
        break;
    case 0:
        cout<<"Saliendo del gestor de contrasenas."<<endl;
        return 0;    
    
    default:
        cout<<"Opcion no valida. Saliendo."<<endl;
        break;
    }
}while(choice!=0);
    return 0;
}
