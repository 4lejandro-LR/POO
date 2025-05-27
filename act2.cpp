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

    double obtenerRadio() {
        return radio;
    }

    double calcularArea() {
        return M_PI * radio * radio;
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
    
    Triangulo t;
    Circulo c;

    cout << "Área del triángulo: " << t.calcularArea() << endl;
    cout << "Área del círculo: " << c.calcularArea() << endl;
    cout << "Radio del círculo: " << c.obtenerRadio() << endl;

    return 0;
}
