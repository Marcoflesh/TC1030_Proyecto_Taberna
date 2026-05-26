#ifndef BEBIDAS_H
#define BEBIDAS_H

#include <string>
#include <iostream>

using namespace std;

// 1. Clase Abstracta
class Bebida {
protected:
    int stock;
    float porcentaje, precio, descuento;
    string nombre, marca, pais, tipo_bebida;

public:
    Bebida(string _tipo_bebida, int _stock, float _porcentaje, float _precio, 
        float _descuento, const string& _marca, const string& _pais, 
        const string& _nombre);

    virtual ~Bebida(){}

    int getStock() {return stock;}
    float getGrados() {return porcentaje;}
    float getPrecio() {return precio;}
    float getDescuento() {return descuento;}
    string getNombre() {return nombre;}
    string getMarca() {return marca;}
    string getPais() {return pais;}
    string getTipoBebida() {return tipo_bebida;}

    void sumarStock(int cantidad);
    void restarStock(int loot);

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

void Bebida::sumarStock(int cantidad) {
    stock += cantidad;
}

void Bebida::restarStock(int cantidad) {
    stock -= abs(cantidad);
}

float Bebida::descontar(float total) {
    float descontado =precio - (precio * descuento);
    cout << "Se aplico un descuento a " << nombre << " del "
         << (descuento * 100) << "%, nuevo precio: $" << descontado << endl;
    return descontado;
}

float Bebida::descontar(int cantidad) {
    if (cantidad <= 0) {
        cout << "Cantidad invalida." << endl;
        return 0.0;
    }
    float total = precio * cantidad;
    cout << "Tomaste " << cantidad << " de " << nombre << endl;
    return descontar(total);
}

string Bebida::toString() {
    string texto = "Bebida: " + nombre + "\nMarca: " + marca + "\nPais: " 
        + pais + "\nPorcentaje de alcohol: " + to_string(porcentaje) 
        + "\nPrecio: $" + to_string(precio) + "\nCon descuento de : " 
        + to_string(descuento);
    return texto;
}

// 2. Cerveza
class Cerveza : public Bebida {
private:
    string tipo;
    float ibu; 

public:
    Cerveza(string _tipo_bebida, int _stock, float _porcentaje, float _precio, 
        float _descuento, const string& _marca, const string& _pais, 
        const string& _nombre, const string& _tipo, float _ibu);
    virtual ~Cerveza(){}
    
    string getTipo(){return tipo;}
    float getIbu(){return ibu;}

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

void Cerveza::servir() {
    cout << "Sirviendo una " << nombre << " tipo " << tipo << "." << endl;
}

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

string Cerveza::toString() {
    return Bebida::toString() + "\nTip: " + tipo + "\nIBU (amargor): "
        + to_string(ibu);
}

string Cerveza::toTexto() {
    string texto;
    texto = "Cerveza," + to_string(stock) + "," + to_string(porcentaje)
        + "," + to_string(precio) + "," + to_string(descuento)
        + "," + marca + "," + pais + "," + nombre
        + "," + tipo + "," + to_string(ibu);
        return texto;
}

// 3. Mezcal
class Mezcal : public Bebida {
private:
    string tipo_agave;
    bool gusano;

public:
    Mezcal(string _tipo_bebida, int _stock, float _porcentaje, float _precio, 
        float _descuento, const string& _marca, const string& _pais, 
        const string& _nombre, const string& _tipo_agave, bool _gusano);
    virtual ~Mezcal(){}

    string getTipoAgave(){return tipo_agave;}
    bool getGusano(){return gusano;}

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

void Mezcal::servir() {
    cout << "Aqui tienes un " << nombre << " de agave " << tipo_agave 
    << "." << endl;
    if (gusano) {
        cout << "Este mezcal trae gusano de maguey." << endl;
    }   
}

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

string Mezcal::toString() {
    string texto, g = gusano ? "con gusano" : "sin gusano";
    texto = Bebida::toString() + "\nAgave: " + tipo_agave + "\n" + g;
    return texto; 
}

string Mezcal::toTexto() {
    string texto;
    texto = "Mezcal," + to_string(stock) + "," + to_string(porcentaje)
        + "," + to_string(precio) + "," + to_string(descuento) + "," + marca 
        + "," + pais + "," + nombre + "," + tipo_agave + "," + 
        to_string(gusano);
    return texto;
}

// 4. Ron
class Ron : public Bebida {
private:
    string estilo;
    bool especias;

public:
    Ron(string _tipo_bebida, int _stock, float _porcentaje, float _precio, 
        float _descuento, const string& _marca, const string& _pais, 
        const string& _nombre, const string& _estilo, bool _especias);

    virtual ~Ron(){}

    string getEstilo(){return estilo;}
    bool getEspecias(){return especias;}

    void servir();
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

string Ron::toString() {
    string especiado = especias ? "especiado" : "puro", texto;
    texto = Bebida::toString() + "\nEstilo de ron: " + estilo + "\nTipo: " 
    + especiado;
    return texto;
}

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

string Ron::toTexto() {
    string texto;
    texto = "Ron," + to_string(stock) + "," + to_string(porcentaje)
        + "," + to_string(precio) + "," + to_string(descuento) + "," + marca 
        + "," + pais + "," + nombre + "," + estilo + "," + to_string(especias);
    return texto;
}

// 5. Tequila
class Tequila : public Bebida {
private:
    string region, categoria;
    bool agave;

public:
    Tequila(string _tipo_bebida, int _stock, float _porcentaje, float _precio, 
        float _descuento, const string& _marca, const string& _pais, 
        const string& _nombre, const string& _region, const string& _categoria, 
        bool _agave);
    virtual ~Tequila(){}
    
    string getRegion(){return region;}
    string getCategoria(){return categoria;}
    bool isAgave(){return agave;}

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

void Tequila::servir() {
    cout << "Estas tomando tequila " << categoria <<  " de " << region << endl;
    if (categoria == "Blanco") {
        cout << "Tómalo en seco" << endl;
    } else {
        cout << "Tómalo a tragos para un mejor disfrute" << endl;
    }
}

string Tequila::toString() {
    string pureza = agave ? "100% agave" : "mixto", texto;
    texto = Bebida::toString() + "\nRegion: " + region + "\nCategoria: " 
    + categoria + "\nHecho 100% de agave: " + pureza; 
    return texto;
}

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

string Tequila::toTexto() {
    string texto;
    texto = "Tequila," + to_string(stock) + "," + to_string(porcentaje)
        + "," + to_string(precio) + "," + to_string(descuento) + "," + marca 
        + "," + pais + "," + nombre + "," + region + "," + categoria + "," 
        + to_string(agave);
        return texto;
}

// 6. Vino
class Vino : public Bebida {
private:
    string uva;
    int year_cosecha;

public:
    Vino(string _tipo_bebida, int _stock, float _porcentaje, float _precio, 
        float _descuento, const string& _marca, const string& _pais, 
        const string& _nombre, const string& _uva, int _year_cosecha);
    virtual ~Vino(){}
    
    string getUva(){return uva;}
    int getYearCosecha(){return year_cosecha;}

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

void Vino::servir() {
    cout << "Una copa del vino " << nombre << ", cosecha " << year_cosecha 
    << endl;
}

string Vino::toString() {
        string texto;
        texto = Bebida::toString() + "\nTipo de uva: " + uva + 
        "\nAño de cosecha: " + to_string(year_cosecha);
    return texto;
}

string Vino::toTexto() {
    string texto;
    texto = "Vino," + to_string(stock) + "," + to_string(porcentaje)
        + "," + to_string(precio) + "," + to_string(descuento) + "," + marca 
        + "," + pais + "," + nombre + "," + uva + "," + 
        to_string(year_cosecha);
    return texto;
}

// 7. Vodka
class Vodka : public Bebida {
private:
    string sabor;
    int destilaciones;

public:
    Vodka(string _tipo_bebida, int _stock, float _porcentaje, float _precio, 
        float _descuento, const string& _marca, const string& _pais, 
        const string& _nombre, const string& _sabor, int _destilaciones);
    virtual ~Vodka(){}

    string getSabor(){return sabor;}
    int getDestilaciones(){return destilaciones;}

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

void Vodka::servir() {cout << "Ten un vodka de " << sabor << endl;}

string Vodka::toString()  {
        string texto = Bebida::toString() + "\nSabor: " + sabor 
    + "\nNúmero de destilaciones: " + to_string(destilaciones); 
    return texto;
}

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

string Vodka::toTexto() {
    string texto;
    texto = "Vodka," + to_string(stock) + "," + to_string(porcentaje)
        + "," + to_string(precio) + "," + to_string(descuento) + "," + marca 
        + "," + pais + "," + nombre + "," + sabor + "," + 
        to_string(destilaciones);
    return texto;
}

// 8. Whiskey
class Whiskey : public Bebida {
private:
    int years_aged; 
    string barrica;

public:
    Whiskey(string _tipo_bebida, int _stock, float _porcentaje, float _precio, 
        float _descuento, const string& _marca, const string& _pais, 
        const string& _nombre, int _years_aged, const string& _barrica);
    virtual ~Whiskey(){}
    
    int getYearsAged() {return years_aged;}
    string getBarrica() {return barrica;}

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

void Whiskey::servir() {
    cout << "Ten un whiskey de " << years_aged 
        << " años de añejamiento de una barrica " << barrica << endl;
}

string Whiskey::toString() {
        string texto = Bebida::toString() + "\nAños de añejamiento: " 
    + to_string(years_aged) + "\nTipo de barrica: " + barrica;
    return texto;
}

float Whiskey::descontar(int cantidad) {
    if (years_aged > 20) {
        float total = precio * cantidad;
        cout << "Total: $" << total << endl;
        return total;
    }
    return Bebida::descontar(cantidad);
}

string Whiskey::toTexto() {
    string texto;
    texto = "Whiskey," + to_string(stock) + "," + to_string(porcentaje)
        + "," + to_string(precio) + "," + to_string(descuento) + "," + marca 
        + "," + pais + "," + nombre + "," + to_string(years_aged) 
        + "," + barrica;
    return texto;
}

#endif