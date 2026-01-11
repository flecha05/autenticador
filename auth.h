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
            string hash;
        };
        string filename;
        //Funciones de la clase ver si existe el archivo, crear y guardar, verificar
        bool fileExists()const;
        void crearMasterPassword();
        bool verificarContra(const string& hashGuardado)const;

        //Implememtar Argon2 
        string hashContrasena(const string& contrasena)const;
        bool verificarHash(const string& contrasena, const string& hashGuardado)const;

        //Pararmetros de configuracion
        static constexpr unsigned long long OPSLIMIT = 2;// cantidad de vueltas que realiza
        static constexpr size_t MEMLIMIT = 128 * 1024 * 1024;//Memoria que utiliza 128MB
};

#endif // AUTH_H