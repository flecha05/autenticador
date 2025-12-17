#include "menuPrincipal.h"


#include "servicios.h"
#include "util.h"
#include <iostream>
#include <string>
using namespace std;
void menuPrincipal(const string& nombreUsuario, const string& contrasenas){
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
        cout<<endl<<"Opcion: ";
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
            break;    
        
        default:
            cout<<"Opcion no valida. Saliendo."<<endl;
            break;
        }
        }while(choice!=0);
    }