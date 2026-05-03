#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>

using namespace std;

class Menu {
    public:

        
        Menu() {
            estado = true;
        }

        
        Menu(int c, string n, string cat, int p, string d, bool e) {
            codigo = c;
            nombre = n;
            categoria = cat;
            precio = p;
            descripcion = d;
            estado = e;
        }

        
        virtual ~Menu() {
        }

        
        int Getcodigo() {
            return codigo;
        }

        void Setcodigo(int val) {
            codigo = val;
        }

        
        string Getnombre() {
            return nombre;
        }

        void Setnombre(string val) {
            nombre = val;
        }

        
        string Getcategoria() {
            return categoria;
        }

        void Setcategoria(string val) {
            categoria = val;
        }

        
        int Getprecio() {
            return precio;
        }

        void Setprecio(int val) {
            precio = val;
        }

        
        string Getdescripcion() {
            return descripcion;
        }

        void Setdescripcion(string val) {
            descripcion = val;
        }

        //Otros metodos
        //Funcion Agregar Menu
        static bool agregarM(string nombre, string categoria, int precio,
                     string descripcion, vector<Menu>& menu) {

            bool estado = true;

            int codigo = menu.size() + 1;

            Menu nuevo(codigo, nombre, categoria, precio, descripcion, estado);

            menu.push_back(nuevo);

            return true;
        }

    protected:

    private:
        int codigo;
        string nombre;
        string categoria;
        int precio;
        string descripcion;
        bool estado;
};

#endif // MENU_H