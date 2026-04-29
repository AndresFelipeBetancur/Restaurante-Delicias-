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
