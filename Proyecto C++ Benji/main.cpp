#include <iostream> // Salida de datos
#include <string> // Permite generar y usar strings
#include <ctime> // Se usa para generar números aleatorios siempre
#include <Windows.h> // Se usa para que la terminal pueda mostrar acentos
// Importa la clase de Licoreria
#include "Licoreria.h"

using namespace std;

// Función que inicia sesión a los administradores
bool login();

int main() {

    // Función que ayuda a generar ID random de clientes siempre
    srand(time(NULL)); 

    /*
    funciones de Windows.h para poder mostrar los acentos al ejecutar 
    el código
    */
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
        cout << "\n¿Quién eres?" << endl;
        cout << "1. Admin/Empleado" << endl;
        cout << "2. Cliente" << endl;
        cout << "3. Salir" << endl;
        cin >> rol;

        switch (rol) {
            case 1: {
                if (!login()) break;

                int opcion;
                do {
                    cout << "\nQue quieres hacer?\n" << endl;
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
                            cout << "\nQue tipo de Bebida quieres agregar?"
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

                            cin.ignore();
                            cout << "Nombre: ";   
                            getline(cin, nombre);
                            cout << "Marca: ";    
                            getline(cin, marca);
                            cout << "Pais: ";     
                            getline(cin, pais);
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
                                    cin.ignore();
                                    cout << "Tipo de cerveza: ";
                                    getline(cin, tipo_cerveza);
                                    cout << "IBU (amargor): ";
                                    cin >> ibu;
                                    bar.agregar_bebida(new Cerveza("Cerveza", 
                                        stock, grados, precio, descuento, marca, 
                                        pais, nombre, tipo_cerveza, ibu));
                                    cout << "\nBebida agregada." << endl;
                                    break;
                                }
                                case 2: {
                                    string agave;
                                    int gusano;
                                    cin.ignore();
                                    cout << "Tipo de agave: ";
                                    getline(cin, agave);
                                    cout << "Tiene gusano? (1 = si, 0 = no): ";
                                    cin >> gusano;
                                    bar.agregar_bebida(new Mezcal("Mezcal", 
                                        stock, grados, precio, descuento, 
                                        marca, pais, nombre, agave, gusano));
                                    cout << "\nBebida agregada." << endl;
                                    break;
                                }
                                case 3: {
                                    string estilo;
                                    int especias;
                                    cin.ignore();
                                    cout << "Estilo: ";
                                    getline(cin, estilo);
                                    cout << "Tiene especias? (1 = si, 0 = no): ";
                                    cin >> especias;
                                    bar.agregar_bebida(new Ron("Ron", stock, 
                                        grados, precio, descuento, marca, pais, 
                                        nombre, estilo, especias));
                                    cout << "\nBebida agregada." << endl;
                                    break;
                                }
                                case 4: {
                                    string region, categoria;
                                    int agave;
                                    cin.ignore();
                                    cout << "Region: ";
                                    getline(cin, region);
                                    cout << "Categoria: ";
                                    cin >> categoria;
                                    cout << "100% agave? (1 = si, 0 = no): ";
                                    cin >> agave;
                                    bar.agregar_bebida(new Tequila("Tequila", 
                                        stock, grados, precio, descuento, 
                                        marca, pais, nombre, region, categoria, 
                                        agave));
                                    cout << "\nBebida agregada." << endl;
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
                                    cout << "\nBebida agregada." << endl;
                                    break;
                                }
                                case 6: {
                                    string sabor;
                                    int destilaciones;
                                    cin.ignore();
                                    cout << "Sabor: ";
                                    getline(cin, sabor);
                                    cout << "Numero de destilaciones: ";
                                    cin >> destilaciones;
                                    bar.agregar_bebida(new Vodka("Vodka", 
                                        stock, grados, precio, descuento, 
                                        marca, pais, nombre, sabor, 
                                        destilaciones));
                                    cout << "\nBebida agregada." << endl;
                                    break;
                                }
                                case 7: {
                                    string barrica;
                                    int years;
                                    cout << "Años de añejamiento: ";
                                    cin >> years;
                                    cin.ignore();
                                    cout << "Tipo de barrica: ";
                                    getline(cin, barrica);
                                    bar.agregar_bebida(new Whiskey("Whiskey", 
                                        stock, grados, precio, descuento, 
                                        marca, pais, nombre, years, barrica));
                                    cout << "\nBebida agregada." << endl;
                                    break;
                                }
                            }
                            break;
                        }
                        case 4: {
                            bar.mostrar_inventario();
                            cout << "\nIngresa el id de la bebida a eliminar: ";
                            int id;
                            cin >> id;
                            bar.eliminar_bebida(id);
                            break;
                        }
                        case 5: {
                            bar.mostrar_inventario();
                            cout << "\nIngresa el id de la bebida: ";
                            int id;
                            cin >> id;
                            cout << "\n";
                            bar.mostrar_info_bebida(id);
                            break;
                        }
                        case 6: {
                            cout << "\n";
                            bar.mostrar_empleado();
                            break;
                        }
                        case 7: {
                            cout << "\n";
                            bar.mostrar_empleado();
                            cout << "Número de Empleado: ";
                            int i;
                            cin >> i;
                            cout << "\n";
                            bar.mostrar_info_empleado(i);
                            break;
                        }
                        case 8: {
                            cout << "\n";
                            bar.contratar();
                            break;
                        }
                        case 9: {
                            cout << "\n";
                            bar.mostrar_empleado();
                            cout << "Número de Empleado: ";
                            int i;
                            cin >> i;
                            bar.editar_empleado(i);
                            break;
                        }
                        case 10: {
                            cout << "\n";
                            bar.mostrar_cliente();
                            break;
                        }
                        case 11: {
                            cout << "\n";
                            bar.mostrar_cliente();
                            cout << "\nNúmero de cliente: ";
                            int i;
                            cin >> i;
                            cout << "\n";
                            bar.mostrar_info_cliente(i);
                            cout << "\n";
                            break;
                        }
                        case 12: {
                            cout << "\n";
                            bar.registrar_new_cliente();
                            break;
                        }
                        case 13: {
                            cout << "\n";
                            bar.mostrar_cliente();
                            cout << "\nNúmero del Cliente a editar: ";
                            int i;
                            cin >> i;
                            cout << "\n";
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
                cout << "\nIdentificate con tu ID: ";
                int id_client;
                cin >> id_client;
                Cliente* c_actual = bar.getClientes(id_client);
                if (c_actual != nullptr) {
                    cout << "\nBienvenid@ " << c_actual->getNombre() << "!" 
                    << endl;

                    int c_opcion;
                    do{
                        cout << "\nQue quieres hacer?" << endl;
                        cout << "1. Ver carta de Bebidas" << endl;
                        cout << "2. Ver info de bebida" << endl;
                        cout << "3. Comprar Bebida" << endl;
                        cout << "4. Pagar mi cuenta" << endl;
                        cout << "5. Salir" << endl;
                        cout << "\nEscoge: ";
                        cin >> c_opcion;

                        switch (c_opcion) {
                            case 1: {
                                cout << "\n";
                                bar.mostrar_inventario();
                                break;
                            }
                            case 2: {
                                cout << "\n";
                                bar.mostrar_inventario();
                                cout << "\nIngresa el id de la bebida: ";
                                int id;
                                cin >> id;
                                cout << "\n";
                                bar.mostrar_info_bebida(id);
                                break;
                            }
                            case 3: {
                                cout << "\n";
                                bar.mostrar_inventario();
                                cout << "\nQue deseas comprar? Ingresa el id: ";
                                int id_bebida;
                                cin >> id_bebida;
                                cout << "\n";
                                bar.vender_trago(id_bebida, c_actual);
                                break;
                            }
                            case 4: {
                                cout << "\n";
                                c_actual->pagar_cuenta();
                                break;
                            }
                            case 5: {
                                cout << "\n";
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
                cout << "\n";
                cout << "Hasta luego" << endl;
                return false;
            }
            default:
                cout << "\nOPCIÓN NO VALIDA\n" << endl; 
            break;
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