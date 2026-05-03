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

    protected:

    private:
        string cedula;
        string nombre;
        string correo;
        string contrasena;
        bool estado;  
};
#endif