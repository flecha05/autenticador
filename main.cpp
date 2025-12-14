#include <iostream>
#include "auth.h"
#include "servicios.h"
#include "util.h"


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
        verServicios(user);
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
