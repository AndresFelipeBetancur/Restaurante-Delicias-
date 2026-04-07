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
// Se utilizó la librería cpp-httplib para implementar un servidor HTTP en C++,
// permitiendo la comunicación entre dispositivos móviles y el sistema del restaurante mediante solicitudes POST.
// Mysql para la base de datos.

#define _WIN32_WINNT 0x0A00
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include "httplib.h"

using namespace httplib;

void menu() {

}

int main() {
    Server svr;


    svr.set_mount_point("/", "./web");

    // Ruta pedidos
    svr.Post("/pedido", [](const Request& req, Response& res) {
        std::cout << "Pedido: " << req.body << std::endl;
        res.set_content("OK", "text/plain");
    });

    std::cout << "Servidor encendido en puerto 8080 para conexion movil." << std::endl;

    svr.listen("0.0.0.0", 8080);}
