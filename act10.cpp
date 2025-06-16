//Ejemplos de punteros vistos en clase 

#include <iostream>
using namespace std;
int main() {
    int *v1 = nullptr;
    int value = 4;
    v1 = &value;
    cout << v1 << "\n";
    cout << *v1 << endl;
    (*v1)++;
    cout << *v1 << "in";
    cout << value << "\n";
    int *v2 = new int(2);
    cout << v2 << endl;
    cout << *v2 << endl;
    delete v2;
    return 0;
}
