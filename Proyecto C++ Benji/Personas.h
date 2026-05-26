#ifndef PERSONAS_H
#define PERSONAS_H

#include <iostream>
#include <string>
#include <vector>

// 1. Clase Persona
class Persona {
protected:
    string nombre, apellido, curp, direccion, nacionalidad;
    int no_tarjeta, telefono, edad;

public:
    Persona(const string& _nombre, const string& _apellido, 
        const string& _curp, string _direccion, const string& _nacionalidad, 
        int _no_tarjeta, int _telefono, int _edad);
    virtual ~Persona(){}

    string getNombre() {return nombre;}
    string getApellido() {return apellido;}
    string getCurp() {return curp;}
    string getDireccion() {return direccion;}
    string getNacionalidad() {return nacionalidad;}
    int getTarjeta() {return no_tarjeta;}
    int getTelefono() {return telefono;}
    int getEdad() {return edad;}

    void setDireccion(string direction) {direccion = direction;}
    void setTarjeta(int card) {no_tarjeta = card;}
    void setTelefono(int phone) {telefono = phone;}
    void setEdad(int age) { edad = age;}

    virtual void mostrar_info();
};

Persona::Persona(const string& _nombre, const string& _apellido, 
        const string& _curp, string _direccion, const string& _nacionalidad, 
        int _no_tarjeta, int _telefono, int _edad) : nombre(_nombre), 
        apellido(_apellido), curp(_curp), direccion(_direccion),
        nacionalidad(_nacionalidad), no_tarjeta(_no_tarjeta), 
        telefono(_telefono), edad(_edad) {}

void Persona::mostrar_info() {
    cout << "Nombre: " << nombre << " " << apellido << endl;
    cout << "Curp: " << curp << endl;
    cout << "Dirección: " << direccion << endl;
    cout << "Nacionalidad: " << nacionalidad << endl;
    cout << "Tarjeta: " << no_tarjeta << endl;
    cout << "Teléfono: " << telefono << endl;
    cout << "Edad: " << edad << endl;
}

// 2. Cliente
class Cliente: public Persona {
private:
    int id, tragos;
    double cuenta;
    string preferencia_trago;

public:
    Cliente(const string& _nombre, const string& _apellido, 
        const string& _curp, string _direccion, const string& _nacionalidad, 
        int _no_tarjeta, int _telefono, int _edad, 
        const string& _preferencia_trago);

    Cliente(const string& _nombre, const string& _apellido, const string& _curp,
        string _direccion, const string& _nacionalidad, int _tarjeta,
        int _telefono, int _edad, const string& _preferencia, int _id, 
        int _tragos, double _cuenta);
    
    virtual ~Cliente(){}

    int getCliente(){return id;}
    int getTragos(){return tragos;}
    double getCuenta(){return cuenta;}
    string getPreferenciaTrago(){return preferencia_trago;}

    void setTragos(int drinks) {tragos = drinks;}
    void setCuenta(double bill) {cuenta = bill;}
    void setPreferenciaTrago(string beverage_preference) {preferencia_trago = 
        beverage_preference;}

    void registro_consumo(double precio_trago);
    void mostrar_info();
    void pagar_cuenta();
};

Cliente::Cliente(const string& _nombre, const string& _apellido, 
    const string& _curp, string _direccion, const string& _nacionalidad,
    int _tarjeta, int _telefono, int _edad, const string& _preferencia)
    : Persona(_nombre, _apellido, _curp, _direccion, _nacionalidad,
        _tarjeta, _telefono, _edad) {
        preferencia_trago = _preferencia;
        tragos  = 0;
        cuenta  = 0.0;
        id      = 100000 + rand() % 900000;
}

Cliente::Cliente(const string& _nombre, const string& _apellido, 
    const string& _curp, string _direccion, const string& _nacionalidad,
    int _tarjeta, int _telefono, int _edad, const string& _preferencia, 
    int _id, int _tragos, double _cuenta) : Persona(_nombre, _apellido, _curp, 
        _direccion, _nacionalidad, _tarjeta, _telefono, _edad) {
    preferencia_trago = _preferencia;
    id     = _id;
    tragos = _tragos;
    cuenta = _cuenta;
}

void Cliente::registro_consumo(double precio_trago) {
    if (edad < 18){
        cout << "Prohibido la venta a menores" << endl;
        return;
    }
    if (precio_trago > 0){
        tragos++;
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
    cout << "Preferencias de Bebidas " << preferencia_trago << endl;
    cout << "Tragos tomados" << tragos << endl;
}

void Cliente::pagar_cuenta() {
    if(tragos == 0 && cuenta <= 0.0){
        cout << nombre << "No tienes deuda pendiente." << endl;
        return;
    }
    char opcion;
    do{
        cout << "ID cliente: " << id << " Nombre: " << nombre << endl;
        cout << "Tragos Tomados: " << tragos << endl;
        cout << "SUBTOTAL: $" << cuenta << endl;
        cout << "IVA: 16%" << endl;
        cout << "TOTAL: $" << (cuenta * 1.16) << endl;
        cout << "¿Desea pagar? (s/n): ";
        cin >> opcion;
        if (opcion == 's' || opcion == 'S') {
            cout << "Pago realizado." << endl;
            tragos = 0.0;
            cuenta = 0.0;
            cout << "Muchas gracias por su compra " << nombre << endl;
        } else {
            cout << "No se registró bien su respuesta" << endl;
        }
    } while (opcion != 's' && opcion != 'S');
}

// 3. Empleado
class Empleado: public Persona {
private:
    private:
    double sueldo_base;
    int horas_trabajo; 
    string puesto;

public:
    Empleado(const string& _nombre, const string& _apellido, 
    const string& _curp, string _direccion, const string& _nacionalidad, 
    int _tarjeta, int _telefono, int _edad, double _sueldo, int _horas_trabajo, 
    string _puesto);

    virtual ~Empleado(){}

    double getSueldoBase() {return sueldo_base;}
    int getHoras() {return horas_trabajo;}
    string getPuesto() {return puesto;}

    void setSueldoBase(double salary) {sueldo_base = salary;}
    void setHorasTrabajo(int hours) {horas_trabajo = hours;}
    void setPuesto(string position) {puesto = position;}

    double calculo_nomina();
    void mostrar_info();
};

Empleado::Empleado(const string& _nombre, const string& _apellido, 
        const string& _curp, string _direccion,  const string& _nacionalidad, 
        int _tarjeta, int _telefono, int _edad, double _sueldo, 
        int _horas_trabajo, string _puesto) : Persona(_nombre, _apellido, 
            _curp, _direccion, _nacionalidad, _tarjeta, _telefono, _edad) {
    sueldo_base        = _sueldo;
    horas_trabajo      = _horas_trabajo;
    puesto             = _puesto;
}

double Empleado::calculo_nomina() {return sueldo_base * horas_trabajo;}

void Empleado::mostrar_info() {
    Persona::mostrar_info();
    cout << "Puesto: " << puesto << endl;
    cout << "Sueldo: $" << sueldo_base << endl;
    cout << "Horas: " << horas_trabajo << endl;
    cout << "Nómina: $" << calculo_nomina() << endl; 
}

#endif
