#ifndef PEDIDOS_H
#define PEDIDOS_H

#include <iostream>
#include <vector>

using namespace std;

class Mesas{
    public:
        Mesas(){
            estado=true;
        }
        Mesas(int c, bool e) {
            codigo = c;
            estado = e;
        }

    protected:

    private:
        int codigo;
        bool estado;  
};
#endif