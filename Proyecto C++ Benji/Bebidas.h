/*
 * Proyecto Licorería Clase Bebida y sus variedades
 * Marco Antonio Hernández Roque
 * A01709802
 * 12/06/2026
 * Materia: TC1030 Programación Orientada a Objetos
 * Este archivo define la clase abstracta Bebida y todos los tipos de alcohol 
 * que se vende en el local. Aquí se controla el inventario, los precios 
 *  base y la lógica de descuentos, que cada subclase sobreescribe según
 * sus reglas.
 */

#ifndef BEBIDAS_H
#define BEBIDAS_H

#include <string>
#include <iostream>

using namespace std;

/**
 * Bebida es la clase abstracta base para todas las bebidas del inventario.
 * Guarda los datos que todas comparten como nombre, marca, precio, etc.
 * Declara métodos abstractos servir() y toTexto() que cada subclase debe
 * implementar obligatoriamente, y provee implementaciones por defecto para
 * descontar() y toString().
 */
class Bebida {
protected: // declaro protegido para que se pueda acceder en las hijas
    int stock;
    float porcentaje, precio, descuento;
    string nombre, marca, pais, tipo_bebida;

public:
    // Constructor
    Bebida(string _tipo_bebida, int _stock, float _porcentaje, float _precio, 
        float _descuento, const string& _marca, const string& _pais, 
        const string& _nombre);
    
    // Destructor
    virtual ~Bebida(){}

    // Getters
    int getStock();
    float getGrados();
    float getPrecio();
    float getDescuento();
    string getNombre();
    string getMarca();
    string getPais();
    string getTipoBebida();

    // Suman o restan bebidas del inventario
    void sumarStock(int cantidad);
    void restarStock(int loot);

    // Aplica el descuento dando un total o una cantidad de bebidas
    virtual float descontar(float total); 
    virtual float descontar(int cantidad);

    virtual void servir() = 0; 
    virtual string toString();
    virtual string toTexto() = 0;
};

Bebida::Bebida(string _tipo_bebida, int _stock, float _porc, float _precio, 
        float _desc, const string& _marca, const string& _pais, 
        const string& _nombre) : tipo_bebida(_tipo_bebida), stock(_stock), 
        porcentaje(_porc), precio(_precio), descuento(_desc), marca(_marca), 
        pais(_pais), nombre(_nombre) {}

int Bebida::getStock() {return stock;}
float Bebida::getGrados() {return porcentaje;}
float Bebida::getPrecio() {return precio;}
float Bebida::getDescuento() {return descuento;}
string Bebida::getNombre() {return nombre;}
string Bebida::getMarca() {return marca;}
string Bebida::getPais() {return pais;}
string Bebida::getTipoBebida() {return tipo_bebida;}

/**
 * SumarStock incrementa la cantidad disponible de una bebida en inventario.
 * 
 * Recibe la cantidad de unidades a agregar y la suma directamente al 
 * atributo de stock de la bebida seleccionada.
 * 
 * @param int cantidad número de unidades a agregar al inventario
 * @return
 */
void Bebida::sumarStock(int cantidad) {stock += cantidad;}

/**
 * restarStock reduce la cantidad disponible de una bebida en inventario.
 * 
 * Utiliza el valor absoluto de la cantidad recibida para evitar que un
 * número negativo genere una resta incorrecta y la suma al stock.
 * 
 * @param int cantidad número de unidades a returar del inventario.
 * @return
 */
void Bebida::restarStock(int cantidad) {stock -= abs(cantidad);}

/**
 * descontar aplica el porcentaje de descuento a un total dado.
 * 
 * Recibe el precio total de una compra, le resta el descuento proporcional
 * e imprime en panatalla el porcentaje aplicado y el nuevo precio
 * resultante. 
 * 
 * @param float total precio acumulado antes de aplicar el descuento.
 * @return float con el precio final ya con el descuento aplicado. 
 */
float Bebida::descontar(float total) {
    float descontado = total - (total * descuento);
    cout << "Se aplico un descuento a " << nombre << " del "
         << (descuento * 100) << "%, nuevo precio: $" << descontado << endl;
    return descontado;
}

/**
 * descontar calcula el precio de una cantidad de unidades con descuento.
 * 
 * Valida que la cantidad sea positiva, multiplica el precio unitario por
 * la cantidad y manda el cálculo del descuento a la versión de descontar()
 * que recibe un total en float. 
 * 
 * @param int cantidad número de unidades que el cliente desea comprar.
 * @return float con el precio final de la compra ya con el descuento
 * aplicado.
 */
float Bebida::descontar(int cantidad) {
    if (cantidad <= 0) {
        cout << "Cantidad invalida." << endl;
        return 0.0;
    }
    float total = precio * cantidad;
    cout << "Tomaste " << cantidad << " de " << nombre << endl;
    return descontar(total);
}

/**
 * toString convierte los atributos base de la bebida a un string legible.
 * 
 * Concatena nombre, marca, país, porcentaje alcohol, precio y descuento
 * en un solo string con formato de varias líeans para mostrarlo en consola.
 * Las subclases pueden extenderlo llamando a Bebida::toString() y 
 * añadiendo sus atributos propios al final.
 * 
 * @param
 * @return string con los atributos base de la bebida concatenados.
 */
string Bebida::toString() {
    string texto = "Bebida: " + nombre + "\nMarca: " + marca + "\nPais: " 
        + pais + "\nPorcentaje de alcohol: " + to_string(porcentaje) + "%"
        + "\nPrecio: $" + to_string(precio) + "\nCon descuento de: " 
        + to_string(descuento * 100) + "%";
    return texto;
}

/**
 * Cerveza hereda de Bebida y agrega el estilo y el IBU (amargor).
 * Su política de descontar se activa únicamente cuando el cliente compra
 * 5 o más unidades.
 */
class Cerveza : public Bebida {
private:
    string tipo;
    float ibu; 

public:
    // Constructor
    Cerveza(string _tipo_bebida, int _stock, float _porcentaje, float _precio, 
        float _descuento, const string& _marca, const string& _pais, 
        const string& _nombre, const string& _tipo, float _ibu);
    
    // Destructor
    virtual ~Cerveza(){}
    
    // Getters
    string getTipo();
    float getIbu();

    void servir();
    string toString();
    float descontar(int cantidad);
    string toTexto();
};

Cerveza::Cerveza(string _tipo_bebida, int _stock, float _porcentaje, 
    float _precio, float _descuento, const string& _marca, const string& _pais,
    const string& _nombre, const string& _tipo, float _ibu) : 
    Bebida(_tipo_bebida, _stock, _porcentaje, _precio, _descuento, _marca, 
        _pais, _nombre) {
            tipo = _tipo;
            ibu = _ibu;
        }

string Cerveza::getTipo() {return tipo;}
float Cerveza::getIbu() {return ibu;}

/**
 * servir imprime en pantalla el mensaje al entregar una cerveza al cliente.
 * 
 * Muestra el nombre de la cerveza y su estilo para darle contexto al cliente
 * sobre lo que está consumiendo
 * 
 * @param
 * @return
 */
void Cerveza::servir() {
    cout << "Sirviendo una " << nombre << " tipo " << tipo << "." << endl;
}

/**
 * descontar aplica la política de descuento por volumen para cervezas.
 * 
 * Si el cliente compra menos de 5 unidades no hay descuento. A partir de 
 * 5 unidades se aplica automáticamente un 20% de descuento. Luego manda
 * el cálculo final a Bebida::descontar(int).
 * 
 * @param int cantidad número de cervezas que el cliente desea comprar.
 * @return float con el precio final de la compra ya con el descuento
 * aplicado.
 */
float Cerveza::descontar(int cantidad) {
    if (cantidad < 5) {
        descuento = 0.0;
        cout << "No hay descuentos disponibles" << endl;
    } else {
        descuento = 0.2;
        cout << "Tienes un 20% de descuento" << endl;
    }
    return Bebida::descontar(cantidad);
}

/**
 * toString extiende el método de Bebida añadiendo el estilo y el IBU.
 * 
 * Llama a Bebida::toString() para obtener los datos base y concatena al 
 * final el tipo de cerveza y su nivel de amargor en IBU.
 * 
 * @param
 * @return string con todos los atributos de la cerveza concatenados.
 */
string Cerveza::toString() {
    return Bebida::toString() + "\nTip: " + tipo + "\nIBU (amargor): "
        + to_string(ibu) + "%";
}

/**
 * toTexto serializa los atributos de la cerveza en formato CSV.
 * 
 * Genera una línea de texto con todos los campos separados por comas para
 * ser escrita en el archivo Bebidas.txt y poder reconstruir el objeto al
 * leer el archivo con cargar_bebidas() de la clase Licoreria.
 * 
 * @param
 * @return string con los atributos de la cerveza en formato CSV.
 */
string Cerveza::toTexto() {
    string texto;
    texto = "Cerveza," + to_string(stock) + "," + to_string(porcentaje)
        + "," + to_string(precio) + "," + to_string(descuento)
        + "," + marca + "," + pais + "," + nombre
        + "," + tipo + "," + to_string(ibu);
        return texto;
}

/**
 * Mezcal hereda de Bebida y tiene atributos propios como tipo de agave
 * y si trae gusano la botella o no. Los mezcales de agaves silvestres
 * (Tobalá, Tepeztate y Jabalí) están exentos de cualquier descuento. 
 */
class Mezcal : public Bebida {
private:
    string tipo_agave;
    bool gusano; // si trae gusano es true, sino es false

public:
    // Constructor
    Mezcal(string _tipo_bebida, int _stock, float _porcentaje, float _precio, 
        float _descuento, const string& _marca, const string& _pais, 
        const string& _nombre, const string& _tipo_agave, bool _gusano);
    
    // Destructor
    virtual ~Mezcal(){}

    // Getters
    string getTipoAgave();
    bool getGusano();

    void servir();
    string toString();
    float descontar(int cantidad);
    string toTexto();
};

Mezcal::Mezcal(string _tipo_bebida, int _stock, float _porcentaje, 
    float _precio, float _descuento, const string& _marca, const string& _pais, 
    const string& _nombre, const string& _agave, bool _gusano) 
        : Bebida(_tipo_bebida, _stock, _porcentaje, _precio, _descuento, 
            _marca, _pais, _nombre)
        {
        tipo_agave = _agave;
        gusano = _gusano;
    }

string Mezcal::getTipoAgave() {return tipo_agave;}
bool Mezcal::getGusano() {return gusano;}

/**
 * servir imprime en pantalla el mensaje al entregar un mezcal al cliente.
 * 
 * Muestra el nombre del mezcal y el tipo de agave con el que fue elaborado.
 * Si la botella trae gusano de maguey, también lo comunica al cliente.
 * 
 * @param
 * @return
 */
void Mezcal::servir() {
    cout << "Aqui tienes un " << nombre << " de agave " << tipo_agave 
    << "." << endl;
    if (gusano) {
        cout << "Este mezcal trae gusano de maguey." << endl;
    }   
}

/**
 * descontar aplica la política de descuento por volumen para mezcales.
 * 
 * Los mezcales de agave silvestre(Tobalá, Tepeztate y Jabalí) no entran
 * dentro del descuento. Para el resto, si el cliente compra más de 7
 * unidades se aplica el 15% de descuento automáticamente, luego manda el 
 * cálculo final a Bebida::descontar(int).
 * 
 * @param int cantidad número de botellas que el cliente desea comprar.
 * @return float con el precio final de la compra ya con el descuento
 * aplicado.
 */
float Mezcal::descontar(int cantidad) {
    float total = precio * cantidad;
    if (tipo_agave == "Tabala" || tipo_agave == "Tepeztate" 
        || tipo_agave == "Jabali") {
        cout << "No hay descuentos para esta bebida" << endl;
        cout << "Total: $" << total << endl;
        return total;
    }
    if (cantidad > 7) {
        descuento = 0.15;
        cout << "Descuento del 15% aplicado." << endl;
    }
    return Bebida::descontar(cantidad);
}

/**
 * toString extiende el toString de Bebida añadiendo el tipo de agave y 
 * el gusano.
 * 
 * Llama a Bebida::toString() para obtener los datos base y concatena al 
 * final el tipo de agave y si la botella trae o no gusano de maguey.
 * 
 * @param
 * @return string con todos los atributos del mezcal concatenados.
 */
string Mezcal::toString() {
    string texto, g = gusano ? "con gusano" : "sin gusano";
    texto = Bebida::toString() + "\nAgave: " + tipo_agave + "\n" + g;
    return texto; 
}

/**
 * toTexto serializa los atributos del mezcal en formato CSV.
 * 
 * Genera una línea de texto con todos los campos separados por comas para
 * ser escrita en el archivo Bebidas.txt y poder reconstruir el objeto al 
 * leer el archivo con cargar_bebidas() de la clase Licoreria.
 * 
 * @param 
 * @return string con los atributos del mezcal en formato CSV.
 */
string Mezcal::toTexto() {
    string texto;
    texto = "Mezcal," + to_string(stock) + "," + to_string(porcentaje)
        + "," + to_string(precio) + "," + to_string(descuento) + "," + marca 
        + "," + pais + "," + nombre + "," + tipo_agave + "," + 
        to_string(gusano);
    return texto;
}

/**
 * Ron hereda de Bebida y agrega métodos como estilo y un booleano que 
 * indica si es especiado o no. Los rones premium como Añejo y Gran Reserva
 * no son aplicables para un descuento; el resto hereda la lógica de Bebida.
 */
class Ron : public Bebida {
private:
    string estilo;
    bool especias;

public:
    // Constructor
    Ron(string _tipo_bebida, int _stock, float _porcentaje, float _precio, 
        float _descuento, const string& _marca, const string& _pais, 
        const string& _nombre, const string& _estilo, bool _especias);

    // Destructor
    virtual ~Ron(){}

    // Getters
    string getEstilo();
    bool getEspecias();

    void servir(); // da sugerencias segun el estilo de ron
    string toString();
    float descontar(int cantidad);
    string toTexto();
};

Ron::Ron(string _tipo_bebida, int _stock, float _porcentaje, float _precio, 
        float _descuento, const string& _marca, const string& _pais, 
        const string& _nombre, const string& _estilo, bool _especias) :
        Bebida(_tipo_bebida, _stock, _porcentaje, _precio, _descuento, _marca, 
            _pais, _nombre) {
            estilo = _estilo;
            especias = _especias;
        }

string Ron::getEstilo() {return estilo;}
bool Ron::getEspecias() {return especias;}

/**
 * servir imprime en pantalla una sugerencia de consumo dependiendo el Ron
 * que el usuario haya escogido.
 * 
 * Si el ron es especiado, recomienda tomarlo en cuba. Si es puro, adapta
 * la sugerencia según el estilo, blanco en mojito, añejo o gran reserva
 * solo con hielo, y cualquier otro con jugo de fruta.
 * 
 * @param
 * @return
 */
void Ron::servir() {
        cout << "Aquí tienes un buen " << nombre << " " << estilo << endl;
    if (especias){
        cout << "Tómatelo en una cuba" << endl;
    } else {
        if (estilo == "Blanco") {
            cout << "Tómatelo en un mojito" << endl;
        } else if (estilo == "Añejo" || estilo == "Gran Reserva") {
            cout << "Tómalo solo con hielo" << endl;
        } else {
            cout << "Tómalo con jugo de cualquier fruta" << endl;
        }
    }
}

/**
 * toString extiende el toString de Bebida añadiendo el estilo y si es 
 * especiado.
 * 
 * Llama a Bebida::toString() para obtener los datos base y concatena al
 * final el estilo del ron y si es especiado o puro.
 * 
 * @param
 * @return string con todos los atributos de ron concatenados.
 */
string Ron::toString() {
    string especiado = especias ? "especiado" : "puro", texto;
    texto = Bebida::toString() + "\nEstilo de ron: " + estilo + "\nTipo: " 
    + especiado;
    return texto;
}

/**
 * descontar aplica la política de descuento para rones.
 * 
 * Los rones añejos premium no son elegibles para un descuento. Para el 
 * resto de los estilos manda el cálculo directamente a 
 * Bebida::descontar(int).
 * 
 * @param int cantidad número de botellas que el cliente desea comprar.
 * @return float con el precio final de la compra ya con el desucuento
 * aplicado.
 */
float Ron::descontar(int cantidad) {
    if (estilo == "Añejo" || estilo == "Gran Reserva") {
        float total = precio * cantidad;
        cout << "Este ron " << estilo << " al ser premium no aplica descuentos" 
        << endl;
        cout << "Tienes que pagar $" << total << endl;
        return total;
    }
    return Bebida::descontar(cantidad);
}

/**
 * toTexto serializa los atributos del ron en formato CSV.
 * 
 * Genera una línea de texto con todos los campos separados por comas para
 * ser escrita en el archivo Bebidas.txt y poder reconstruir el objeto 
 * al leer el archivo con cargar_bebidas() en la clase de Licoreria.
 * 
 * @param
 * @return string con los atributos del ron en formato CSV.
 */
string Ron::toTexto() {
    string texto;
    texto = "Ron," + to_string(stock) + "," + to_string(porcentaje)
        + "," + to_string(precio) + "," + to_string(descuento) + "," + marca 
        + "," + pais + "," + nombre + "," + estilo + "," + to_string(especias);
    return texto;
}

/**
 * Tequila hereda de Bebida y tiene como atributos la región de origen
 * la categoría y si es 100% de agave o es tequila mixto.
 * Solo los tequilas mixtos y en compras mayores a 7 unidades, son 
 * elegibles para un descuento.
 */
class Tequila : public Bebida {
private:
    string region, categoria;
    bool agave;

public:
    // Constructor
    Tequila(string _tipo_bebida, int _stock, float _porcentaje, float _precio, 
        float _descuento, const string& _marca, const string& _pais, 
        const string& _nombre, const string& _region, const string& _categoria, 
        bool _agave);
    
    // Destructor
    virtual ~Tequila(){}
    
    // Getters
    string getRegion();
    string getCategoria();
    bool isAgave();

    void servir();
    string toString(); 
    float descontar(int cantidad);
    string toTexto();
};

Tequila::Tequila(string _tipo_bebida, int _stock, float _porcentaje, 
        float _precio, float _descuento, const string& _marca, 
        const string& _pais, const string& _nombre, const string& _region, 
        const string& _categoria, bool _agave) 
        : Bebida(_tipo_bebida, _stock, _porcentaje, _precio, _descuento, 
            _marca, _pais, _nombre) {
            region = _region;
            categoria = _categoria;
            agave = _agave; 
        }

string Tequila::getRegion() {return region;}
string Tequila::getCategoria() {return categoria;}
bool Tequila::isAgave() {return agave;}

/**
 * servir imprime en pantalla una sugerencia de consumo para el tequila.
 * 
 * Muestra la categoría y la región de origen del tequila. Si es Blanco
 * recomienda tomarlo en seco; para cualquier otra categoría sugiere
 * tomarlo a tragos.
 * 
 * @param
 * @return
 */
void Tequila::servir() {
    cout << "Estas tomando tequila " << categoria <<  " de " << region << endl;
    if (categoria == "Blanco") {
        cout << "Tómalo en seco" << endl;
    } else {
        cout << "Tómalo a tragos para un mejor disfrute" << endl;
    }
}

/**
 * toString extiende el toString de Bebida añadiendo región, categoría y 
 * pureza.
 * 
 * Llama a Bebida::toString() para obtener los datos base y concatena al
 * final la región de origen, la categoría del tequila y si es 100% agave
 * o mixto. 
 * 
 * @param 
 * @return string con todos los atributos del tequila concatenados.
 */
string Tequila::toString() {
    string pureza = agave ? "100% agave" : "mixto", texto;
    texto = Bebida::toString() + "\nRegion: " + region + "\nCategoria: " 
    + categoria + "\nHecho con agave: " + pureza; 
    return texto;
}

/**
 * Los tequilas 100% de agave no son elegibles para un descuento. Para 
 * los tequilas mixtos, el descuento se aplica solo si el cliente compra
 * más de 7 unidades se manda el cálculo a Bebida::descontar(int).
 * 
 * @param int cantidad número de botellas que el cliente desea comprar.
 * @return float con el precio final de la compra ya con el descuento.
 */
float Tequila::descontar(int cantidad) {
    float total = precio * cantidad;
    if (agave){
        cout << "No se encontraron descuentos disponibles" << endl;
        cout << "Total: $" << total << endl;
        return total;
    } else {
        if (cantidad > 7) return Bebida::descontar(cantidad);
        else {
            cout << "Total: $" << total << endl;
            return total;
        }
    }
}

/**
 * toTexto serializa los atributos del tequila en formato CSV.
 * 
 * Genera una línea de texto con todos los campos separados por comas para 
 * ser escrita en el archivo Bebidas.txt y poder reconstruir el objeto al
 * leer el archivo con cargar_bebidas() de la clase Licoreria.
 * 
 * @param
 * @return string con los atributos del tequila en formato CSV.
 */
string Tequila::toTexto() {
    string texto;
    texto = "Tequila," + to_string(stock) + "," + to_string(porcentaje)
        + "," + to_string(precio) + "," + to_string(descuento) + "," + marca 
        + "," + pais + "," + nombre + "," + region + "," + categoria + "," 
        + to_string(agave);
        return texto;
}

/**
 * Vino hereda de Bebida y tiene como atributos el tipo de uva y el año
 * de cosecha. No tiene lógica de descuento propia, usa la que hereda de
 * la clase madre Bebida. 
 */
class Vino : public Bebida {
private:
    string uva;
    int year_cosecha;

public:
    // Constructor
    Vino(string _tipo_bebida, int _stock, float _porcentaje, float _precio, 
        float _descuento, const string& _marca, const string& _pais, 
        const string& _nombre, const string& _uva, int _year_cosecha);
    
    // Destructor
    virtual ~Vino(){}
    
    // Getters
    string getUva();
    int getYearCosecha();

    void servir();
    string toString();
    string toTexto();
};

Vino::Vino(string _tipo_bebida, int _stock, float _porcentaje, float _precio, 
        float _descuento, const string& _marca, const string& _pais, 
        const string& _nombre, const string& _uva, int _year_cosecha) : 
        Bebida(_tipo_bebida, _stock, _porcentaje, _precio, _descuento, _marca, 
            _pais, _nombre) {
                uva = _uva;
                year_cosecha = _year_cosecha;
            }

string Vino::getUva() {return uva;}
int Vino::getYearCosecha() {return year_cosecha;}

/**
 * servir imprime en pantalla el mensaje al entregar una copa de vino al
 * cliente.
 * 
 * Muestra el nombre del vino y su año de cosecha para darle contexto al
 * cliente sobre lo que está consumiendo.
 * 
 * @param
 * @return
 */
void Vino::servir() {
    cout << "Una copa del vino " << nombre << ", cosecha " << year_cosecha 
    << endl;
}

/**
 * toString extiende el toString de Bebida añadiendo el tipo de uva y
 * el año de cosecha.
 * 
 * Llama a Bebida::toString() para obtener los datos base y concatena
 * al final el tipo de uva con el que fue elaborado y el año de cosecha.
 * 
 * @param
 * @return string con todos los atributos del vino concatenados.
 */
string Vino::toString() {
        string texto;
        texto = Bebida::toString() + "\nTipo de uva: " + uva + 
        "\nAño de cosecha: " + to_string(year_cosecha);
    return texto;
}

/**
 * toTexto serializa los atributos del vino en formato CSV.
 * 
 * Genera una línea de texto con todos los campos separados por comas para
 * ser escrita en el archivo Bebidas.txt y poder reconstruir el objeto al
 * leer el archivo con cargar_bebidas() de la clase Licoreria.
 * 
 * @param
 * @return string con los atributos del vino en formato CSV.
 */
string Vino::toTexto() {
    string texto;
    texto = "Vino," + to_string(stock) + "," + to_string(porcentaje)
        + "," + to_string(precio) + "," + to_string(descuento) + "," + marca 
        + "," + pais + "," + nombre + "," + uva + "," + 
        to_string(year_cosecha);
    return texto;
}

/**
 * Vodka hereda de Bebida y tiene atributos como el sabor y el no. de 
 * destilaciones. Solo aplica descuento del 18% cuando el cliente compra 5
 * o más unidades de un vodka con menos de 5 destilaciones.
 */
class Vodka : public Bebida {
private:
    string sabor;
    int destilaciones;

public:
    // Constructor
    Vodka(string _tipo_bebida, int _stock, float _porcentaje, float _precio, 
        float _descuento, const string& _marca, const string& _pais, 
        const string& _nombre, const string& _sabor, int _destilaciones);
    
    // Destructor
    virtual ~Vodka(){}

    // Getters
    string getSabor();
    int getDestilaciones();

    void servir();
    string toString();
    float descontar(int cantidad);
    string toTexto();
};

Vodka::Vodka(string _tipo_bebida, int _stock, float _porcentaje, float _precio, 
        float _descuento, const string& _marca, const string& _pais, 
        const string& _nombre, const string& _sabor, int _destilaciones) 
        : Bebida(_tipo_bebida, _stock, _porcentaje, precio, _descuento, _marca, 
            _pais, _nombre) {
                sabor = _sabor;
                destilaciones = _destilaciones;
            }

string Vodka::getSabor() {return sabor;}
int Vodka::getDestilaciones() {return destilaciones;}

/**
 * servir imprime en pantalla el mensaje al entregar un vodka al cliente.
 * 
 * Muestra el nombre del sabor del vodka que se está sirviendo.
 * 
 * @param
 * @return
 */
void Vodka::servir() {cout << "Ten un vodka de " << sabor << endl;}

/**
 * toString extiende el toString de Bebida añadiendo el sabor y las
 * destilaciones.
 * 
 * Llama a Bebida::toString() para obtener para obtener los datos base y 
 * concatena al final el sabor del vodka y el número de veces que fue
 * destilado. 
 * 
 * @param
 * @return string con todos los atributos del vodka concatenados.
 */
string Vodka::toString()  {
        string texto = Bebida::toString() + "\nSabor: " + sabor 
    + "\nNúmero de destilaciones: " + to_string(destilaciones); 
    return texto;
}

/**
 * Si el cliente compra 4 o menos unidades o si el vodka tiene 5 o más 
 * destilaciones, no se vueleve elegible para un descuento. Si el cliente
 * compra 5 o más de un vodka con menos de 5 destilaciones, se aplica un 
 * 18% de descuento y se manda el cálculo a Bebida::descontar(int).
 * 
 * @param int cantidad número de botella que el cliente desea comprar.
 * @return float con el precio final de la compra ya con descuento apicado.
 */
float Vodka::descontar(int cantidad) {
    if (cantidad <= 4 || destilaciones >= 5){
        float total = precio * cantidad;
        cout << "Total: $" << total << endl;
        return total;
    } else if(cantidad >= 5 && destilaciones < 5){
        cout << "Se aplicó un 18% de descuento" << endl;
        descuento = 0.18;
        return Bebida::descontar(cantidad);
    }
    return Bebida::descontar(cantidad);
}

/**
 * toTexto serializa los atributos del vodka en formato CSV.
 * 
 * Genera una línea de texto con todos los campos separados por comas
 * para ser escrita en el archivo Bebidas.txt y poder reconstruir el
 * objeto al leer el archivo con cargar_bebidas() de la clase Licoreria.
 * 
 * @param 
 * @return string con los atributos del vodka en formato CSV.
 */
string Vodka::toTexto() {
    string texto;
    texto = "Vodka," + to_string(stock) + "," + to_string(porcentaje)
        + "," + to_string(precio) + "," + to_string(descuento) + "," + marca 
        + "," + pais + "," + nombre + "," + sabor + "," + 
        to_string(destilaciones);
    return texto;
}

/**
 * Whiskey hereda de Bebida y tiene de atributos los años de añejamiento
 * y el tipo de barrica. Los whiskeys con más de 20 años de añejamiento
 * no son elegibles para un descuento.
 */
class Whiskey : public Bebida {
private:
    int years_aged; 
    string barrica;

public:
    // Constructor
    Whiskey(string _tipo_bebida, int _stock, float _porcentaje, float _precio, 
        float _descuento, const string& _marca, const string& _pais, 
        const string& _nombre, int _years_aged, const string& _barrica);
    
    // Destructor
    virtual ~Whiskey(){}
    
    // Getters
    int getYearsAged();
    string getBarrica();

    void servir();
    string toString();
    float descontar(int cantidad);
    string toTexto();
};

Whiskey::Whiskey(string _tipo_bebida, int _stock, float _porcentaje, 
        float _precio, float _descuento, const string& _marca, 
        const string& _pais, const string& _nombre, int _years_aged, 
        const string& _barrica) : Bebida(_tipo_bebida, _stock, _porcentaje, 
            _precio, _descuento, _marca, _pais, _nombre) {
                years_aged = _years_aged;
                barrica = _barrica;
            }

int Whiskey::getYearsAged() {return years_aged;}
string Whiskey::getBarrica() {return barrica;}

/**
 * servir imprime en pantalla el mensaje al entregar un whiskey al cliente
 * 
 * Muestra los años de añejamiento y el tipo de barrica en la que fue
 * envejecido para darle contexto al cliente de lo que está consumiendo.
 * 
 * @param
 * @return
 */
void Whiskey::servir() {
    cout << "Ten un whiskey de " << years_aged 
        << " años de añejamiento de una barrica " << barrica << endl;
}

/**
 * toString extiende el toString de Bebida añadiendo años de añejamiento
 * y barrica. 
 * 
 * Llama a Bebida::toString() para obtener los datos base y concatena al
 * final los años que estuvo añejado y el tipo de barrica utilizada.
 * 
 * @param
 * @return string con todos los atributos del whiskey concatenados.
 */
string Whiskey::toString() {
        string texto = Bebida::toString() + "\nAños de añejamiento: " 
    + to_string(years_aged) + "\nTipo de barrica: " + barrica;
    return texto;
}

/**
 * Los whiskies con más de 20 años de añejamiento se considerna premium
 * por ende, no son elegibles para un descuento. Para el resto, se manda
 * el cálculo a Bebida::descontar(int).
 * 
 * @param int cantidad número de botellas que el cliente desea comprar.
 * @return float con el precio final de la compra ya con descuento 
 * aplicado. 
 */
float Whiskey::descontar(int cantidad) {
    if (years_aged > 20) {
        float total = precio * cantidad;
        cout << "Total: $" << total << endl;
        return total;
    }
    return Bebida::descontar(cantidad);
}

/**
 * toTexto serializa los atributos del whiskey en formato CSV.
 * 
 * Genera una línea de texto con todos los campos separados por comas
 * para ser escrita en el archivo Bebidas.txt y poder reconstruir el
 * objeto al leer el archivo con cargar_bebidas() de la clase Licoreria.
 * 
 * @param
 * @return string con los atributos del whiskey en formato CSV.
 */
string Whiskey::toTexto() {
    string texto;
    texto = "Whiskey," + to_string(stock) + "," + to_string(porcentaje)
        + "," + to_string(precio) + "," + to_string(descuento) + "," + marca 
        + "," + pais + "," + nombre + "," + to_string(years_aged) 
        + "," + barrica;
    return texto;
}

#endif