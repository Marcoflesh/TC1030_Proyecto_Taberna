#ifndef LICORERIA_H
#define LICORERIA_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Bebidas.h"
#include "Personas.h"

using namespace std;

class Licoreria {
private:
    string nombre;
    vector <Bebida*> inventario;
    vector <Empleado*> lista_empleados;
    vector <Cliente*> registro_clientes;

public:
    Licoreria(string _nombre);
    virtual ~Licoreria();

    string getNombre() {return nombre;}

    void agregar_bebida(Bebida* b) {inventario.push_back(b);}
    void contratar_empleado(Empleado* e) {lista_empleados.push_back(e);}
    void registrar_cliente(Cliente* c) {registro_clientes.push_back(c);}

    Bebida* getBebida(int i) {return inventario[i];}
    Empleado* getEmpleado(int i) {return lista_empleados[i];}
    Cliente* getClientes(int id) {
        for(int i = 0; i < registro_clientes.size(); i++) {
            if (registro_clientes[i]->getCliente() == id) {
                return registro_clientes[i]; 
            }
        }
        return nullptr;
    }
    int total_bebidas() {return inventario.size();}
    int total_empleados() {return lista_empleados.size();}
    int total_clientes() {return registro_clientes.size();}

    // inventario
    void vender_trago(int index, Cliente* c);
    void mostrar_inventario();
    void mostrar_info_bebida(int index);
    void ajustar_inventario(int index, int cantidad);
    void eliminar_bebida(int index);
    
    // Empleados
    void mostrar_empleado();
    void mostrar_info_empleado(int index);
    void contratar();
    void editar_empleado(int index);

    // Clientes
    void mostrar_cliente();
    void mostrar_info_cliente(int id);
    void registrar_new_cliente();
    void editar_cliente(int id); 

    //archivos
    void cargar_bebidas();
    void cargar_clientes();
    void cargar_empleados();
    void guardar_bebidas();
    void guardar_clientes(); 
    void guardar_empleados();
    void guardar_todo(); 

};

Licoreria::Licoreria(string _nombre) {nombre = _nombre;}

// Inventario
Licoreria::~Licoreria() {
    for (int i = 0; i < inventario.size(); i++) 
        delete inventario[i];
    for (int i = 0; i < lista_empleados.size(); i++) 
        delete lista_empleados[i];
    for (int i = 0; i < registro_clientes.size(); i++) 
        delete registro_clientes[i];
}

void Licoreria::vender_trago(int index, Cliente* c) {
    if (index >= 0 && index < inventario.size()) {
        if (inventario[index]->getStock() > 0) {
            inventario[index]->servir();
            float precio = inventario[index]->getPrecio();
            inventario[index]->restarStock(1);
            c->registro_consumo(precio);
            cout << "Consumiste " << inventario[index]->getNombre() << endl;
            } else {
            cout << "Una disculpa, ya no queda " 
                << inventario[index]->getNombre() << " en stock." << endl;
        }
    } else {
        cout << "Numero de bebida no valido." << endl;
    }
}

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

void Licoreria::mostrar_info_bebida(int index) {
    if (index >= 0 && index < inventario.size()) {
        cout << inventario[index]->toString() << endl;
    } else {
        cout << "Numero de bebida no valido." << endl;
    }
}

void Licoreria::ajustar_inventario(int index, int cantidad) {
    if(index >= 0 && index < inventario.size()) {
        if (cantidad > 0) {
            inventario[index]->sumarStock(cantidad);
            cout << "Se agregaron " << cantidad << " botellas de: "
                << inventario[index]->getNombre() << endl;
        }else if (cantidad < 0) {
            inventario[index]->restarStock((cantidad));
            cout << "Se quitaron " << cantidad << " botellas de: "
                << inventario[index]->getNombre() << endl;
            }
        }else {
            cout << "Bebida no válida" << endl;
    }
}

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
void Licoreria::mostrar_empleado() {
    cout << "Empleados" << endl;
    for (int i = 0; i < lista_empleados.size(); i++) {
        cout << i << " " << lista_empleados[i]->getNombre() << " "
        << lista_empleados[i]->getApellido() << ", " 
        << lista_empleados[i]->getPuesto() << endl;
    }
}

void Licoreria::mostrar_info_empleado(int index) {
    if (index >= 0 && index < lista_empleados.size()) {
        lista_empleados[index]->mostrar_info();
    } else {
        cout << "Empleado no reconocido" << endl;
    }
}

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
void Licoreria::mostrar_cliente() {
    cout << "Lista Clientes" << endl;
    cout << "\n";
    for (int i = 0; i < registro_clientes.size(); i++) {
        cout << i << " " << registro_clientes[i]->getNombre() << " "
        << registro_clientes[i]->getApellido() << " ID: "
        << registro_clientes[i]->getCliente() << endl;
    }
}

void Licoreria::mostrar_info_cliente(int id) {
    Cliente* cliente = getClientes(id);

    if (cliente != nullptr) {
        cliente->mostrar_info();
    } else {
        cout << "ID invalido" << endl;
    }
}

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

void Licoreria::guardar_todo() {
    guardar_bebidas();
    guardar_clientes();
    guardar_empleados();

    cout << "\nCambios guardados con éxito" << endl;
}
#endif