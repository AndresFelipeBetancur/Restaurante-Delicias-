//Proyecto Restaurante Programacion Orientada a Objetos
//Autores:
//- Andres Felipe Betancur Quintero-202563100
//- Juan Jose Garces Casas-
//- Juan Manuel Carvajal-
//- Eduardo Jose Castro-
//- Nicolas Diaz Galeano-
//Version: 1.0
//Descripcion: Este proyecto es un sistema de gestion de restaurante,
// el cual permite a los usuarios realizar pedidos,
// a los empleados gestionar los pedidos y a los administradores gestionar el menu y las mesas. 
// El sistema esta desarrollado en C++ utilizando el framework Crow para la parte web y Mysql para la base de datos.

#include<iostream>
#include "routes/Routes.h"
#include "crow.h"

using namespace std;

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([](){
        return "Hello world";
    });

    app.port(18080).run();
}
