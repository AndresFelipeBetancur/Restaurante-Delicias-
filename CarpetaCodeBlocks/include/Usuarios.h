//Proyecto Restaurante Programacion Orientada a Objetos
//Autores:
//- Andres Felipe Betancur Quintero-202563100 - Programador lider
//- Juan Jose Garces Casas-202563114 - Programador Auxiliar
//- Juan Manuel Carvajal-202563167 - Programador Apoyo
//- Nicolas Diaz Galeano-202563147 - Nicolas
//Version: 2.7
//Descripcion: La clase Usuarios representa la entidad principal
//encargada de gestionar la información de los usuarios registrados
//dentro del sistema de restaurante. Almacena datos básicos como
//cédula, nombre, correo electrónico, contraseña y estado de actividad.
//Además, implementa métodos para realizar operaciones fundamentales
//del sistema como registrar usuarios, buscar usuarios por cédula, 
//actualizar información, desactivar cuentas y validar el inicio de
//sesión. Esta clase sirve como base para la administración y control
//de acceso dentro de la aplicación.


#ifndef USUARIOS_H
#define USUARIOS_H
#include <iostream>
#include <vector>
using namespace std;

class Usuarios
{
    public:
        Usuarios() {
            estado = true;
        }

        Usuarios(string c, string n, string co, string p, bool e) {
            cedula = c;
            nombre = n;
            correo = co;
            contrasena = p;
            estado = e;
        }

        virtual ~Usuarios() {}

        string Getcedula() { return cedula; }
        void Setcedula(string val) { cedula = val; }

        static bool BuscarCedula(string id_buscar, vector<Usuarios>& usuarios) {
        for(int i = 0; i < usuarios.size(); i++) {
            if(usuarios[i].Getcedula() == id_buscar) {
                return true;
            }
        }
        return false;
        }

        string Getnombre() { return nombre; }
        void Setnombre(string val) { nombre = val; }

        string Getcorreo() { return correo; }
        void Setcorreo(string val) { correo = val; }

        string Getcontrasena() { return contrasena; }
        void Setcontrasena(string val) { contrasena = val; }

        bool Getestado() { return estado; }
        void Setestado(bool val) { estado = val; }
        
        //Otros metodos de usuario
        
        //Funcion Agregar usuario
        static bool agregarU(string cedula, string nombre, string correo, string pass, vector<Usuarios>& usuarios) {
    
            if(BuscarCedula(cedula, usuarios)) {
                return false;
            }

            bool estado = true;

            Usuarios nuevo(cedula, nombre, correo, pass, estado);

            usuarios.push_back(nuevo);

            return true;
        }



        static bool actualizar(string id_buscar, string nuevoNombre, string nuevoCorreo, string nuevaPass, vector<Usuarios>& usuarios) {
        for(int i = 0; i < usuarios.size(); i++) {
            if(usuarios[i].Getcedula() == id_buscar) {
                
                usuarios[i].Setnombre(nuevoNombre);
                usuarios[i].Setcorreo(nuevoCorreo);
                usuarios[i].Setcontrasena(nuevaPass);

                return true;
            }
        }
        return false;
        }



        static bool eliminarUsuario(string id_buscar, vector<Usuarios>& usuarios) {
        for(int i = 0; i < usuarios.size(); i++) {
            if(usuarios[i].Getcedula() == id_buscar) {
                
                
                usuarios[i].Setestado(!usuarios[i].Getestado());
            
            return true;
        }
        }
        return false;
        }


        static bool loguearUsuario(string id_buscar, string pass, vector<Usuarios>& usuarios) {
        for(int i = 0; i < usuarios.size(); i++) {
            if(usuarios[i].Getcedula() == id_buscar && 
                usuarios[i].Getcontrasena() == pass &&
                usuarios[i].Getestado()) {
                return true;      
        }
        }
        return false;
        }




    protected:

    private:
        string cedula;
        string nombre;
        string correo;
        string contrasena;
        bool estado;
};

#endif // USUARIOS_H
