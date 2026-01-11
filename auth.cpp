#include "auth.h"
#include <iostream>
#include <fstream>
#include <sodium.h>


using namespace std;

Autenticador::Autenticador(const string& filename): filename(filename) {
    if (sodium_init() < 0) {
        throw runtime_error("Error al inicializar libsodium");
    }
}


bool Autenticador::fileExists()const {
    std::ifstream f(filename, std::ios::binary);
    return f.good();
}

void Autenticador::crearMasterPassword(){
    string contra;
    cout<<"Crear contrasena maestra: ";
    getline(cin, contra);

    string hash = hashContrasena(contra);
    ofstream f(filename);
    f<<hash;
}
/*
  ofstream: abre o crea el archivo y escribe los datos de auth-Guarda en binario
  ifstream: abre el archivo para leer los datos de auth-Lee en binario
  ios::binary: trabajamos en modo binario no se interpreta nada
  reinterpret_cast: indica que trate el struct como bytes.
  escribo-->memoria-->archivo
  leo-->archivo-->memoria
*/

bool Autenticador::verificarContra(const string& hashGuardado)const{
    string contra;
    cout<<"Ingresar contrasena maestra: ";
    getline(cin, contra);
    return verificarHash(contra, hashGuardado);
}

bool Autenticador::autenticar(){
    if(!fileExists()){
        crearMasterPassword();
        return true;
    }
    ifstream f(filename);
    string hashGuardado;
    getline(f, hashGuardado);

    return verificarContra(hashGuardado);
}

string Autenticador::hashContrasena(const string& contrasena)const{
    char hash[crypto_pwhash_STRBYTES];

    if (crypto_pwhash_str(
            hash,
            contrasena.c_str(),
            contrasena.size(),
            OPSLIMIT,
            MEMLIMIT
        ) != 0) {
        throw runtime_error("Error al hashear la contrasena");
    }
    return string(hash);
}
bool Autenticador::verificarHash(const string& contrasena, const string& hashGuardado)const{
   return crypto_pwhash_str_verify(
        hashGuardado.c_str(),
        contrasena.c_str(),
        contrasena.size()
    ) == 0;
}