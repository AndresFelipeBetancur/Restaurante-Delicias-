#ifndef FACTURAS_H
#define FACTURAS_H

#include <iostream>
#include <vector>

using namespace std;
class facturas{
    public:
        facturas(){
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