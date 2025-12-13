#include <iostream>
#include "auth.h"


int main(){
    const string authPass = "authArchivo.dat";

    Autenticador auth(authPass);
    if(!auth.autenticar()){
        std::cout<<"Limite de intentos. Saliendo del sistema"<<std::endl;
        return 1;
    }

    //Ya se verifico la contrasena
    cout<<"Accediendo al sistema."<<endl;

    return 0;
}
