#include "auth.h"
#include "servicios.h"
#include "util.h"

#include <iostream>
#include <string>

using namespace std;

int main(){
    const string authPass = "authArchivo.dat";

    cout<<"----------GESTOR DE CONTRASENAS----------"<<endl;
    
    cout<<"Verifique su identidad."<<endl;
    Autenticador auth(authPass);
    if(!auth.autenticar()){
        cout<<"Limite de intentos. Saliendo del sistema"<<endl;
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
    string accion;
    string c="y";
    
    do{
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
        guardarUsuario(user, "contrasenas.dat");
        cout<<"Servicios guardados correctamente."<<endl;
        break;
    case 2:
        verServicios(user);
        break;
    case 3:
        {
            borrarServicio(user);
            guardarUsuario(user, "contrasenas.dat");
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
