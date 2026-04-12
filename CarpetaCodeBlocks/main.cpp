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
// Se utilizo la libreria cpp-httplib para implementar un servidor HTTP en C++,
// permitiendo la comunicacion entre dispositivos moviles y el sistema del restaurante mediante solicitudes POST.
// vectores para la almacenacion de datos.

#define _WIN32_WINNT 0x0A00
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include "httplib.h"
#include <thread> 

using namespace httplib;
using namespace std;





int main() {
    Server svr;

    svr.set_mount_point("/", "./web");

    //Ruta principal
    svr.Post("/pedido", [](const Request& req, Response& res) {
        std::cout << "Pedido: " << req.body << std::endl;
        res.set_content("OK", "text/plain");
    });

    //Ruta mesas
    svr.Get("/mesas", [](const Request& req, Response& res) {
    res.set_redirect("/mesas.html");
    });

    //Ruta inicio de sesion
    svr.Get("/sesion", [](const Request& req, Response& res) {
    res.set_redirect("/sesion.html");
    });


    std::cout << "Servidor encendido en puerto 8080 para conexion movil." << std::endl;

    // Ejecutar servidor en hilo separado
    std::thread server_thread([&svr]() {
        svr.listen("0.0.0.0", 8080);
    });

   

    server_thread.join();
    return 0;
}