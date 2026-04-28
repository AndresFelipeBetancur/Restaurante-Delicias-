//Proyecto Restaurante Programacion Orientada a Objetos
//Autores:
//- Andres Felipe Betancur Quintero-202563100
//- Juan Jose Garces Casas-202563114
//- Juan Manuel Carvajal-202563167
//- Nicolas Diaz Galeano-202563147
//Version: 1.25
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
#include <vector>
#include "include/Usuarios.h"


using namespace httplib;
using namespace std;

//USUARIOS ------------------------------------------------------
Usuarios u;

vector<Usuarios> usuarios;

//Usuario administrador del sistema, es unico y solo la entidad tiene acceso.
string usuarioAdmin[2] = {"Admin", "12345"};

//Funcion Agregar usuario



void agregarU(string cedula,string nombre,string correo,string pass){
    
    if(Usuarios::BuscarCedula(cedula, usuarios)) {
        cout << "Ya existe un usuario con el ID\n";
        return;
    }
    //activo de forma predeterminada
    bool estado = true;
    Usuarios u(cedula, nombre, correo, pass, estado);
    usuarios.push_back(u);
}

//Rutas ------------------------------------------------------------------


int main() {
    Server svr;

    svr.set_mount_point("/", "./web");

    //Ruta principal
    svr.Post("/pedido", [](const Request& req, Response& res) {
        std::cout << "Pedido: " << req.body << std::endl;

        res.set_content("OK", "text/plain");
    });
    

    //RUTAS DE USUARIO -------------------------------------------------

    //RUTAS ACTUALIZAR USUARIO
    svr.Get("/actualizarU", [](const Request& req, Response& res) {
        res.set_redirect("/actualizarU.html");
    });

    svr.Post("/actualizarUsuario", [&](const Request& req, Response& res) {
        
        string cedula = req.get_param_value("cedula");
        string nombre = req.get_param_value("nombre");
        string correo = req.get_param_value("correo");
        string pass = req.get_param_value("pass");
        
        if(Usuarios::BuscarCedula(cedula,usuarios)) {
            Usuarios::actualizar(cedula,nombre,correo,pass,usuarios);
            res.set_redirect("/administracion?msg=Usuario+actualizado!");
        } else {
            res.set_redirect("/actualizarU.html?msg=Este+usuario+no+existe.");
        }
        
    });



    

    //RUTAS ELIMINAR / DESHABILITAR USUARIO
    svr.Post("/eliminarUsuario", [&](const Request& req, Response& res) {
    
    std::string cedula = req.get_param_value("cedula");

    if (u.BuscarCedula(cedula, usuarios)) {
        Usuarios::eliminarUsuario(cedula, usuarios);
        res.set_redirect("/admin.html?msj=y");
    } else {
        res.set_redirect("/eliminarU.html?error=1");
    }
    });

    svr.Get("/eliminarU", [](const Request& req, Response& res) {
    res.set_redirect("/eliminarU.html");
    });

    //RUTA VISUALIZAR USUARIOS
    svr.Get("/verUsuario", [](const Request& req, Response& res) {
    string html = "<h1 style='text-align:center;'>Usuarios</h1>"
              "<table style='margin:auto; border:4px solid black; border-collapse:collapse;'>"
              "<tr>"
              "<th style='border:1px solid black; padding:8px;'>Cedula</th>"
              "<th style='border:1px solid black; padding:8px;'>Nombre</th>"
              "<th style='border:1px solid black; padding:8px;'>Correo</th>"
              "<th style='border:1px solid black; padding:8px;'>Contrasena</th>"
              "<th style='border:1px solid black; padding:8px;'>Estado</th>"
              "</tr>";
    
    for (auto& u : usuarios) {
        html += "<tr>"
                "<td style='border:1px solid black; padding:8px;'>" + u.Getcedula() + "</td>"
                "<td style='border:1px solid black; padding:8px;'>" + u.Getnombre() + "</td>"
                "<td style='border:1px solid black; padding:8px;'>" + u.Getcorreo() + "</td>"
                "<td style='border:1px solid black; padding:8px;'>" + u.Getcontrasena() + "</td>"
                "<td style='border:1px solid black; padding:8px;'>" + string(u.Getestado() ? "Activo" : "Inactivo") + "</td>"
                "</tr>";
    }

    html += "</table>";

    html += "<div style='text-align:center; margin-top:20px;'>"
        "<a href='/administracion'>"
        "<button style='border: solid 3px; width: 10%; height: 70px;'>Regresar</button>"
        "</a>"
        "</div>";

    res.set_content(html, "text/html"); 
    });

    //RUTAS PARA AGREGAR USUARIOS
    //Aqui se reciben los datos del nuevo usuario y se envian a la funcion crear usuario
    svr.Post("/nuevoUsuario", [&](const Request& req, Response& res) {
        string cedula = req.get_param_value("identificacion");
        string nombre = req.get_param_value("nombre");
        string correo = req.get_param_value("correo");
        string pass = req.get_param_value("contrasena");
        
        if(u.BuscarCedula(cedula,usuarios)) {
            res.set_redirect("/administracion?msg=Este+Usuario+ya+existe");
        } else {
            agregarU(cedula,nombre,correo,pass);
            res.set_redirect("/administracion?msg=Creado+Correctamente");
        }
        
    });

    //Ruta usuario/agregar
    svr.Get("/administracion", [](const Request& req, Response& res) {
    
    if(req.has_param("msg")) {
        string msg = req.get_param_value("msg");
        res.set_redirect("/admin.html?msg=" + msg);
    } else {
        res.set_redirect("/admin.html");
    }
    });

  
    svr.Get("/agregarUsuario", [](const Request& req, Response& res) {
    res.set_redirect("/agregarUsuario.html");
    });

    //RUTAS DE MESAS
    //Ruta mesas
    svr.Get("/mesas", [](const Request& req, Response& res) {
    res.set_redirect("/mesas.html");
    });


    
    //Rutas de inicio de sesion
    svr.Get("/sesion", [](const Request& req, Response& res) {
        res.set_redirect("/sesion.html");
    });
    //Aqui se reciben los datos del formulario sesion
    svr.Post("/inicioSesion", [](const Request& req, Response& res) {
        std::string cedula = req.get_param_value("identificacion");
        std::string pass = req.get_param_value("contrasena");


        if (cedula == usuarioAdmin[0] && pass == usuarioAdmin[1]) {
            res.set_redirect("/admin.html");
        } else {
            res.set_redirect("/sesion.html?error=1");
        }
        });

    
    //ESTRICTAMENTE DE LA LIBRERIA 
    std::cout << "Servidor encendido en puerto 8080 para conexion movil." << std::endl;

    // Ejecutar servidor en hilo separado
    std::thread server_thread([&svr]() {
        svr.listen("0.0.0.0", 8080);
    });

   

    server_thread.join();
    return 0;
}