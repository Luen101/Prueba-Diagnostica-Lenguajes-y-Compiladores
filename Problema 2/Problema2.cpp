#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cctype>

using namespace std;

bool validarTablero(string tablero) {
    int filas = 0, casillasEnFila = 0;
    for (char c : tablero) {
        if (c == '/') {
            if (casillasEnFila != 8) return false;
            filas++;
            casillasEnFila = 0;
        } else if (isdigit(c)) {
            casillasEnFila += (c - '0');
        } else if (string("pnbrqkPNBRQK").find(c) != string::npos) {
            casillasEnFila++;
        } else return false;
    }
    return (filas == 7 && casillasEnFila == 8);
}

bool esNotacionFEN(string* cadena) {
    stringstream ss(*cadena);
    string campo;
    vector<string>* campos = new vector<string>();

    while (ss >> campo) {
        campos->push_back(campo);
    }

    if (campos->size() != 6) {
        delete campos;
        return false;
    }

    if (!validarTablero((*campos)[0])) return false;

    if ((*campos)[1] != "w" && (*campos)[1] != "b") return false;

    for (char c : (*campos)[2]) {
        if (c != '-' && string("KQkq").find(c) == string::npos) return false;
    }

    delete campos;
    return true;
}

int main() {
    string* C = new string();
    cout << "--- Validador de Notacion FEN (UNEG) ---" << endl;
    cout << "Ingrese la cadena C: ";
    getline(cin, *C);

    if (esNotacionFEN(C)) {
        cout << "\nRESULTADO: La cadena se encuentra en notacion FEN valida." << endl;
    } else {
        cout << "\nRESULTADO: La cadena NO es una notacion FEN valida." << endl;
    }

    delete C;
    return 0;
}
