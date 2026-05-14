#ifndef MESAS_H
#define MESAS_H

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


        virtual ~Mesas(){
        }

        int Getcodigo(){
            return codigo;
        }

        void Setcodigo(int val){
            codigo = val;
        }

        bool Getestado(){
            return estado;
        }

        void Setestado(bool val){
            estado = val;
        }

        static bool agregarMesa(vector<Mesas>& mesas){

            bool estado = true;

            int codigo = mesas.size() + 1;

            Mesas nueva(codigo, estado);

            mesas.push_back(nueva);

            return true;
        }

        static bool agregarMesa(vector<Mesas>& mesas){

            bool estado = true;

            int codigo = mesas.size() + 1;

            Mesas nueva(codigo, estado);

            mesas.push_back(nueva);

            return true;
        }

        static bool BuscarCodigo(int id_buscar, vector<Mesas>& mesas){
        
            for(int i = 0; i < mesas.size(); i++){
        
                if(mesas[i].Getcodigo() == id_buscar){
                    return true;
                }
            }
        
            return false;
        }
        
        static bool eliminarMesa(int id_buscar, vector<Mesas>& mesas){
        
            for(int i = 0; i < mesas.size(); i++){
        
                if(mesas[i].Getcodigo() == id_buscar){
        
                    mesas[i].Setestado(!mesas[i].Getestado());
        
                    return true;
                }
            }
        
            return false;
        }

        static bool eliminarMesa(int id_buscar, vector<Mesas>& mesas){

            for(int i = 0; i < mesas.size(); i++){

                if(int(mesas[i].Getcodigo()) == id_buscar){

                    mesas[i].Setestado(!mesas[i].Getestado());

                    return true;
                }
            }

            return false;
        }

    protected:

    private:
        int codigo;
        bool estado;  
};
#endif
