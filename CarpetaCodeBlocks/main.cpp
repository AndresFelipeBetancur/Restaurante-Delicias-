//Proyecto Restaurante Programacion Orientada a Objetos
//Autores:
//- Andres Felipe Betancur Quintero-202563100
//- Juan Jose Garces Casas-202563114
//- Juan Manuel Carvajal-202563167
//- Nicolas Diaz Galeano-202563147
//Version: 2.7
//Descripcion: Este proyecto es un sistema de gestion de restaurante,
// el cual permite a los usuarios realizar pedidos,
// a los empleados gestionar los pedidos el menu y las mesas.
// Se utilizo la libreria cpp-httplib para implementar un servidor HTTP en C++,
// permitiendo la comunicacion entre dispositivos moviles y el sistema del restaurante mediante solicitudes POST.
// vectores para la almacenacion de datos y un uso de estructura de datos primitivo(array) con el objetivo
// de satisfacer el requerimiento del proyecto.

#define _WIN32_WINNT 0x0A00
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include "httplib.h"

#include <thread> 
#include <vector>
#include "include/Usuarios.h"
#include "include/Menu.h"

using namespace httplib;
using namespace std;

//IMPORTACIONES ---------------------------------------------------------
//USUARIOS 
Usuarios u;
//MENU
Menu m;

//VECTORES DE OBJETOS ----------------------------------------------------
vector<Usuarios> usuarios;
vector<Menu> productos;


//Usuario administrador del sistema, es unico y solo la entidad tiene acceso.
string usuarioAdmin[2] = {"Admin", "12345"};


//Rutas ------------------------------------------------------------------


int main() {
    Server svr;

    svr.set_mount_point("/", "./web");

    //Ruta principal
    svr.Post("/pedido", [](const Request& req, Response& res) {
        std::cout << "Pedido: " << req.body << std::endl;

        res.set_content("OK", "text/plain");
    });
    //RUTAS DE MENU ----------------------------------------------------


    //RUTA VISUALIZAR menu
    svr.Get("/verMenu", [&](const Request& req, Response& res) {

    string encabezado = "<tr>"
                        "<th>Codigo</th>"
                        "<th>Nombre</th>"
                        "<th>Precio</th>"
                        "<th>Descripcion</th>"
                        "</tr>";

    string html = "<h1 style='text-align:center;'>Menu del Restaurante</h1>";

    // COMIDAS
    html += "<h2 style='text-align:center;'>Comidas</h2>";
    html += "<table border='1' style='margin:auto; border-collapse:collapse;'>" + encabezado;

    for (auto &m : productos) {
        if (m.Getcategoria() == "Comida") {
            html += "<tr>"
                    "<td>" + to_string(m.Getcodigo()) + "</td>"
                    "<td>" + m.Getnombre() + "</td>"
                    "<td>$" + to_string(m.Getprecio()) + "</td>"
                    "<td>" + m.Getdescripcion() + "</td>"
                    "</tr>";
        }
    }
    html += "</table><br><br>";

    // BEBIDAS
    html += "<h2 style='text-align:center;'>Bebidas</h2>";
    html += "<table border='1' style='margin:auto; border-collapse:collapse;'>" + encabezado;

    for (auto &m : productos) {
        if (m.Getcategoria() == "Bebida") {
            html += "<tr>"
                    "<td>" + to_string(m.Getcodigo()) + "</td>"
                    "<td>" + m.Getnombre() + "</td>"
                    "<td>$" + to_string(m.Getprecio()) + "</td>"
                    "<td>" + m.Getdescripcion() + "</td>"
                    "</tr>";
        }
    }
    html += "</table><br><br>";

    // POSTRES
    html += "<h2 style='text-align:center;'>Postres</h2>";
    html += "<table border='1' style='margin:auto; border-collapse:collapse;'>" + encabezado;

    for (auto &m : productos) {
        if (m.Getcategoria() == "Postre") {
            html += "<tr>"
                    "<td>" + to_string(m.Getcodigo()) + "</td>"
                    "<td>" + m.Getnombre() + "</td>"
                    "<td>$" + to_string(m.Getprecio()) + "</td>"
                    "<td>" + m.Getdescripcion() + "</td>"
                    "</tr>";
        }
    }
    html += "</table><br><br>";

    // Botón regresar
    html += "<div style='text-align:center; margin-top:20px;'>"
            "<a href='/menu'><button style='border: solid 3px; width:10%; height:70px;'>Regresar</button></a>"
            "</div>";

    res.set_content(html, "text/html");
});

    svr.Post("/nuevoMenu", [&](const Request& req, Response& res) {
        
        
        string nombre = req.get_param_value("nombre");
        string categoria = req.get_param_value("categoria");
        int precio = stoi(req.get_param_value("precio"));
        string descripcion = req.get_param_value("descripcion");
        
        Menu::agregarM(nombre,categoria,precio,descripcion,productos);
        res.set_redirect("/menu?msg=Creado+Correctamente");
        
    });

    svr.Get("/agregarMenu", [](const Request& req, Response& res) {
    res.set_redirect("/agregarMenu.html");
    });

    svr.Get("/menu", [](const Request& req, Response& res) {
    res.set_redirect("/menu.html");
    });




    //RUTAS DE MESAS ---------------------------------------------------
    //Aqui deberian estar las rutas de nicolas y juan manuel


    //RUTAS DE EMPLEADOS -----------------------------------------------

    


    svr.Get("/SesionE", [](const Request& req, Response& res) {
        res.set_redirect("/sesionE.html");
    });

    //Aqui se reciben los datos del formulario de empleados
    svr.Post("/inicioSesionE", [](const Request& req, Response& res) {
        std::string cedula = req.get_param_value("identificacion");
        std::string pass = req.get_param_value("contrasena");

        if (Usuarios::loguearUsuario(cedula,pass,usuarios)) {
            res.set_redirect("/empleados.html");
        } else {
            res.set_redirect("/sesionE.html?error=1");
        }
        });


        //Falta pedidos menu y facturas

    




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


    svr.Get("/verUsuarios", [](const Request& req, Response& res) {
    res.set_redirect("/visualizaciones.html");
    });


    // RUTA VISUALIZAR USUARIO POR CEDULA -----------------------------------------------------------
    svr.Get("/verEmpleado", [&](const Request& req, Response& res) {
        string cedula = req.get_param_value("cedula");

        string html = "<h1 style='text-align:center;'>Buscar por Cedula</h1>"
                "<table style='margin:auto; border:4px solid black; border-collapse:collapse;'>"
                "<tr>"
                "<th style='border:1px solid black; padding:8px;'>Cedula</th>"
                "<th style='border:1px solid black; padding:8px;'>Nombre</th>"
                "<th style='border:1px solid black; padding:8px;'>Correo</th>"
                "<th style='border:1px solid black; padding:8px;'>Contrasena</th>"
                "<th style='border:1px solid black; padding:8px;'>Estado</th>"
                "</tr>";

        bool encontrado = false;
        for (auto& u : usuarios) {
            if (u.Getcedula() == cedula) {
                html += "<tr>"
                        "<td style='border:1px solid black; padding:8px;'>" + u.Getcedula() + "</td>"
                        "<td style='border:1px solid black; padding:8px;'>" + u.Getnombre() + "</td>"
                        "<td style='border:1px solid black; padding:8px;'>" + u.Getcorreo() + "</td>"
                        "<td style='border:1px solid black; padding:8px;'>" + u.Getcontrasena() + "</td>"
                        "<td style='border:1px solid black; padding:8px;'>" + string(u.Getestado() ? "Activo" : "Inactivo") + "</td>"
                        "</tr>";
                encontrado = true;
            }
        }

        if (!encontrado) {
            html += "<tr><td colspan='5' style='text-align:center; padding:8px;'>No se encontro ningun usuario con esa cedula.</td></tr>";
        }

        html += "</table>";
        html += "<div style='text-align:center; margin-top:20px;'>"
                "<a href='/verUsuarios'>"
                "<button style='border: solid 3px; width: 10%; height: 70px;'>Regresar</button>"
                "</a>"
                "</div>";

        res.set_content(html, "text/html");
    });

    // RUTA VISUALIZAR USUARIOS ACTIVOS --------------------------------------------------------
    svr.Get("/verActivos", [&](const Request& req, Response& res) {
        string html = "<h1 style='text-align:center;'>Usuarios Activos</h1>"
                "<table style='margin:auto; border:4px solid black; border-collapse:collapse;'>"
                "<tr>"
                "<th style='border:1px solid black; padding:8px;'>Cedula</th>"
                "<th style='border:1px solid black; padding:8px;'>Nombre</th>"
                "<th style='border:1px solid black; padding:8px;'>Correo</th>"
                "<th style='border:1px solid black; padding:8px;'>Contrasena</th>"
                "<th style='border:1px solid black; padding:8px;'>Estado</th>"
                "</tr>";

        for (auto& u : usuarios) {
            if (u.Getestado()) {
                html += "<tr>"
                        "<td style='border:1px solid black; padding:8px;'>" + u.Getcedula() + "</td>"
                        "<td style='border:1px solid black; padding:8px;'>" + u.Getnombre() + "</td>"
                        "<td style='border:1px solid black; padding:8px;'>" + u.Getcorreo() + "</td>"
                        "<td style='border:1px solid black; padding:8px;'>" + u.Getcontrasena() + "</td>"
                        "<td style='border:1px solid black; padding:8px;'>Activo</td>"
                        "</tr>";
            }
        }

        html += "</table>";
        html += "<div style='text-align:center; margin-top:20px;'>"
                "<a href='/verUsuarios'>"
                "<button style='border: solid 3px; width: 10%; height: 70px;'>Regresar</button>"
                "</a>"
                "</div>";

        res.set_content(html, "text/html");
    });

    // RUTA VISUALIZAR USUARIOS INACTIVOS ---------------------------------------------------
    svr.Get("/verInactivos", [&](const Request& req, Response& res) {
        string html = "<h1 style='text-align:center;'>Usuarios Inactivos</h1>"
                "<table style='margin:auto; border:4px solid black; border-collapse:collapse;'>"
                "<tr>"
                "<th style='border:1px solid black; padding:8px;'>Cedula</th>"
                "<th style='border:1px solid black; padding:8px;'>Nombre</th>"
                "<th style='border:1px solid black; padding:8px;'>Correo</th>"
                "<th style='border:1px solid black; padding:8px;'>Contrasena</th>"
                "<th style='border:1px solid black; padding:8px;'>Estado</th>"
                "</tr>";

        for (auto& u : usuarios) {
            if (!u.Getestado()) {
                html += "<tr>"
                        "<td style='border:1px solid black; padding:8px;'>" + u.Getcedula() + "</td>"
                        "<td style='border:1px solid black; padding:8px;'>" + u.Getnombre() + "</td>"
                        "<td style='border:1px solid black; padding:8px;'>" + u.Getcorreo() + "</td>"
                        "<td style='border:1px solid black; padding:8px;'>" + u.Getcontrasena() + "</td>"
                        "<td style='border:1px solid black; padding:8px;'>Inactivo</td>"
                        "</tr>";
            }
        }

        html += "</table>";
        html += "<div style='text-align:center; margin-top:20px;'>"
                "<a href='/verUsuarios'>"
                "<button style='border: solid 3px; width: 10%; height: 70px;'>Regresar</button>"
                "</a>"
                "</div>";

        res.set_content(html, "text/html");
    });

    //RUTA VISUALIZAR USUARIOS GENERAL ---------------------------------------------------------------
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
        "<a href='/verUsuarios'>"
        "<button style='border: solid 3px; width: 10%; height: 70px;'>Regresar</button>"
        "</a>"
        "</div>";

    res.set_content(html, "text/html"); 
    });

    // RUTA VISUALIZAR ACTIVIDAD DE UN EMPLEADO
    svr.Get("/verActividad", [&](const Request& req, Response& res) {
        string cedula = req.get_param_value("cedula");

        string html = "<h1 style='text-align:center;'>Actividad del Empleado</h1>";

        bool encontrado = false;
        for (auto& u : usuarios) {
            if (u.Getcedula() == cedula) {
                encontrado = true;
                html += "<table style='margin:auto; border:4px solid black; border-collapse:collapse;'>"
                        "<tr>"
                        "<th style='border:1px solid black; padding:8px;'>Cedula</th>"
                        "<th style='border:1px solid black; padding:8px;'>Nombre</th>"
                        "<th style='border:1px solid black; padding:8px;'>Correo</th>"
                        "<th style='border:1px solid black; padding:8px;'>Estado</th>"
                        "</tr>"
                        "<tr>"
                        "<td style='border:1px solid black; padding:8px;'>" + u.Getcedula() + "</td>"
                        "<td style='border:1px solid black; padding:8px;'>" + u.Getnombre() + "</td>"
                        "<td style='border:1px solid black; padding:8px;'>" + u.Getcorreo() + "</td>"
                        "<td style='border:1px solid black; padding:8px;'>" + string(u.Getestado() ? "Activo" : "Inactivo") + "</td>"
                        "</tr>"
                        "</table>"
                        "<h2 style='text-align:center; margin-top:20px;'>" +
                        string(u.Getestado() ? "Este usuario esta activo!" : "Este usuario esta inactivo.") +
                        "</h2>";
            }
        }

        if (!encontrado) {
            html += "<p style='text-align:center;'>No se encontro ningun usuario con esa cedula.</p>";
        }

        html += "<div style='text-align:center; margin-top:20px;'>"
                "<a href='/verUsuarios'>"
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
        
        if(Usuarios::agregarU(cedula,nombre,correo,pass,usuarios)) {
            res.set_redirect("/administracion?msg=Creado+Correctamente");
        } else {
            res.set_redirect("/administracion?msg=Este+Usuario+ya+existe");
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