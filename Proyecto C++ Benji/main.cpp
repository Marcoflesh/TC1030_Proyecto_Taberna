#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include "Licoreria.h"

using namespace std;

bool login();

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    setlocale(LC_NUMERIC, "C");

    Licoreria bar("Taberna de Moe");
    bar.cargar_bebidas();
    bar.cargar_clientes();
    bar.cargar_empleados();

    int rol;

    cout << "Bienvenido a " << bar.getNombre() << endl;

    do {
        cout << "¿Quién eres?" << endl;
        cout << "1. Admin/Empleado" << endl;
        cout << "2. Cliente" << endl;
        cout << "3. Salir" << endl;
        cin >> rol;

        switch (rol) {
            case 1: {
                if (!login()) break;

                int opcion;
                do {
                    cout << "Que quieres hacer?" << endl;
                    cout << "1. Mostrar inventario" << endl;
                    cout << "2. Modificar Stock de Bebidas" << endl;
                    cout << "3. Agregar nueva bebida" << endl;
                    cout << "4. Eliminar Bebida" << endl;
                    cout << "5. Ver info de Bebida" << endl;
                    cout << "6. Ver Empleados" << endl;
                    cout << "7. Info Empleado" << endl;
                    cout << "8. Contratar Empleado" << endl;
                    cout << "9. Editar Empleado" << endl;
                    cout << "10. Ver Clientes" << endl;
                    cout << "11. Info de Cliente" << endl;
                    cout << "12. Registrar Nuevo Cliente" << endl;
                    cout << "13. Editar Cliente" << endl;
                    cout << "14. Volver al inicio" << endl;
                    cout << "Opcion: ";
                    cin >> opcion;

                    switch (opcion) {
                        case 1: {
                            bar.mostrar_inventario();
                            break;
                        }
                        case 2: {
                            bar.mostrar_inventario();
                            cout << "Ingresa el 'id' de la bebida" << endl;
                            int id, cant;
                            cin >> id;
                            cout << "Indica la cantidad a agregar" 
                            << " (negativo para quitar)" << endl;
                            cin >> cant;
                            bar.ajustar_inventario(id, cant);
                            break;
                        }
                        case 3: {
                            cout << "Que tipo de Bebida quieres agregar?"
                            << endl;
                            cout << "1. Cerveza" << endl;
                            cout << "2. Mezcal" << endl;
                            cout << "3. Ron" << endl;
                            cout << "4. Tequila" << endl;
                            cout << "5. Vino" << endl;
                            cout << "6. Vodka" << endl;
                            cout << "7. Whiskey" << endl;
                            cout << "Tipo: ";
                            int tipo;
                            cin >> tipo;
                            string nombre, marca, pais;
                            int stock;
                            float grados, precio, descuento;

                            cout << "utiliza \"_\" en vez de espacios" << endl;
                            cout << "Nombre: ";   
                            cin >> nombre;
                            cout << "Marca: ";    
                            cin >> marca;
                            cout << "Pais: ";     
                            cin >> pais;
                            cout << "Stock: ";    
                            cin >> stock;
                            cout << "Grados de alcohol: "; 
                            cin >> grados;
                            cout << "Precio: $";  
                            cin >> precio;
                            cout << "Descuento (ej. 0.10 para 10%): "; 
                            cin >> descuento;

                            switch (tipo) {
                                case 1: {
                                    string tipo_cerveza;
                                    float ibu;
                                    cout << "Tipo de cerveza ";
                                    cin >> tipo_cerveza;
                                    cout << "IBU (amargor): ";
                                    cin >> ibu;
                                    bar.agregar_bebida(new Cerveza("Cerveza", 
                                        stock, grados, precio, descuento, marca, 
                                        pais, nombre, tipo_cerveza, ibu));
                                    cout << "Bebida agregada." << endl;
                                    break;
                                }
                                case 2: {
                                    string agave;
                                    int gusano;
                                    cout << "Tipo de agave: ";
                                    cin >> agave;
                                    cout << "Tiene gusano? (1=si, 0=no): ";
                                    cin >> gusano;
                                    bar.agregar_bebida(new Mezcal("Mezcal", 
                                        stock, grados, precio, descuento, 
                                        marca, pais, nombre, agave, gusano));
                                    cout << "Bebida agregada." << endl;
                                    break;
                                }
                                case 3: {
                                    string estilo;
                                    int especias;
                                    cout << "Estilo: ";
                                    cin >> estilo;
                                    cout << "Tiene especias? (1=si, 0=no): ";
                                    cin >> especias;
                                    bar.agregar_bebida(new Ron("Ron", stock, 
                                        grados, precio, descuento, marca, pais, 
                                        nombre, estilo, especias));
                                    cout << "Bebida agregada." << endl;
                                    break;
                                }
                                case 4: {
                                    string region, categoria;
                                    int agave;
                                    cout << "Region: ";
                                    cin >> region;
                                    cout << "Categoria: ";
                                    cin >> categoria;
                                    cout << "100% agave? (1=si, 0=no): ";
                                    cin >> agave;
                                    bar.agregar_bebida(new Tequila("Tequila", 
                                        stock, grados, precio, descuento, 
                                        marca, pais, nombre, region, categoria, 
                                        agave));
                                    cout << "Bebida agregada." << endl;
                                    break;
                                }
                                case 5: {
                                    string uva;
                                    int year;
                                    cout << "Tipo de uva: ";
                                    cin >> uva;
                                    cout << "Año de cosecha: ";
                                    cin >> year;
                                    bar.agregar_bebida(new Vino("Vino", stock, 
                                        grados, precio, descuento, marca, pais, 
                                        nombre, uva, year));
                                    cout << "Bebida agregada." << endl;
                                    break;
                                }
                                case 6: {
                                    string sabor;
                                    int destilaciones;
                                    cout << "Sabor: ";
                                    cin >> sabor;
                                    cout << "Numero de destilaciones: ";
                                    cin >> destilaciones;
                                    bar.agregar_bebida(new Vodka("Vodka", 
                                        stock, grados, precio, descuento, 
                                        marca, pais, nombre, sabor, 
                                        destilaciones));
                                    cout << "Bebida agregada." << endl;
                                    break;
                                }
                                case 7: {
                                    string barrica;
                                    int years;
                                    cout << "Años de añejamiento: ";
                                    cin >> years;
                                    cout << "Tipo de barrica: ";
                                    cin >> barrica;
                                    bar.agregar_bebida(new Whiskey("Whiskey", 
                                        stock, grados, precio, descuento, 
                                        marca, pais, nombre, years, barrica));
                                    cout << "Bebida agregada." << endl;
                                    break;
                                }
                            }
                            break;
                        }
                        case 4: {
                            bar.mostrar_inventario();
                            cout << "Ingresa el id de la bebida a eliminar";
                            int id;
                            cin >> id;
                            bar.eliminar_bebida(id);
                            break;
                        }
                        case 5: {
                            bar.mostrar_inventario();
                            cout << "Ingresa el id de la bebida: ";
                            int id;
                            cin >> id;
                            bar.mostrar_info_bebida(id);
                            break;
                        }
                        case 6: {
                            bar.mostrar_empleado();
                            break;
                        }
                        case 7: {
                            bar.mostrar_empleado();
                            cout << "Número de Empleado: ";
                            int i;
                            cin >> i;
                            bar.mostrar_info_empleado(i);
                            break;
                        }
                        case 8: {
                            bar.contratar();
                            break;
                        }
                        case 9: {
                            bar.mostrar_empleado();
                            cout << "Número de Empleado: ";
                            int i;
                            cin >> i;
                            bar.editar_empleado(i);
                            break;
                        }
                        case 10: {
                            bar.mostrar_cliente();
                            break;
                        }
                        case 11: {
                            bar.mostrar_cliente();
                            cout << "Número de cliente: ";
                            int i;
                            cin >> i;
                            bar.mostrar_info_cliente(i);
                            break;
                        }
                        case 12: {
                            bar.registrar_new_cliente();
                            break;
                        }
                        case 13: {
                            bar.mostrar_cliente();
                            cout << "Número del Cliente a editar: ";
                            int i;
                            cin >> i;
                            bar.editar_cliente(i);
                            break;
                        }
                        case 14: {
                            bar.guardar_todo();
                            break;
                        }
                    }
                } while (opcion != 14);
                break;
            }
            case 2: {
                bar.mostrar_cliente();
                cout << "Identificate con el número que está a la izquierda: ";
                int id_client;
                cin >> id_client;
                if (id_client >= 0 && id_client < bar.total_clientes()) {
                    Cliente* c_actual = bar.getClientes(id_client);
                    cout << "Bienvenido " << c_actual->getNombre() << endl;

                    int c_opcion;
                    do{
                        cout << "Que quieres hacer?" << endl;
                        cout << "1. Ver carta de Bebidas" << endl;
                        cout << "2. Ver info de bebida" << endl;
                        cout << "3. Comprar Bebida" << endl;
                        cout << "4. Pagar mi cuenta" << endl;
                        cout << "5. Salir" << endl;
                        cout << "Escoge: ";
                        cin >> c_opcion;

                        switch (c_opcion) {
                            case 1: {
                                bar.mostrar_inventario();
                                break;
                            }
                            case 2: {
                                bar.mostrar_inventario();
                                cout << "Ingresa el id de la bebida: ";
                                int id;
                                cin >> id;
                                bar.mostrar_info_bebida(id);
                                break;
                            }
                            case 3: {
                                bar.mostrar_inventario();
                                cout << "Que deseas comprar? Ingresa el id: ";
                                int id_bebida;
                                cin >> id_bebida;
                                bar.vender_trago(id_bebida, c_actual);
                                break;
                            }
                            case 4: {
                                c_actual->pagar_cuenta();
                                break;
                            }
                            case 5: {
                                bar.guardar_todo();
                                return false;
                            }
                        }
                    } while (c_opcion != 5);
                } else {
                    cout << "Cliente no encontrado" << endl;
                }
                break;
            }
            case 3: {
                bar.guardar_todo();
                cout << "Hasta luego" << endl;
                return false;
            }
        }
    } while (true);

    return 0;
}

bool login() {
    string user, password;
    for (int i = 1; i <= 3; i++) {
        cout << "Usuario: ";
        cin >> user;
        cout << "Contraseña: ";
        cin >> password;

        if (user == "Marcoflecha" && password == "TabernaMou123") {
            cout << "Bienvenido" << endl;
            return true;
        } else {
            cout << "Acceso denegado. Intentos restantes: " << (3 - i) << endl;
        }
    }
    cout << "Demasiados intentos." << endl;
    return false; 
}