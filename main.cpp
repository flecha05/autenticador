#include "auth.h"
#include "servicios.h"
#include "util.h"

#include <iostream>
#include <string>

using namespace std;

int main(){
    string nombreUsuario;
    
    cout<<"----------GESTOR DE CONTRASENAS----------"<<endl;
    //Solicito el nombre del usuario para cargar sus archivos
    cout<<"Usuario: ";
    getline(cin,nombreUsuario);
    string authPass = nombreUsuario+"_auth.dat";
    string contrasenas = nombreUsuario + "_contras.dat";

    //Autentifico al usuario con su contrasena maestra o se crea contrasena
    Autenticador auth(authPass);
    if(!auth.autenticar()){
        cout<<"Limite de intentos. Saliendo del sistema"<<endl;
        return 1;
    }
    
    Usuario user;
    //Cargo los servicios del usuario si existen o comienza a crearlos
    if (fileExists(contrasenas)) {
        user = leerUsuario(contrasenas);
    } else {
        user.nombre = nombreUsuario;
    }
    //Menu para gestionar los servicios--PROXIMO PASO ENCAPSULAR EN FUNCION
    int choice=0;
    string accion;
    string c="y";
    
    do{
    guardarUsuario(user, contrasenas);
    cout<<endl<<"Indique que desea hacer: "<<endl;
    cout<<"1. Agregar nuevo servicio "<<endl;
    cout<<"2. Ver servicios guardados "<<endl;
    cout<<"3. Borrar un servicio "<<endl;
    cout<<"0. Salir "<<endl;
 
    getline(cin,accion);
    try {
        choice = stoi(accion);
    } catch (...) {
        cout << "Opcion invalida" << endl;
        continue;
    }

    switch (choice)
    {
    case 1:
        do{ 
            agregarServicio(user);
            cout<<"Quiere agregar nuevos servicios? (y/n): ";
            getline(cin,c);
        }while(c=="y" || c=="Y");
        guardarUsuario(user, contrasenas);
        cout<<"Servicios guardados correctamente."<<endl;
        break;
    case 2:
        verServicios(user,contrasenas);
        break;
    case 3:
        {
            borrarServicio(user);
            guardarUsuario(user, contrasenas);
            cout<<"Servicio borrado."<<endl;
        }
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
