#include <iostream>
#include <cmath>  // Para M_PI
using namespace std;

// Interfaz para figuras geométricas
class IFigura {
public:
    virtual double calcularArea() = 0;
    virtual double calcularPerimetro() const = 0;
    virtual void mostrar() const = 0;
    virtual ~IFigura() {}
};

// Clase base abstracta que implementa lógica común
class FiguraBase : public IFigura {
protected:
    double _area = -1;  // -1 indica que aún no se ha calculado

public:
    double calcularArea() override {
        if (_area < 0) {
            cout << "Calculando área...\n";
            _area = calcularAreaReal();
        }
        return _area;
    }

    virtual double calcularAreaReal() = 0;
};

// Triángulo
class Triangulo : public FiguraBase {
private:
    double base, altura;
public:
    Triangulo(double b, double h) : base(b), altura(h) {}

    double calcularAreaReal() override {
        return (base * altura) / 2.0;
    }

    double calcularPerimetro() const override {
        return 3 * base;  // Asume triángulo equilátero
    }

    void mostrar() const override {
        cout << "Triángulo:\n";
        cout << "Base: " << base << ", Altura: " << altura << "\n";
        cout << "Área: " << _area << ", Perímetro: " << calcularPerimetro() << "\n\n";
    }
};

// Círculo
class Circulo : public FiguraBase {
private:
    double radio;
public:
    Circulo(double r) : radio(r) {}

    double calcularAreaReal() override {
        return M_PI * radio * radio;
    }

    double calcularPerimetro() const override {
        return 2 * M_PI * radio;
    }

    void mostrar() const override {
        cout << "Círculo:\n";
        cout << "Radio: " << radio << "\n";
        cout << "Área: " << _area << ", Perímetro: " << calcularPerimetro() << "\n\n";
    }
};

// Cuadrado
class Cuadrado : public FiguraBase {
private:
    double lado;
public:
    Cuadrado(double l) : lado(l) {}

    double calcularAreaReal() override {
        return lado * lado;
    }

    double calcularPerimetro() const override {
        return 4 * lado;
    }

    void mostrar() const override {
        cout << "Cuadrado:\n";
        cout << "Lado: " << lado << "\n";
        cout << "Área: " << _area << ", Perímetro: " << calcularPerimetro() << "\n\n";
    }
};

// Función principal
int main() {
    IFigura* figuras[] = {
        new Triangulo(3.0, 4.0),
        new Circulo(2.5),
        new Cuadrado(5.0)
    };

    for (IFigura* fig : figuras) {
        fig->calcularArea();  // Solo calcula si no está guardado
        fig->mostrar();       // Muestra información
        delete fig;           // Libera memoria
    }

    return 0;
}
