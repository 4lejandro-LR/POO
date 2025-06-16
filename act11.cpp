#include <iostream>
#include <cmath>
#include <vector>
#include <memory>

using namespace std;

// -------------------- Interfaz de Repositorio --------------------
class IRepoArea {
public:
    virtual void Save(float valor) = 0;
    virtual float GetArea(int index) const = 0;
    virtual int getCount() const = 0;
    virtual string getNombre() const = 0;
    virtual ~IRepoArea() {}
};

// -------------------- Repositorio con Arreglo --------------------
class RepoArrFloat : public IRepoArea {
private:
    float data[100];
    int count = 0;
public:
    void Save(float valor) override {
        if (count < 100) {
            data[count++] = valor;
            cout << "Guardado [" << count - 1 << "] en Arreglo: " << valor << endl;
        } else {
            cout << "Repositorio de arreglo lleno\n";
        }
    }

    float GetArea(int index) const override {
        return (index >= 0 && index < count) ? data[index] : -1;
    }

    int getCount() const override {
        return count;
    }

    string getNombre() const override {
        return "Arreglo";
    }
};

// -------------------- Repositorio con Vector --------------------
class RepoVector : public IRepoArea {
private:
    vector<float> data;
public:
    void Save(float valor) override {
        data.push_back(valor);
        cout << "Guardado [" << data.size() - 1 << "] en Vector: " << valor << endl;
    }

    float GetArea(int index) const override {
        return (index >= 0 && index < data.size()) ? data[index] : -1;
    }

    int getCount() const override {
        return static_cast<int>(data.size());
    }

    string getNombre() const override {
        return "Vector";
    }
};

// -------------------- Interfaces y FigGeo --------------------
class FigGeoPrinter {
public:
    virtual void PrintDetails() const = 0;
};

class IFig {
public:
    virtual double area() = 0;
    virtual double perimetro() const = 0;
    virtual void mostrar() const = 0;
    virtual ~IFig() {}
};

class FigGeo {
protected:
    double _area = 0;
public:
    virtual double calcArea() = 0;

    void saveArea() {
        if (_area == 0)
            _area = calcArea();
    }

    double getArea() const {
        return _area;
    }
};

// -------------------- Figuras --------------------
class Triangle : public IFig, public FigGeo, public FigGeoPrinter {
private:
    double base, altura;
public:
    Triangle(double b, double h) : base(b), altura(h) {}

    double calcArea() override { return (base * altura) / 2.0; }
    double area() override { saveArea(); return getArea(); }
    double perimetro() const override { return 3 * base; }

    void mostrar() const override {
        cout << "Triángulo: base = " << base << ", altura = " << altura << "\n";
        cout << "Área = " << _area << ", Perímetro = " << perimetro() << "\n";
    }

    void PrintDetails() const override {
        cout << "[PrintDetails] Triángulo: base = " << base << ", altura = " << altura << ", área = " << _area << "\n";
    }
};

class Circle : public IFig, public FigGeo, public FigGeoPrinter {
private:
    double radio;
public:
    Circle(double r) : radio(r) {}

    double calcArea() override { return M_PI * radio * radio; }
    double area() override { saveArea(); return getArea(); }
    double perimetro() const override { return 2 * M_PI * radio; }

    void mostrar() const override {
        cout << "Círculo: radio = " << radio << "\n";
        cout << "Área = " << _area << ", Perímetro = " << perimetro() << "\n";
    }

    void PrintDetails() const override {
        cout << "[PrintDetails] Círculo: radio = " << radio << ", área = " << _area << "\n";
    }
};

class Square : public IFig, public FigGeo, public FigGeoPrinter {
private:
    double lado;
public:
    Square(double l) : lado(l) {}

    double calcArea() override { return lado * lado; }
    double area() override { saveArea(); return getArea(); }
    double perimetro() const override { return 4 * lado; }

    void mostrar() const override {
        cout << "Cuadrado: lado = " << lado << "\n";
        cout << "Área = " << _area << ", Perímetro = " << perimetro() << "\n";
    }

    void PrintDetails() const override {
        cout << "[PrintDetails] Cuadrado: lado = " << lado << ", área = " << _area << "\n";
    }
};

// -------------------- Fábricas --------------------
class FigFactory {
public:
    virtual unique_ptr<IFig> createFig() const = 0;
    virtual ~FigFactory() {}
};

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

// -------------------- Main --------------------
int main() {
    vector<unique_ptr<FigFactory>> factories;
    factories.push_back(make_unique<TriangleFactory>(3.0, 4.0));
    factories.push_back(make_unique<CircleFactory>(2.5));
    factories.push_back(make_unique<SquareFactory>(5.0));

    // Puedes cambiar aquí entre RepoArrFloat y RepoVector
    unique_ptr<IRepoArea> repo = make_unique<RepoVector>();  // O new RepoArrFloat()

    for (auto& factory : factories) {
        auto fig = factory->createFig();
        auto printer = dynamic_cast<FigGeoPrinter*>(fig.get());

        float a = fig->area();
        fig->mostrar();
        if (printer) printer->PrintDetails();

        repo->Save(a);
        cout << "-----------------------\n";
    }

    cout << "\n--- Áreas almacenadas en REPO (" << repo->getNombre() << ") ---\n";
    for (int i = 0; i < repo->getCount(); ++i) {
        cout << "Área[" << i << "] = " << repo->GetArea(i) << "\n";
    }

    return 0;
}
