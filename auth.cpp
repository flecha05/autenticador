#include "auth.h"
#include <iostream>
#include <fstream>

using namespace std;

Autenticador::Autenticador(const string& filename): filename(filename) {}

uint64_t Autenticador::simpleHash(const string& s)const {
    uint64_t h=1469598103934665603ULL; //tenemos un valor fjo
    for(char c : s){
        h^=c; // con el XOR entre C y H mezacla los bits
        h*=1099511628211ULL;//multiplicamos para realiar un cambio mayor
} 
    return h;
}

bool Autenticador::fileExists()const {
    std::ifstream f(filename, std::ios::binary);
    return f.good();
}

void Autenticador::crearMasterPassword(){
    string contra;
    cout<<"Crear contrasena maestra: ";
    getline(cin, contra);

    authArchivo auth;
    auth.hash = simpleHash(contra);

    ofstream f(filename, ios::binary);
    f.write(reinterpret_cast<const char*>(&auth), sizeof(auth));
    f.close();

    cout<<"Contrasena creada"<<endl;
}
/*
  ofstream: abre o crea el archivo y escribe los datos de auth-Guarda en binario
  ifstream: abre el archivo para leer los datos de auth-Lee en binario
  ios::binary: trabajamos en modo binario no se interpreta nada
  reinterpret_cast: indica que trate el struct como bytes.
  escribo-->memoria-->archivo
  leo-->archivo-->memoria
*/

bool Autenticador::verificarContra()const{
    authArchivo auth;
    ifstream f(filename, ios::binary);
    f.read(reinterpret_cast<char*>(&auth), sizeof(auth));
    f.close();

    for (int intentos=0; intentos<3; ++intentos){
        string contra;
        cout<<"Ingresar contrasena: ";
        getline(cin, contra);

        if(simpleHash(contra) == auth.hash){
            cout<<"Acceso concedido"<<endl;
            return true;
        } else {
            cout<<"Contrasena incorrecta"<<endl;
        }
    }
    return false;
}

bool Autenticador::autenticar(){
    if(!fileExists()){
        crearMasterPassword();
    }
    return verificarContra();
}