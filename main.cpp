#include "auth.h"
#include "menuPrincipal.h"

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
    //YA SE INGRESO AL SISTEMA_ IMPLEMENTAR MENU DE GESTION DE CONTRASENAS

    menuPrincipal(nombreUsuario, contrasenas);

    return 0;
}
