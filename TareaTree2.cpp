#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

const int MAX_PERSONAS = 100;

class Nodo {
public:
    int id;
    char nombre[50];
    char apellido[50];
    int edad;
    Nodo* padre;
    Nodo* madre;
    Nodo* hermanos[MAX_PERSONAS];
    int numHermanos;

    Nodo(int id, const char* nombre, const char* apellido, int edad)
        : id(id), edad(edad), padre(nullptr), madre(nullptr), numHermanos(0) {
        strcpy(this->nombre, nombre);
        strcpy(this->apellido, apellido);
        memset(hermanos, 0, sizeof(hermanos));
    }
};

class ArbolGenealogico {
private:
    Nodo* personas[MAX_PERSONAS];
    int numPersonas;

public:
    ArbolGenealogico() : numPersonas(0) {
        memset(personas, 0, sizeof(personas));
    }

    void agregarPersona(int id, const char* nombre, const char* apellido, int edad) {
        if (numPersonas < MAX_PERSONAS) {
            personas[numPersonas++] = new Nodo(id, nombre, apellido, edad);
        }
    }

    Nodo* buscarPersona(int id) {
        for (int i = 0; i < numPersonas; ++i) {
            if (personas[i]->id == id) {
                return personas[i];
            }
        }
        return nullptr;
    }

    void establecerPadres(int id, int idPadre, int idMadre) {
        Nodo* persona = buscarPersona(id);
        if (persona) {
            persona->padre = buscarPersona(idPadre);
            persona->madre = buscarPersona(idMadre);
        }
    }

    void agregarHermano(int id, int idHermano) {
        Nodo* persona = buscarPersona(id);
        Nodo* hermano = buscarPersona(idHermano);
        if (persona && hermano && persona->numHermanos < MAX_PERSONAS) {
            persona->hermanos[persona->numHermanos++] = hermano;
        }
    }

    void mostrarArbol(int id, int nivel = 0) {
        Nodo* persona = buscarPersona(id);
        if (persona) {
            cout << string(nivel * 2, ' ') << persona->nombre << " " << persona->apellido << " (" << persona->edad << " anos)" << endl;
            if (persona->padre) {
                cout << string((nivel + 1) * 2, ' ') << "Padre: " << persona->padre->nombre << " " << persona->padre->apellido << endl;
            }
            if (persona->madre) {
                cout << string((nivel + 1) * 2, ' ') << "Madre: " << persona->madre->nombre << " " << persona->madre->apellido << endl;
            }
            if (persona->numHermanos > 0) {
                cout << string((nivel + 1) * 2, ' ') << "Hermanos:" << endl;
                for (int i = 0; i < persona->numHermanos; ++i) {
                    cout << string((nivel + 2) * 2, ' ') << persona->hermanos[i]->nombre << " " << persona->hermanos[i]->apellido << " (" << persona->hermanos[i]->edad << " anos)" << endl;
                }
            }
        }
    }
};

void leerCSV(const char* archivo, ArbolGenealogico& arbol) {
    ifstream file(archivo);
    string line;
    getline(file, line); // Leer la cabecera

    while (getline(file, line)) {
        stringstream ss(line);
        string id, nombre, apellido, edad;
        getline(ss, id, ',');
        getline(ss, nombre, ',');
        getline(ss, apellido, ',');
        getline(ss, edad, ',');

        arbol.agregarPersona(stoi(id), nombre.c_str(), apellido.c_str(), stoi(edad));
    }
}

int main() {
    ArbolGenealogico arbol;
    leerCSV("PERSONASTREE.CSV", arbol);

 
    arbol.establecerPadres(1, 2, 3);
    arbol.agregarHermano(1, 4);
    arbol.agregarHermano(1, 5);
    arbol.mostrarArbol(1);

    return 0;
}