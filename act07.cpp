#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
using namespace std;

// === INTERFAZ BASE ===
class IFig {
public:
    virtual double area() = 0;
    virtual double perimetro() const = 0;
    virtual void mostrar() const = 0;
    virtual void imprimirDetalles() const = 0;
    virtual ~IFig() {}
};

// === CLASE BASE CON LÓGICA DE ÁREA ===
class FigGeo {
protected:
    double _area = -1;  // Sin calcular

    double getArea() const {
        return _area;
    }

    void saveArea(double val) {
        _area = val;
    }
};

// === TRIÁNGULO ===
class Triangle : public IFig, public FigGeo {
private:
    double base, altura;
public:
    Triangle(double b, double h) : base(b), altura(h) {}

    double area() override {
        if (_area < 0) {
            cout << "Calculando área de triángulo...\n";
            saveArea((base * altura) / 2.0);
        }
        return getArea();
    }

    double perimetro() const override {
        return 3 * base;
    }

    void mostrar() const override {
        cout << "Triángulo:\nBase: " << base << ", Altura: " << altura << ", Área: " << _area << ", Perímetro: " << perimetro() << "\n";
    }

    void imprimirDetalles() const override {
        cout << "[Detalles] Triángulo - base: " << base << ", altura: " << altura << ", área: " << _area << "\n";
    }
};

// === CÍRCULO ===
class Circle : public IFig, public FigGeo {
private:
    double radio;
public:
    Circle(double r) : radio(r) {}

    double area() override {
        if (_area < 0) {
            cout << "Calculando área de círculo...\n";
            saveArea(M_PI * radio * radio);
        }
        return getArea();
    }

    double perimetro() const override {
        return 2 * M_PI * radio;
    }

    void mostrar() const override {
        cout << "Círculo:\nRadio: " << radio << ", Área: " << _area << ", Perímetro: " << perimetro() << "\n";
    }

    void imprimirDetalles() const override {
        cout << "[Detalles] Círculo - radio: " << radio << ", área: " << _area << "\n";
    }
};

// === CUADRADO ===
class Square : public IFig, public FigGeo {
private:
    double lado;
public:
    Square(double l) : lado(l) {}

    double area() override {
        if (_area < 0) {
            cout << "Calculando área de cuadrado...\n";
            saveArea(lado * lado);
        }
        return getArea();
    }

    double perimetro() const override {
        return 4 * lado;
    }

    void mostrar() const override {
        cout << "Cuadrado:\nLado: " << lado << ", Área: " << _area << ", Perímetro: " << perimetro() << "\n";
    }

    void imprimirDetalles() const override {
        cout << "[Detalles] Cuadrado - lado: " << lado << ", área: " << _area << "\n";
    }
};

int main() {
    // Fábricas usando funciones lambda (más flexible que clases)
    vector<function<unique_ptr<IFig>()>> fabricas;

    fabricas.push_back([] { return make_unique<Triangle>(3.0, 4.0); });
    fabricas.push_back([] { return make_unique<Circle>(2.5); });
    fabricas.push_back([] { return make_unique<Square>(5.0); });

    vector<unique_ptr<IFig>> figuras;

    for (const auto& crear : fabricas) {
        auto figura = crear();        // Crea figura
        figura->area();               // Calcula área (lazy)
        figura->mostrar();            // Muestra datos
        figura->imprimirDetalles();   // Muestra detalles técnicos
        figuras.push_back(move(figura));
    }

    return 0;
}
