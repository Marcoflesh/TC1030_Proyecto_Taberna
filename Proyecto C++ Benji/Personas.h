/*
 * Proyecto Licorería Clase Persona, Cliente y Empleado
 * Marco Antonio Hernández Roque
 * A01709802
 * 12/06/2026
 * Materia: TC1030 Programación Orientada a Objetos
 * * En este archivo se creó la clase base Persona y sus dos hijas: Cliente y Empleado. 
 * Sirve para guardar los datos básicos de cualquier persona involucrada en el 
 * negocio y manejar cosas específicas como las cuentas de consumo o las nóminas.
 */

#ifndef PERSONAS_H
#define PERSONAS_H

#include <iostream>
#include <string>

/**
 * Persona es la clase padre. Guarda los datos que todos comparten (nombre, 
 * edad, teléfono, dirección, etc.) para no tener que repetir código después.
 */
class Persona {
    // atributos
protected: // Declaro protegido para que se pueda acceder en las hijas
    string nombre, apellido, curp, direccion, nacionalidad, telefono;
    int no_tarjeta, edad;

    // metodos
public:
    // Constructor
    Persona(const string& _nombre, const string& _apellido, 
        const string& _curp, string _direccion, const string& _nacionalidad, 
        int _no_tarjeta, string _telefono, int _edad);
    
    // Método Destructor
    virtual ~Persona(){}

    // Getters y setters
    string getNombre();
    string getApellido();
    string getCurp();
    string getDireccion();
    string getNacionalidad();
    int getTarjeta();
    string getTelefono();
    int getEdad();
    void setDireccion(string direction);
    void setTarjeta(int card);
    void setTelefono(string phone);
    void setEdad(int age);

    virtual void mostrar_info(); // imprime en la pantalla datos personales
};

Persona::Persona(const string& _nombre, const string& _apellido, 
        const string& _curp, string _direccion, const string& _nacionalidad, 
        int _no_tarjeta, string _telefono, int _edad) : nombre(_nombre), 
        apellido(_apellido), curp(_curp), direccion(_direccion),
        nacionalidad(_nacionalidad), no_tarjeta(_no_tarjeta), 
        telefono(_telefono), edad(_edad) {}

string Persona::getNombre() {return nombre;}
string Persona::getApellido() {return apellido;}
string Persona::getCurp() {return curp;}
string Persona::getDireccion() {return direccion;}
string Persona::getNacionalidad() {return nacionalidad;}
int Persona::getTarjeta() {return no_tarjeta;}
string Persona::getTelefono() {return telefono;}
int Persona::getEdad() {return edad;}

void Persona::setDireccion(string direction) {direccion = direction;}
void Persona::setTarjeta(int card) {no_tarjeta = card;}
void Persona::setTelefono(string phone) {telefono = phone;}
void Persona::setEdad(int age) {edad = age;}

void Persona::mostrar_info() {
    cout << "Nombre: " << nombre << " " << apellido << endl;
    cout << "Curp: " << curp << endl;
    cout << "Dirección: " << direccion << endl;
    cout << "Nacionalidad: " << nacionalidad << endl;
    cout << "Tarjeta: " << no_tarjeta << endl;
    cout << "Teléfono: " << telefono << endl;
    cout << "Edad: " << edad << endl;
}

/**
 * Cliente hereda de Persona. Además de sus datos personales, le añade un ID, 
 * cuántos tragos lleva y una cuenta de dinero para saber cuánto debe pagar.
 */
class Cliente: public Persona {
private:
    int id, tragos;
    double cuenta;
    string preferencia_trago;

public:
    // Constructor hecho para las funciones del programa en terminal
    Cliente(const string& _nombre, const string& _apellido, 
        const string& _curp, string _direccion, const string& _nacionalidad, 
        int _no_tarjeta, string _telefono, int _edad, 
        const string& _preferencia_trago);

    // Constructor para poder guardar los datos en los archivos .txt
    Cliente(const string& _nombre, const string& _apellido, const string& _curp,
        string _direccion, const string& _nacionalidad, int _tarjeta,
        string _telefono, int _edad, const string& _preferencia, int _id, 
        int _tragos, double _cuenta);
    
    // Método destructor
    virtual ~Cliente(){}

    // Getters y Setters
    int getCliente();
    int getTragos();
    double getCuenta();
    string getPreferenciaTrago();
    void setTragos(int drinks);
    void setCuenta(double bill);
    void setPreferenciaTrago(string preference);

    // suma el precio de la bebida a la cuenta total
    void registro_consumo(double precio_trago, int cantidad); 
    // sobreescribe el método de Persona para aplicar polimorfismo
    void mostrar_info(); 
    // Avisa al cliente cuánto debe, regresa cuenta y tragos en 0
    void pagar_cuenta(); 
};

Cliente::Cliente(const string& _nombre, const string& _apellido, 
    const string& _curp, string _direccion, const string& _nacionalidad,
    int _tarjeta, string _telefono, int _edad, const string& _preferencia)
    : Persona(_nombre, _apellido, _curp, _direccion, _nacionalidad,
        _tarjeta, _telefono, _edad) {
        preferencia_trago = _preferencia;
        tragos  = 0;
        cuenta  = 0.0;
        id      = 100000 + rand() % 900000;
}

Cliente::Cliente(const string& _nombre, const string& _apellido, 
    const string& _curp, string _direccion, const string& _nacionalidad,
    int _tarjeta, string _telefono, int _edad, const string& _preferencia, 
    int _id, int _tragos, double _cuenta) : Persona(_nombre, _apellido, _curp, 
        _direccion, _nacionalidad, _tarjeta, _telefono, _edad) {
    preferencia_trago = _preferencia;
    id     = _id;
    tragos = _tragos;
    cuenta = _cuenta;
}

int Cliente::getCliente() {return id;}
int Cliente::getTragos() {return tragos;}
double Cliente::getCuenta() {return cuenta;}
string Cliente::getPreferenciaTrago() {return preferencia_trago;}

void Cliente::setCuenta(double bill) {cuenta = bill;}
void Cliente::setTragos(int drinks) {tragos = drinks;}
void Cliente::setPreferenciaTrago(string preference) {preferencia_trago 
    = preference;}

void Cliente::registro_consumo(double precio_trago, int cantidad) {
    if (edad < 18){
        cout << "Prohibido la venta a menores" << endl;
        return;
    }
    if (precio_trago > 0){
        tragos += cantidad;
        cuenta += precio_trago;
        cout << nombre << " LLevas # " << tragos << endl;
        cout << "Precio Bebida: $" << precio_trago << endl;
        cout << "Subtotal: $" << cuenta << endl;
    }
}

void Cliente::mostrar_info() {
    cout << "Detalles del cliente" << endl;
    Persona::mostrar_info();
    cout << "Id " << id << endl;
    cout << "Preferencia de Bebida: " << preferencia_trago << endl;
    cout << "Tragos tomados: " << tragos << endl;
    cout << "Cuenta: $" << cuenta << endl;
}

void Cliente::pagar_cuenta() {
    if(tragos == 0 && cuenta <= 0.0){
        cout << nombre << ", No tienes deuda pendiente." << endl;
        return;
    }
    char opcion;
    do{
        cout << "\nID cliente: " << id << endl;
        cout << "Nombre: " << nombre << " " << apellido << endl;
        cout << "Tragos Tomados: " << tragos << endl;
        cout << "SUBTOTAL: $" << cuenta << endl;
        cout << "IVA: 16%" << endl;
        cout << "TOTAL: $" << (cuenta * 1.16) << endl;
        cout << "¿Desea pagar? (s/n): ";
        cin >> opcion;
        if (opcion == 's' || opcion == 'S') {
            cout << "\nPago realizado." << endl;
            tragos = 0.0;
            cuenta = 0.0;
            cout << "\nMuchas gracias por su compra " << nombre << endl;
        } else {
            cout << "\nNo se registró bien su respuesta" << endl;
        }
    } while (opcion != 's' && opcion != 'S');
}

/**
 * Empleado hereda de Persona. Le agrega atributos de trabajo como 
 * su sueldo base, las horas que trabaja y su puesto en la licorería.
 */
class Empleado: public Persona {
private:
    private:
    double sueldo_base;
    int horas_trabajo; 
    string puesto;

public:
    // Método Constructor
    Empleado(const string& _nombre, const string& _apellido, 
    const string& _curp, string _direccion, const string& _nacionalidad, 
    int _tarjeta, string _telefono, int _edad, double _sueldo, int _horas_trabajo, 
    string _puesto);

    // Método Destructor
    virtual ~Empleado(){}

    // Getters y Setters
    double getSueldoBase();
    int getHoras();
    string getPuesto();

    void setSueldoBase(double salary);
    void setHorasTrabajo(int hours);
    void setPuesto(string position);

    // Calcula el dinero total que se le va a pagar el empleado
    double calculo_nomina();
    // Método que sobreescribe para mostrar información del empleado
    void mostrar_info();
};

Empleado::Empleado(const string& _nombre, const string& _apellido, 
        const string& _curp, string _direccion,  const string& _nacionalidad, 
        int _tarjeta, string _telefono, int _edad, double _sueldo, 
        int _horas_trabajo, string _puesto) : Persona(_nombre, _apellido, 
            _curp, _direccion, _nacionalidad, _tarjeta, _telefono, _edad) {
    sueldo_base        = _sueldo;
    horas_trabajo      = _horas_trabajo;
    puesto             = _puesto;
}

double Empleado::getSueldoBase() {return sueldo_base;}
int Empleado::getHoras() {return horas_trabajo;}
string Empleado::getPuesto() {return puesto;}

void Empleado::setSueldoBase(double salary) {sueldo_base = salary;}
void Empleado::setHorasTrabajo(int hours) {horas_trabajo = hours;}
void Empleado::setPuesto(string position) {puesto = position;}

double Empleado::calculo_nomina() {return sueldo_base * horas_trabajo;}

void Empleado::mostrar_info() {
    Persona::mostrar_info();
    cout << "Puesto: " << puesto << endl;
    cout << "Sueldo: $" << sueldo_base << endl;
    cout << "Horas: " << horas_trabajo << endl;
    cout << "Nómina: $" << calculo_nomina() << endl; 
}

#endif