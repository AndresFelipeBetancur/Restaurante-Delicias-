#ifndef PEDIDOS_H
#define PEDIDOS_H

#include <iostream>
#include <vector>

using namespace std;

class pedidos{
    public:
        pedidos(){
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