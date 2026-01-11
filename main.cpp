#include "auth.h"
#include "menuPrincipal.h"

#include <iostream>
#include <string>

using namespace std;

int main(){
   
   
try {
        Autenticador auth("auth.dat");

        if (auth.autenticar()) {
            std::cout << "Autenticacion exitosa\n";
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
            //YA SE INGRESO AL SISTEMA_ IMPLEMENTAR MENU DE GESTION DE CONTRASENAS

            menuPrincipal(nombreUsuario, contrasenas);

        } else {
            std::cout << "Password incorrecta\n";
        }

    } catch (const std::exception& e) {
        std::cerr << "Error fatal: " << e.what() << '\n';
        return 1;
    }

    return 0;
}
