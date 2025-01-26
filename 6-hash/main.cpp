#include "Hash.h"

int main() {
    Hash<int,int> hashMapInt;
    hashMapInt.put(1, 100);
    hashMapInt.put(2, 200);
    hashMapInt.put(3, 300);
    cout << "Valor asociado a la clave 1: " << hashMapInt.get(1) << endl;
    cout << "Valor asociado a la clave 2: " << hashMapInt.get(2) << endl;
    cout << "Valor asociado a la clave 4 (no existe): " << hashMapInt.get(4) << endl;

    cout << "El tamaño actual es: " << hashMapInt.size() << endl;

    hashMapInt.remove(2);
    cout << "Valor asociado a la clave 2 después de eliminarla: " << hashMapInt.get(2) << endl;

    cout << "¿La clave 3 existe?: " << (hashMapInt.exists(3) ? "Sí" : "No") << endl;
    cout << "¿La clave 4 existe?: " << (hashMapInt.exists(4) ? "Sí" : "No") << endl;

    hashMapInt.clear();
    cout << "Tamaño después de limpiar: " << hashMapInt.size() << endl;

    Hash<char,int> hashMapChar;
    hashMapChar.put('a', 10);
    hashMapChar.put('b', 20);
    hashMapChar.put('c', 30);
    cout << "Valor asociado a la clave 'a': " << hashMapChar.get('a') << endl;
    cout << "Valor asociado a la clave 'b': " << hashMapChar.get('b') << endl;

    Hash<string,int> hashMapString;
    hashMapString.put("apple", 50);
    hashMapString.put("banana", 30);
    cout << "Valor asociado a la clave 'apple': " << hashMapString.get("apple") << endl;
    cout << "Valor asociado a la clave 'banana': " << hashMapString.get("banana") << endl;

    return 0;
}
