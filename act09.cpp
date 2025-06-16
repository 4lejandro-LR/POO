#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
#include <string>

using namespace std;

// INTERFACES Y BASES
class FigGeoPrinter {
public:
    virtual void PrintDetails() const = 0;
    virtual ~FigGeoPrinter() = default;
};

class IFig {
public:
    virtual double area() = 0;
    virtual double perimetro() const = 0;
    virtual void mostrar() const = 0;
    virtual ~IFig() = default;
};

class FigGeo {
protected:
    double _area = 0;
public:
    virtual double calcArea() = 0;

    void saveArea() {
        if (_area == 0) {
            cout << "Calculando área...\n";
            _area = calcArea();
        }
    }

    double getArea() const {
        return _area;
    }
};

// FIGURAS

class Triangle : public IFig, public FigGeo, public FigGeoPrinter {
private:
    double base, altura;
public:
    Triangle(double b, double h) : base(b), altura(h) {}

    double calcArea() override {
        return (base * altura) / 2.0;
    }

    double area() override {
        saveArea();
        return getArea();
    }

    double perimetro() const override {
        return 3 * base;
    }

    void mostrar() const override {
        cout << "Triángulo:\n";
        cout << "Base: " << base << ", Altura: " << altura << endl;
        cout << "Área: " << _area << ", Perímetro: " << perimetro() << "\n\n";
    }

    void PrintDetails() const override {
        cout << "[PrintDetails] Triángulo - base = " << base << ", altura = " << altura << ", área = " << _area << "\n";
    }
};

class Circle : public IFig, public FigGeo, public FigGeoPrinter {
private:
    double radio;
public:
    Circle(double r) : radio(r) {}

    double calcArea() override {
        return M_PI * radio * radio;
    }

    double area() override {
        saveArea();
        return getArea();
    }

    double perimetro() const override {
        return 2 * M_PI * radio;
    }

    void mostrar() const override {
        cout << "Círculo:\n";
        cout << "Radio: " << radio << endl;
        cout << "Área: " << _area << ", Perímetro: " << perimetro() << "\n\n";
    }

    void PrintDetails() const override {
        cout << "[PrintDetails] Círculo - radio = " << radio << ", área = " << _area << "\n";
    }
};

class Square : public IFig, public FigGeo, public FigGeoPrinter {
private:
    double lado;
public:
    Square(double l) : lado(l) {}

    double calcArea() override {
        return lado * lado;
    }

    double area() override {
        saveArea();
        return getArea();
    }

    double perimetro() const override {
        return 4 * lado;
    }

    void mostrar() const override {
        cout << "Cuadrado:\n";
        cout << "Lado: " << lado << endl;
        cout << "Área: " << _area << ", Perímetro: " << perimetro() << "\n\n";
    }

    void PrintDetails() const override {
        cout << "[PrintDetails] Cuadrado - lado = " << lado << ", área = " << _area << "\n";
    }
};

// FACTORÍA ABSTRACTA
class FigFactory {
public:
    virtual unique_ptr<IFig> createFig() const = 0;
    virtual ~FigFactory() = default;
};

// FACTORÍAS CONCRETAS
class TriangleFactory : public FigFactory {
    double base, altura;
public:
    TriangleFactory(double b, double h) : base(b), altura(h) {}
    unique_ptr<IFig> createFig() const override {
        return make_unique<Triangle>(base, altura);
    }
};

class CircleFactory : public FigFactory {
    double radio;
public:
    CircleFactory(double r) : radio(r) {}
    unique_ptr<IFig> createFig() const override {
        return make_unique<Circle>(radio);
    }
};

class SquareFactory : public FigFactory {
    double lado;
public:
    SquareFactory(double l) : lado(l) {}
    unique_ptr<IFig> createFig() const override {
        return make_unique<Square>(lado);
    }
};

// REPOSITORIO MODERNIZADO
class RepoArrFloat {
private:
    vector<float> data;
public:
    void Save(float valor) {
        data.push_back(valor);
        cout << "Área guardada [" << data.size() - 1 << "]: " << valor << endl;
    }

    float GetArea(size_t index) const {
        if (index < data.size()) {
            return data[index];
        } else {
            cout << "Índice inválido\n";
            return -1;
        }
    }

    size_t getCount() const {
        return data.size();
    }
};

// MAIN MODERNIZADO
int main() {
    vector<unique_ptr<FigFactory>> factories;
    factories.push_back(make_unique<TriangleFactory>(3.0, 4.0));
    factories.push_back(make_unique<CircleFactory>(2.5));
    factories.push_back(make_unique<SquareFactory>(5.0));

    RepoArrFloat repo;

    for (const auto& factory : factories) {
        unique_ptr<IFig> figura = factory->createFig();
        FigGeoPrinter* printer = dynamic_cast<FigGeoPrinter*>(figura.get());

        float area = figura->area();
        figura->mostrar();

        if (printer) {
            printer->PrintDetails();
        }

        repo.Save(area);
    }

    cout << "\n--- Áreas almacenadas en el repositorio ---\n";
    for (size_t i = 0; i < repo.getCount(); ++i) {
        cout << "Área[" << i << "]: " << repo.GetArea(i) << "\n";
    }

    return 0;
}
