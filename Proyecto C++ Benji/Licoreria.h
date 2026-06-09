/*
 * Proyecto Licorería Clase Licoreria
 * Marco Antonio Hernández Roque
 * A01709802
 * 12/06/2026
 * Materia: TC1030 Programación Orientada a Objetos
 * Esta clase funciona como el cerebro del sistema. Guarda en vectores 
 * todas las bebidas del inventario, los empleados contratados y los clientes. 
 * También tiene las funciones para leer y escribir los archivos de texto.
 */

#ifndef LICORERIA_H
#define LICORERIA_H

#include <iostream>
#include <vector> // para guardar objetos en arreglos
#include <string>
#include <fstream> // para poder cargar los archivos
#include <sstream> // para poder guardar los archivos

// Importa las clases
#include "Bebidas.h"
#include "Personas.h"

using namespace std;

class Licoreria {
private:
    // Se usan vectores de apuntadores para guardar objetos
    string nombre;
    vector <Bebida*> inventario;
    vector <Empleado*> lista_empleados;
    vector <Cliente*> registro_clientes;

public:
    Licoreria(string _nombre); // Muestra el nombre de la Licoreia
    virtual ~Licoreria(); // Libera la memoria de todos los vectores

    string getNombre();

    // Métodos para agregar nuevos objetos a los vectores correspondientes
    void agregar_bebida(Bebida* b);
    void contratar_empleado(Empleado* e);
    void registrar_cliente(Cliente* c);

    // Getters
    Bebida* getBebida(int i);
    Empleado* getEmpleado(int i);
    Cliente* getClientes(int id);

    // Métodos para el manejo del inventario

    void vender_trago(int index, Cliente* c);
    void mostrar_inventario();
    void mostrar_info_bebida(int index);
    void ajustar_inventario(int index, int cantidad); 
    void eliminar_bebida(int index); 
    
    // Métodos para el manejo de Empleados

    void mostrar_empleado(); 
    void mostrar_info_empleado(int index); 
    void contratar(); 
    void editar_empleado(int index); 

    // Métodos para el manejo de Clientes

    void mostrar_cliente(); 
    void mostrar_info_cliente(int id);
    void registrar_new_cliente(); 
    void editar_cliente(int id); 

    // Métodos para el manejo de los archivos

    void cargar_bebidas(); 
    void cargar_clientes();
    void cargar_empleados(); 
    void guardar_bebidas(); 
    void guardar_clientes(); 
    void guardar_empleados();
    void guardar_todo();
};

//Licoreria
Licoreria::Licoreria(string _nombre) {nombre = _nombre;}
string Licoreria::getNombre() {return nombre;}

void Licoreria::agregar_bebida(Bebida* b) {inventario.push_back(b);}
void Licoreria::contratar_empleado(Empleado* e) {lista_empleados.push_back(e);}
void Licoreria::registrar_cliente(Cliente* c) {registro_clientes.push_back(c);}

Bebida* Licoreria::getBebida(int i) {return inventario[i];}
Empleado* Licoreria::getEmpleado(int i) {return lista_empleados[i];}

/**
 * getClientes busca y devuelve un cliente por su ID único.
 * 
 * Recorre el vector de clientes comparando el id de cada uno con el
 * parámetro ingresado. Si lo encuentra devuelve el apuntador, si no lo
 * enuentra devuelve 'nullptr'
 * 
 * @param int id único del cliente a buscar
 * @return Cliente* apuntador al cliente encontrado, o nullptr si no
 * existe
 */
Cliente* Licoreria::getClientes(int id) {
        for(int i = 0; i < registro_clientes.size(); i++) {
            if (registro_clientes[i]->getCliente() == id) {
                return registro_clientes[i]; 
            }
        }
        return nullptr;
    }


// Inventario

/**
 * ~Licoreria destructor libera la memoria de todos los objetos guardados
 * en los vectores al terminar el programa.
 * 
 * Recorre cada vector y aplica delete a cada apuntador para evitar fugas
 * de memoria
 * 
 * @param
 * @return
 */
Licoreria::~Licoreria() {
    for (int i = 0; i < inventario.size(); i++) 
        delete inventario[i];
    for (int i = 0; i < lista_empleados.size(); i++) 
        delete lista_empleados[i];
    for (int i = 0; i < registro_clientes.size(); i++) 
        delete registro_clientes[i];
}

/**
 * vender_trago registra la venta de una bebida a un cliente
 * 
 * verifica que el índice sea válido y que haya stock suficiente, solicita
 * la cantidad deesada, aplica el descuento correspondiente, resta las
 * unidades del inventario y registra el consumo en la cuenta del cliente.
 * 
 * @param int index de la bebida, Cliente* c.
 * @return 
 */
void Licoreria::vender_trago(int index, Cliente* c) {
    if (index >= 0 && index < inventario.size()) {
        if (inventario[index]->getStock() > 0) {
            int cantidad;
            cout << "¿Cuántas unidades quieres?: ";
            cin >> cantidad;

            if (cantidad <= 0) {
                cout << "cantidad invalida" << endl;
                return;
            }
            if (cantidad > inventario[index]->getStock()) {
                cout << "No hay suficientes bebidas en stock" << endl;
                return;
            }
            inventario[index]->servir();
            float precio = inventario[index]->descontar(cantidad);
            inventario[index]->restarStock(cantidad);
            c->registro_consumo(precio, cantidad);
            cout << "Consumiste " << inventario[index]->getNombre() << endl;
            } else {
            cout << "Una disculpa, ya no queda " 
                << inventario[index]->getNombre() << " en stock." << endl;
        }
    } else {
        cout << "Numero de bebida no valido." << endl;
    }
}

/**
 * mostrar_inventario imprime en pantalla la lista de bebidas disponibles
 * 
 * Verifica que el inventario no esté vacío antes de recorrerlo. Muestra
 * el índice, nombre, marca y stock actual de cada bebida para que el
 * usuario pueda seleccionar por número.
 * 
 * @param
 * @return
 */
void Licoreria::mostrar_inventario() {
    cout << "Inventario" << endl;
    cout << "\n";
    if (inventario.empty()){
        cout << "No hay bebidas en el inventario" << endl;
        return;
    }else {
        for (int i = 0; i < inventario.size(); i++){
            cout << "(" << i << ") " << inventario[i]->getNombre() << ","
                << " Marca: " << inventario[i]->getMarca() << ","
                << " en stock hay: " << inventario[i]->getStock() << endl;
        }
    }
}

/**
 * mostrar_info_bebida imprime la información completa de una bebida.
 * 
 * valida que el índice sea válido y llama al toString() de la bebida
 * correspondiente para mostrar todos sus atributos en pantalla.
 * 
 * @param int index posición de la bebida en el vector inventario
 * @return 
 */
void Licoreria::mostrar_info_bebida(int index) {
    if (index >= 0 && index < inventario.size()) {
        cout << inventario[index]->toString() << endl;
    } else {
        cout << "Numero de bebida no valido." << endl;
    }
}

/**
 * ajustar_inventario agrega o quita unidades de una bebida en el
 * inventario.
 * 
 * valida que el índice sea válido. Si la cantidad es positiva llama a
 * sumarStock(), si es negativa llama a restarStock(). Imprime el resultado
 * de la operación en pantalla.
 * 
 * @param int index, int cantidad
 * @return
 */
void Licoreria::ajustar_inventario(int index, int cantidad) {
    if(index >= 0 && index < inventario.size()) {
        if (cantidad > 0) {
            inventario[index]->sumarStock(cantidad);
            cout << "Se agregaron " << cantidad << " botellas de: "
                << inventario[index]->getNombre() << endl;
        }else if (cantidad < 0) {
            inventario[index]->restarStock(cantidad);
            cout << "Se quitaron " << cantidad << " botellas de: "
                << inventario[index]->getNombre() << endl;
            }
        }else {
            cout << "Bebida no válida" << endl;
    }
}

/**
 * eliminar_bebida elimina completamente una bebida del inventario.
 * 
 * valida que el índice sea válido, imprime el nombre de la bebida
 * eliminada, libera su memoria con delete y la borra del vector.
 * 
 * @param int index de la beblida a eliminar en el vector inventario
 * @return
 */
void Licoreria::eliminar_bebida(int index) {
    if (index >= 0 && index < inventario.size()) {
        cout << "\nBebida eliminada: " << inventario[index]->getNombre() 
            << endl;
        delete inventario[index];
        inventario.erase(inventario.begin() + index);
    } else {
        cout << "Numero de bebida no valido." << endl;
    }
}

// Empleado

/**
 * mostrar_empleado imprime la lista de empleados contratados.
 * 
 * recorre el vector de empleados e imprime el índice, nombre completo y
 * puesto de cada uno para que el usuario pueda seleccionar por valor de 
 * [i].
 * 
 * @param
 * @return
 */
void Licoreria::mostrar_empleado() {
    cout << "Empleados" << endl;
    for (int i = 0; i < lista_empleados.size(); i++) {
        cout << i << " " << lista_empleados[i]->getNombre() << " "
        << lista_empleados[i]->getApellido() << ", " 
        << lista_empleados[i]->getPuesto() << endl;
    }
}

/**
 * mostrar_info_empleado imprime la información completa de un empleado.
 * 
 * valida que el índice sea válido y llama a mostrar_info() del empleado
 * correspondiente para mostrar todos sus atributos en pantalla.
 * 
 * @param int index posición del empleado en el vector lista_empleados
 * @return
 */
void Licoreria::mostrar_info_empleado(int index) {
    if (index >= 0 && index < lista_empleados.size()) {
        lista_empleados[index]->mostrar_info();
    } else {
        cout << "Empleado no reconocido" << endl;
    }
}

/**
 * contratar solicita los datos de un empleado nuevo a través de la
 * terminal y lo agrega al vector de empleados.
 * 
 * Pide todos los datos necesarios para construir un objeto Empleado y
 * llama a contratar_empleado() para agregarlo al vector.
 * 
 * @param
 * @return
 */
void Licoreria::contratar() {
    string nomb, ape, curp, direc, nacion, puesto, tel;
    int tarj, edad, horas;
    double sueldo;

    cin.ignore();
    cout << "Nombre: ";                     
    getline(cin, nomb);
    cout << "Apellido: ";                   
    getline(cin, ape);
    cout << "CURP: ";                       
    cin >> curp;
    cin.ignore();
    cout << "Direccion: ";                  
    getline(cin, direc);
    cout << "Nacionalidad: ";               
    cin >> nacion;
    cout << "Numero de tarjeta: ";          
    cin >> tarj;
    cout << "Telefono: ";                   
    cin >> tel;
    cout << "Edad: ";                       
    cin >> edad;
    cout << "Sueldo base: $";               
    cin >> sueldo;
    cout << "Horas de trabajo: ";           
    cin >> horas;
    cout << "Puesto: ";                     
    cin >> puesto;

    contratar_empleado(new Empleado(nomb, ape, curp, direc, nacion,
        tarj, tel, edad, sueldo, horas, puesto));
    cout << nomb << " " << ape << " contratado" << endl;
}

/**
 * editar_empleado permite modificar un atributo de un empleado existente
 * 
 * muestra la información actual del empleado y despliega un menú con los
 * campos editables. según la opción elegida solicita el nuevo valor y
 * llama al setter correspondiente del objeto.
 * 
 * @param int index del empleado a editar en el vector lista_empleados
 * @return
 */
void Licoreria::editar_empleado(int index) {
    Empleado *e = lista_empleados[index];
    e->mostrar_info();

    int opcion;
    cout << "\nQue deseas editar?" << endl;
    cout << "1. Direccion" << endl;
    cout << "2. Telefono" << endl;
    cout << "3. Tarjeta" << endl;
    cout << "4. Edad" << endl;
    cout << "5. Sueldo base" << endl;
    cout << "6. Horas de trabajo" << endl;
    cout << "7. Puesto" << endl;
    cout << "Opcion: ";
    cin >> opcion;

    cin.ignore();
        switch (opcion) {
        case 1: {
            string change;
            cout << "\nNueva direccion: "; 
            getline(cin, change); 
            e->setDireccion(change);    
            break; 
        }
        case 2: { 
            string change;    
            cout << "\nNuevo telefono: ";   
            getline(cin, change); 
            e->setTelefono(change);     
            break; 
        }
        case 3: { 
            int change;    
            cout << "\nNueva tarjeta: ";    
            cin >> change;
            e->setTarjeta(change);      
            break; 
        }
        case 4: {
            int change;
            cout << "\nNueva edad mayor a 18: ";
            cin >> change;
            e->setEdad(change); 
            break;
        }
        case 5: { 
            double change; 
            cout << "\nNuevo sueldo: $";    
            cin >> change;
            e->setSueldoBase(change);   
            break; 
        }
        case 6: { 
            int change;    
            cout << "\nNuevas horas: ";     
            cin >> change; 
            e->setHorasTrabajo(change); 
            break; 
        }
        case 7: { 
            string change; 
            cout << "\nNuevo puesto: ";     
            getline(cin, change); 
            e->setPuesto(change);       
            break; 
        }
    }
    cout << "Empleado actualizado." << endl;
}

// Clientes

/**
 * mostrar_cliente imprime la lista de clientes registrados.
 * 
 * recorre el vector de clientes e imprime el índice, nombre completo e
 * id único de cada uno para que el usuario pueda identificarlos.
 * 
 * @param
 * @return
 */
void Licoreria::mostrar_cliente() {
    cout << "Lista Clientes" << endl;
    cout << "\n";
    for (int i = 0; i < registro_clientes.size(); i++) {
        cout << i << " " << registro_clientes[i]->getNombre() << " "
        << registro_clientes[i]->getApellido() << " ID: "
        << registro_clientes[i]->getCliente() << endl;
    }
}

/**
 * mostrar_info_cliente imprime la información completa de un cliente.
 * 
 * usa getClientes() para buscar al cliente por su id. Si lo encuentra
 * llama a su mostrar_info(), si no, imprime un mensaje de error.
 * 
 * @param int id único del cliente a mostrar
 */
void Licoreria::mostrar_info_cliente(int id) {
    Cliente* cliente = getClientes(id);

    if (cliente != nullptr) {
        cliente->mostrar_info();
    } else {
        cout << "ID invalido" << endl;
    }
}

/**
 * registrar_new_cliente solicita los datos de un cliente nuevo por
 * terminal y lo agrega al vector de clientes.
 * 
 * pide todos los datos necesarios para construir un objeto Cliente y
 * llama a registrar_cliente() para agregarlo al vector.
 * 
 * @param
 * @return
 */
void Licoreria::registrar_new_cliente() {
    string nomb, ape, curp, direc, nacion, pref, tel;
    int    tarj, edad;

    cin.ignore();
    cout << "Nombre: ";           
    getline(cin, nomb);
    cout << "Apellido: ";         
    getline(cin, ape);
    cout << "CURP: ";             
    cin >> curp;
    cin.ignore();
    cout << "Direccion: ";        
    getline(cin, direc);
    cout << "Nacionalidad: ";     
    cin >> nacion;
    cout << "Numero de tarjeta: ";
    cin >> tarj;
    cout << "Telefono: ";         
    cin >> tel;
    cout << "Edad: ";             
    cin >> edad;
    cin.ignore();
    cout << "Bebida preferidas: "; 
    getline(cin, pref);

    registrar_cliente(new Cliente(nomb, ape, curp, direc, nacion,
        tarj, tel, edad, pref));
    cout <<  nomb << " registrado." << endl;
}

/**
 * editar_cliente permite modificar un atributo de un cliente existente.
 * 
 * busca al cliente por su id y muestra su información actual. Despliega
 * un menú con los campos editables y según la opción elegida solicita
 * el nuevo valor y llama al setter correspondiente del objeto.
 * 
 * @param int id único del cliente a editar
 * @return
 */
void Licoreria::editar_cliente(int id) {
    Cliente* c = getClientes(id);

    if (c == nullptr) {
        cout << "Id invalido" << endl;
        return;
    }

    c->mostrar_info();

    int opcion;
    cout << "\nQue deseas editar?" << endl;
    cout << "1. Direccion" << endl;
    cout << "2. Telefono" << endl;
    cout << "3. Tarjeta" << endl;
    cout << "4. Edad" << endl;
    cout << "5. Preferencia de bebida" << endl;
    cout << "Opcion: ";
    cin >> opcion;

    cin.ignore();
    switch (opcion) {
        case 1: { 
            string change; 
            cout << "Nueva direccion: ";    
            getline(cin, change); 
            c->setDireccion(change);        
            break; 
        }
        case 2: { 
            string change;    
            cout << "Nuevo telefono: ";     
            getline(cin, change); 
            c->setTelefono(change);         
            break; 
        }
        case 3: { 
            int change;    
            cout << "Nueva tarjeta: ";      
            cin >> change; 
            c->setTarjeta(change);          
            break; 
        }
        case 4: {
            int change;
            cout << "Cambio edad mayor a 18: ";
            cin  >> change;
            c->setEdad(change);
            break;
        }
        case 5: { 
            string change; 
            cout << "Nueva preferencia: ";  
            getline(cin, change); 
            c->setPreferenciaTrago(change); 
            break; 
        }
    }
    cout << "Cliente actualizado." << endl;
}

// Archivos

/**
 * cargar_bebidas lee el archivo Bebidas.txt y reconstruye todos los
 * objetos del inventario en memoria.
 * 
 * abre el archivo línea por línea e identifica el tipo de bebida para
 * crear el objeto correspondiente con sus atributos propios y agregarlo
 * al vector inventario.
 * 
 * @param
 * @return
 */
void Licoreria::cargar_bebidas() {
    ifstream archivo("Bebidas.txt");
    string line;
    if (!archivo.is_open()) return;

    int n_line = 0;
    while (getline(archivo, line)) {
        n_line++;
        if (line.empty()) continue;
        if (line.back() == '\r') line.pop_back();

        stringstream ss(line);
        string tipo, inven, grad, prec, desc, marca, pais, nombre,  extra1, 
        extra2, extra3;

        getline(ss, tipo, ','); getline(ss, inven, ','); 
        getline(ss, grad, ','); getline(ss, prec, ',');
        getline(ss, desc, ','); getline(ss, marca, ',');
        getline(ss, pais, ','); getline(ss, nombre, ',');

        if (tipo == "Cerveza") {
            getline(ss, extra1, ','); getline(ss, extra2, ',');
            agregar_bebida(new Cerveza(nombre, stoi(inven), stof(grad), 
                stof(prec), stof(desc), marca, pais, nombre, extra1, 
                stof(extra2)));
            }
        if (tipo == "Mezcal") {
            getline(ss, extra1, ','); getline(ss, extra2, ',');
            agregar_bebida(new Mezcal(nombre, stoi(inven), stof(grad), 
                stof(prec), stof(desc), marca, pais, nombre, extra1, 
                stoi(extra2)));
            }
        if (tipo == "Ron") {
            getline(ss, extra1, ','); getline(ss, extra2, ',');
            agregar_bebida(new Ron(nombre, stoi(inven), stof(grad), stof(prec),
                stof(desc), marca, pais, nombre, extra1, stoi(extra2)));
            }
        if (tipo == "Tequila") {
            getline(ss, extra1, ','); getline(ss, extra2, ',');
            getline(ss, extra3, ',');
            agregar_bebida(new Tequila(nombre, stoi(inven), stof(grad), 
                stof(prec), stof(desc), marca, pais, nombre, extra1, extra2, 
                stoi(extra3)));
            }
        if (tipo == "Vino") {
            getline(ss, extra1, ','); getline(ss, extra2, ',');
            agregar_bebida(new Vino(nombre, stoi(inven), stof(grad), 
                stof(prec), stof(desc), marca, pais, nombre, extra1, 
                stoi(extra2)));
            }
        if (tipo == "Vodka") {
            getline(ss, extra1, ','); getline(ss, extra2, ',');
            agregar_bebida(new Vodka(nombre, stoi(inven), stof(grad), 
                stof(prec), stof(desc), marca, pais, nombre, extra1, 
                stoi(extra2)));
            }
        if (tipo == "Whiskey") {
            getline(ss, extra1, ','); getline(ss, extra2, ',');
            agregar_bebida(new Whiskey(nombre, stoi(inven), stof(grad), 
                stof(prec), stof(desc), marca, pais, nombre, stoi(extra1), 
                extra2));
        }
    }
    archivo.close();
}

/**
 * cargar_clientes lee el archivo Clientes.txt y reconstruye todos los
 * objetos de clientes en memoria.
 * 
 * abre el archivo línea por línea y construye un objeto Cliente con el
 * cosntructor de carga, que restaura el id, tragos y cuenta previamente
 * guardados.
 * 
 * @param
 * @return
 */
void Licoreria::cargar_clientes() {
    ifstream archivo("Clientes.txt");
    string line;
    if (!archivo.is_open()) return;
    while (getline(archivo, line)) {
        if (line.empty() || line == "\r") continue;
        stringstream ss(line);
        string nomb, ape, curp, direc, nacion, tarj, tel, edad, pref, id, 
        tragos, cuenta;
        getline(ss, nomb, ','); getline(ss, ape, ',');
        getline(ss, curp, ','); getline(ss, direc, ',');
        getline(ss, nacion, ','); getline(ss, tarj, ','); 
        getline(ss, tel, ','); getline(ss, edad, ',');
        getline(ss, pref, ','); getline(ss, id, ','); 
        getline(ss, tragos, ','); getline(ss, cuenta, ',');
        registrar_cliente(new Cliente(nomb, ape, curp, direc, nacion, 
            stoi(tarj), tel, stoi(edad), pref, stoi(id), stoi(tragos),
            stod(cuenta)));
    }
    archivo.close();
}

/**
 * cargar_empleados lee el archivo Empleados.txt y reconstruye todos los 
 * objetos de empleados en memoria.
 * 
 * abre el archivo línea por línea y construye un objeto Empleado con
 * todos sus atributos personales y laborales.
 * 
 * @param
 * @return
 */
void Licoreria::cargar_empleados() {
    ifstream archivo("Empleados.txt");
    string line;
    if (!archivo.is_open()) return;
    while (getline(archivo, line)) {
        if (line.empty() || line == "\r") continue;
        stringstream ss(line);
        string nomb, ape, curp, direc, nacion, tarj, tel, edad, sueldo,
        horas, puesto;
        getline(ss, nomb, ','); getline(ss, ape, ',');
        getline(ss, curp, ','); getline(ss, direc, ',');
        getline(ss, nacion, ','); getline(ss, tarj, ',');
        getline(ss, tel, ','); getline(ss, edad, ',');
        getline(ss, sueldo, ','); getline(ss, horas, ',');
        getline(ss, puesto, ','); 
        contratar_empleado(new Empleado(nomb, ape, curp, direc, nacion, 
            stoi(tarj), tel, stoi(edad), stod(sueldo), stoi(horas),
            puesto));
        }
    archivo.close();   
}

/**
 * guardar_bebidas escribe el inventario actual en el archivo Bebidas.txt
 * 
 * crea un archivo temporal, serializa cada bebida del vector usando
 * el método de toTexto() y lo escribe línea por línea. Al terminar
 * elimina el archivo original y renombra el temporal para sobreescribirlo.
 * 
 * @param
 * @return
 */
void Licoreria::guardar_bebidas() {
    ifstream entrada("Bebidas.txt");
    ofstream temporal("Bebidas_tmp.txt");
    if (!temporal.is_open()) {
        cout << "Error al guardar bebidas." << endl;
        return;
    }
    for (int i = 0; i < inventario.size(); i++) {
        temporal << inventario[i]->toTexto() << "\n";
    }
    entrada.close();
    temporal.close();
    remove("Bebidas.txt");
    rename("Bebidas_tmp.txt", "Bebidas.txt");
}

/**
 * guarda_clientes escribe el registro acutal de clientes en el archivo
 * Clientes.txt
 * 
 * crea un archivo temporal y serializa cada cliente del vector campo
 * por campo separado por comas. Al terminar elimina el archivo orignal
 * y renombra el temporal para sobreescribirlo.
 * 
 * @param
 * @return
 */
void Licoreria::guardar_clientes() {
    ifstream entrada("Clientes.txt");
    ofstream temporal("Clientes_temp.txt");
    if (!temporal.is_open()) {
        cout << "Error" << endl;
        return;
    }
    for (int i = 0; i < registro_clientes.size(); i++) {
        Cliente* c = registro_clientes[i];
        temporal << c->getNombre() << "," << c->getApellido() << ","
            << c->getCurp() << "," << c->getDireccion() << ","
            << c->getNacionalidad() << "," << c->getTarjeta() << ","
            << c->getTelefono() << "," << c->getEdad() << ","
            << c->getPreferenciaTrago() << "," << c->getCliente() << ","
            << c->getTragos() << "," << c->getCuenta() << endl;
    }
    entrada.close();
    temporal.close();
    remove("Clientes.txt");
    rename("Clientes_temp.txt", "Clientes.txt");
}

/**
 * guardar_empleados escribe la lista actual de empleados en el archivo
 * Empleados.txt.
 * 
 * crea un archivo temporal y serializa cada empleado del vector campo
 * por campo separado por comas. Al terminar elimina el archivo original
 * y renombra el temporal para sobreescribirlo.
 * 
 * @param
 * @return
 */
void Licoreria::guardar_empleados() {
    ifstream entrada("Empleados.txt");
    ofstream temporal("Empleados_temp.txt");
    for (int i = 0; i < lista_empleados.size(); i++) {
        Empleado* e = lista_empleados[i];
        temporal << e->getNombre() << "," << e->getApellido() << ","
            << e->getCurp() << "," << e->getDireccion() << ","
            << e->getNacionalidad() << "," << e->getTarjeta() << ","
            << e->getTelefono() << "," << e->getEdad()   << ","
            << e->getSueldoBase() << "," << e->getHoras() << ","
            << e->getPuesto() << endl;
    }
    entrada.close();
    temporal.close();
    remove("Empleados.txt");
    rename("Empleados_temp.txt", "Empleados.txt");

}

/**
 * guarda_todo agrupa los 3 métodos de guardado en una sola llamada en main.
 * 
 * ejecuta guardar_bebidas(), guardar_clientes y guardar_empleados() en
 * secuencia y confirma en pantalla que los cambios se guardaron.
 * 
 * Se llama desde main al cerrar el programa.
 * 
 * @param
 * @return
 */
void Licoreria::guardar_todo() {
    guardar_bebidas();
    guardar_clientes();
    guardar_empleados();

    cout << "\nCambios guardados con éxito" << endl;
}
#endif