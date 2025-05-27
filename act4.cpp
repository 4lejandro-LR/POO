#include <iostream>
#include <cmath>
using namespace std;


class Figura {
public:
    virtual double area() = 0;
};

class Triangulo : public Figura {
private:
    double base, altura;

public:
    Triangulo(double b, double h) {
        base = b;
        altura = h;
    }

    double area() override {
        return (base * altura) / 2;
    }
};

class Cuadrado : public Figura {
private:
    double lado;

public:
    Cuadrado(double l) {
        lado = l;
    }

    double area() override {
        return lado * lado;
    }
};

class Circulo : public Figura {
private:
    double diametro;

public:
    Circulo(double d) {
        diametro = d;
    }

    double area() override {
        double radio = diametro / 2;
        return 3.1416 * radio * radio;
    }
};

int main() {
    Figura* figuras[3];

    figuras[0] = new Triangulo(8, 4);
    figuras[1] = new Cuadrado(5);
    figuras[2] = new Circulo(10);

    cout << "Área del triángulo: " << figuras[0]->area() << endl;
    cout << "Área del cuadrado: " << figuras[1]->area() << endl;
    cout << "Área del círculo: " << figuras[2]->area() << endl;
  
    for (int i = 0; i < 3; i++) {
        delete figuras[i];
    }

    return 0;
}
