#include <iostream>
#include <string>
#include <memory>
using namespace std;

// Interfaz
class INotificacion {
public:
    virtual void enviar(const string& mensaje) = 0;
    virtual ~INotificacion() {}
};

// Implementaciones
class EmailNotificacion : public INotificacion {
public:
    void enviar(const string& mensaje) override {
        cout << "[EMAIL] Enviando email: " << mensaje << endl;
    }
};

class PushNotificacion : public INotificacion {
public:
    void enviar(const string& mensaje) override {
        cout << "[PUSH] Enviando notificación push: " << mensaje << endl;
    }
};

class SMSNotificacion : public INotificacion {
public:
    void enviar(const string& mensaje) override {
        cout << "[SMS] Enviando mensaje de texto: " << mensaje << endl;
    }
};

// Interfaz de la fábrica
class NotificacionFactory {
public:
    virtual unique_ptr<INotificacion> crearNotificacion() = 0;
    virtual ~NotificacionFactory() {}
};

// Fábricas concretas
class EmailFactory : public NotificacionFactory {
public:
    unique_ptr<INotificacion> crearNotificacion() override {
        return make_unique<EmailNotificacion>();
    }
};

class PushFactory : public NotificacionFactory {
public:
    unique_ptr<INotificacion> crearNotificacion() override {
        return make_unique<PushNotificacion>();
    }
};

class SMSFactory : public NotificacionFactory {
public:
    unique_ptr<INotificacion> crearNotificacion() override {
        return make_unique<SMSNotificacion>();
    }
};

// Lógica de envío
void enviarAlerta(NotificacionFactory& factory, const string& mensaje) {
    auto notificacion = factory.crearNotificacion();
    notificacion->enviar(mensaje);
}

int main() {
    EmailFactory emailFactory;
    PushFactory pushFactory;
    SMSFactory smsFactory;

    enviarAlerta(emailFactory, "Tu pedido ha sido confirmado.");
    enviarAlerta(pushFactory, "Tienes una nueva oferta.");
    enviarAlerta(smsFactory, "Código de verificación: 123456");

    return 0;
}
