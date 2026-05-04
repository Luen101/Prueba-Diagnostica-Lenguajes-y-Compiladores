#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <chrono> 

using namespace std;

void mostrarTriangulo(int n) {
    cout << "\nTriangulo de Pascal (niveles 0 a " << n << "):" << endl;
    for (int i = 0; i <= n; i++) {
        long long* fila = new long long[i + 1];
        cout << string((n - i) * 2, ' ');
        for (int j = 0; j <= i; j++) {
            if (j == 0 || j == i) {
                fila[j] = 1;
            } else {
                long long val = 1;
                for (int k = 1; k <= j; k++) {
                    val = val * (i - k + 1) / k;
                }
                fila[j] = val;
            }
            cout << setw(4) << fila[j];
        }
        cout << "  | (n=" << i << ")" << endl;
        delete[] fila;
    }
}

long long* genCoeficiente(int n) {
    long long* coeficientes = new long long[n + 1];
    for (int i = 0; i <= n; ++i) {
        long long val = 1;
        for (int j = 1; j <= i; ++j) {
            val = val * (n - j + 1) / j;
        }
        coeficientes[i] = val;
    }
    return coeficientes;
}

void muestraPol(long long* coeficientes, int n) {
    cout << "\nResultado del polinomio:" << endl;
    cout << "(x+1)^" << n << " = ";
    for (int i = n; i >= 0; i--) {
        if (i < n) cout << " + ";
        if (i == 0) cout << coeficientes[i];
        else if (i == 1) cout << coeficientes[i] << "x";
        else cout << coeficientes[i] << "x^" << i;
    }
    cout << endl;
}

void calcPasos(long long* coeficientes, int n, double x) {
    double total = 0;
    cout << "\nPasos del calculo para f(" << x << ") = (x+1)^" << n << ":" << endl;
    for (int i = n; i >= 0; i--) {
        double potencia = pow(x, i);
        double termino = coeficientes[i] * potencia;
        total += termino;
        cout << "Paso " << (n - i + 1) << ": " << coeficientes[i] << " * (" << x << "^" << i << ") = " 
             << coeficientes[i] << " * " << potencia << " = " << termino << endl;
    }
    cout << "Resultado final f(" << x << ") = " << total << endl;
}

int main() {
    int n;
    double x;

    cout << "--- Prueba Diagnostica: Problema 1 (UNEG) ---" << endl;
    cout << "Ingrese el valor de n (entero no negativo): ";
    cin >> n;

    if (n < 0) {
        cout << "Error: n debe ser no negativo." << endl;
        return 1;
    }

    auto inicio = chrono::high_resolution_clock::now();

    mostrarTriangulo(n);
    long long* coeficientes = genCoeficiente(n);
    muestraPol(coeficientes, n);

    cout << "\nIngrese el valor de x para evaluar el polinomio: ";
    cin >> x;
    calcPasos(coeficientes, n, x);

    auto fin = chrono::high_resolution_clock::now();
    
    chrono::duration<double, std::milli> duracion = fin - inicio;

    cout << "\n--------------------------------------------------" << endl;
    cout << "TIEMPO DE EJECUCION: " << fixed << setprecision(4) << duracion.count() << " ms" << endl;
    cout << "--------------------------------------------------" << endl;

    delete[] coeficientes;
    return 0;
}
