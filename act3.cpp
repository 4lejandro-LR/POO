#include <iostream>
#include <cmath>

class Circulo {
private:
    double radio;
    double area;
    bool areaCalculada;

public:
    Circulo(double r) : radio(r), area(0), areaCalculada(false) {}

    void calcularArea() {
        if (!areaCalculada) {
            area = M_PI * radio * radio;
            areaCalculada = true;
        }
    }

    double getArea() {
        calcularArea();
        return area;
    }
};

class Cuadrado {
private:
    double lado;
    double area;
    bool areaCalculada;

public:
    Cuadrado(double l) : lado(l), area(0), areaCalculada(false) {}

    void calcularArea() {
        if (!areaCalculada) {
            area = lado * lado;
            areaCalculada = true;
        }
    }

    double getArea() {
        calcularArea();
        return area;
    }
};

class Triangulo {
private:
    double base;
    double altura;
    double area;
    bool areaCalculada;

public:
    Triangulo(double b, double h) : base(b), altura(h), area(0), areaCalculada(false) {}

    void calcularArea() {
        if (!areaCalculada) {
            area = (base * altura) / 2.0;
            areaCalculada = true;
        }
    }

    double getArea() {
        calcularArea();
        return area;
    }
};

int main() {
    Circulo c(4);
    Cuadrado q(5);
    Triangulo t(6, 3);

    std::cout << "Área del círculo: " << c.getArea() << std::endl;
    std::cout << "Área del cuadrado: " << q.getArea() << std::endl;
    std::cout << "Área del triángulo: " << t.getArea() << std::endl;

    return 0;
}
