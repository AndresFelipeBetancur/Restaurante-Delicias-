#ifndef PEDIDOS_H
#define PEDIDOS_H

#include <iostream>
#include <vector>

using namespace std;

class Pedidos{
    public:
        Pedidos(){
            estado = true;
        }

    protected:

    private:
        string cedula;
        string nombre;
        string correo;
        string contrasena;
        bool estado;  
};
#endif