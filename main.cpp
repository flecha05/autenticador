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