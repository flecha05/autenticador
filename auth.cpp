#include <iostream>
#include <string>
#include <fstream>
#include <cstdint>

using namespace std;

struct authArcivo //do formato authArchivo.dat
{
    uint64_t hash;
};

uint64_t simpleHash(const string& s){
    uint64_t h=1469598103934665603ULL; //tenemos un valor fjo
    for(char c : s){
        h^=c; // con el XOR entre C y H mezacla los bits
        h*=1099511628211ULL;//multiplicamos para realiar un cambio mayor
} 
    return h;
}

bool fileExists(const string& filename){
    ifstream f(filename, ios::binary);
    return f.good();
}

void crearMasterPassword(const string& fliname){
    string contra;
    cout<<"Crear contrasena maestra: ";
    getline(cin, contra);

    authArcivo auth;
    auth.hash = simpleHash(contra);

    ofstream f(fliname, ios::binary);
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

bool verificarContra(const string& filename){
    authArcivo auth;
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
    cout<<"Limite de intentos. Accesos Bloqueado."<<endl;
    return false;
}

int main(){
    const string authPass = "authArchivo.dat";

    if(!fileExists(authPass)){
        crearMasterPassword(authPass);
    }
    if(!verificarContra(authPass)){
        return 1; 
    }

    //Ya se verifico la contrasena
    cout<<"Accediendo al sistema."<<endl;

    return 0;
}
/*
==============================================
ESTADO ACTUAL DEL PROYECTO (CHECKPOINT)
==============================================

✔ Implementado:
- Verificación de master password
- Persistencia usando archivo binario (auth.dat)
- Hash simple (solo educativo)
- Flujo real de programa:
    * Si no existe auth.dat → crear master password
    * Si existe → pedir contraseña y verificar
    * 3 intentos → bloqueo y salida
- Uso de ifstream / ofstream
- Entendimiento RAM ↔ disco

==============================================
PRÓXIMOS PASOS RECOMENDADOS
==============================================

1) Extraer esta lógica a una clase Authenticator
   - auth.h / auth.cpp
   - main() solo debería llamar a:
       if (!auth.authenticate()) exit(1);

2) Reemplazar simpleHash por un hash real
   - PBKDF2 o Argon2
   - Guardar salt junto al hash en auth.dat

3) Definir estructura del archivo principal
   - passwords.dat
   - Contendrá:
       * cantidad de entradas
       * entradas cifradas

4) Crear estructura Entry
   - servicio
   - usuario
   - contraseña (solo en RAM)

5) Implementar menú CLI básico
   - add
   - list
   - get
   - delete

6) Cifrado simétrico de las entradas
   - clave derivada de la master password

==============================================
NOTAS IMPORTANTES
==============================================

- NO guardar strings directamente en binario
- El archivo es la memoria persistente
- El programa solo carga, modifica y guarda
- Priorizar claridad antes de seguridad perfecta

==============================================
FIN DEL CHECKPOINT
==============================================
*/