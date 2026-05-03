#ifndef FACTURAS_H
#define FACTURAS_H

#include <iostream>
#include <vector>

using namespace std;
class Facturas{
    public:
        Facturas(){
            estado = true;
        }
         Facturas(int c, string n, string cat, int p, string d, bool e) {
            codigo = c;
            nombre = n;
            categoria = cat;
            precio = p;
            descripcion = d;
            estado = e;
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
#endif