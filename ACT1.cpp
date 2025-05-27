#include <iostream>
#include <cmath>
using namespace std;

class Circulo {
private:
    double radio;
public:
    Circulo(double r = 1) {
        radio = r;
    }

    double calcularArea() {
        return M_PI * radio * radio;
    }

    double obtenerRadio() {
        return radio;
    }
};

class Cuadrado {
private:
    double lado;

public:
    Cuadrado(double l = 1) {
        lado = l;
    }

    double calcularArea() {
        return lado * lado;
    }

    double obtenerLado() {
        return lado;
    }
};

class Triangulo {
private:
    double base;
    double altura;

public:
    Triangulo(double b = 1, double h = 1) {
        base = b;
        altura = h;
    }

    double calcularArea() {
        return (base * altura) / 2;
    }

    double obtenerBase() {
        return base;
    }

    double obtenerAltura() {
        return altura;
    }
};


int main() {
    
    Circulo c;
    Cuadrado q;
    Triangulo t;

  
    cout << "Circulo: radio = " << c.obtenerRadio() << ", area = " << c.calcularArea() << endl;
    cout << "Cuadrado: lado = " << q.obtenerLado() << ", area = " << q.calcularArea() << endl;
    cout << "Triangulo: base = " << t.obtenerBase() << ", altura = " << t.obtenerAltura()
         << ", area = " << t.calcularArea() << endl;

    return 0;
}
