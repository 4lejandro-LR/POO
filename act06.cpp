#include <iostream>
#include <cmath>
#include <vector>
#include <memory>
using namespace std;

// Interfaz general para figuras
class Figura {
protected:
    double _area = -1;

public:
    virtual double calcularArea() = 0;
    virtual double calcularPerimetro() const = 0;
    virtual void mostrar() const = 0;
    virtual void imprimirDetalles() const = 0;
    virtual ~Figura() {}

    // Método para calcular y guardar área si no se ha hecho aún
    double obtenerArea() {
        if (_area < 0) {
            cout << "Calculando área...\n";
            _area = calcularArea();
        }
        return _area;
    }
};

// Triángulo
class Triangulo : public Figura {
private:
    double base, altura;

public:
    Triangulo(double b, double h) : base(b), altura(h) {}

    double calcularArea() override {
        return (base * altura) / 2.0;
    }

    double calcularPerimetro() const override {
        return 3 * base; // Triángulo equilátero
    }

    void mostrar() const override {
        cout << "Triángulo:\n";
        cout << "Base: " << base << ", Altura: " << altura << endl;
        cout << "Área: " << _area << ", Perímetro: " << calcularPerimetro() << "\n\n";
    }

    void imprimirDetalles() const override {
        cout << "[Detalles] Triángulo - base = " << base << ", altura = " << altura << ", área = " << _area << "\n";
    }
};

// Círculo
class Circulo : public Figura {
private:
    double radio;

public:
    Circulo(double r) : radio(r) {}

    double calcularArea() override {
        return M_PI * radio * radio;
    }

    double calcularPerimetro() const override {
        return 2 * M_PI * radio;
    }

    void mostrar() const override {
        cout << "Círculo:\n";
        cout << "Radio: " << radio << endl;
        cout << "Área: " << _area << ", Perímetro: " << calcularPerimetro() << "\n\n";
    }

    void imprimirDetalles() const override {
        cout << "[Detalles] Círculo - radio = " << radio << ", área = " << _area << "\n";
    }
};

// Cuadrado
class Cuadrado : public Figura {
private:
    double lado;

public:
    Cuadrado(double l) : lado(l) {}

    double calcularArea() override {
        return lado * lado;
    }

    double calcularPerimetro() const override {
        return 4 * lado;
    }

    void mostrar() const override {
        cout << "Cuadrado:\n";
        cout << "Lado: " << lado << endl;
        cout << "Área: " << _area << ", Perímetro: " << calcularPerimetro() << "\n\n";
    }

    void imprimirDetalles() const override {
        cout << "[Detalles] Cuadrado - lado = " << lado << ", área = " << _area << "\n";
    }
};

// Función principal
int main() {
    vector<unique_ptr<Figura>> figuras;

    figuras.push_back(make_unique<Triangulo>(3.0, 4.0));
    figuras.push_back(make_unique<Circulo>(2.5));
    figuras.push_back(make_unique<Cuadrado>(5.0));

    for (const auto& figura : figuras) {
        figura->obtenerArea();       // Calcula el área solo una vez
        figura->mostrar();           // Muestra detalles generales
        figura->imprimirDetalles();  // Muestra detalles técnicos
    }

    return 0;
}
