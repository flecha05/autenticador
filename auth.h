#ifndef AUTH_H
#define AUTH_H

#include <string>
#include<cstdint>

using namespace std;

class Autenticador {
    public:
        explicit Autenticador(const string& filename);
        bool autenticar();

        private:
        struct authArchivo {//formato de los datos
            uint64_t hash;
        };
        string filename;
        //Funciones de la clase ver si existe el archivo, crear y guardar, verificar
        bool fileExists()const;
        void crearMasterPassword();
        bool verificarContra()const;

        //Funcion para hashear la contrasena
        uint64_t simpleHash(const string& s)const;
};

#endif // AUTH_H