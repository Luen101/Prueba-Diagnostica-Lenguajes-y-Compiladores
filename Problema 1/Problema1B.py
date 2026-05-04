import time
from math import pow

def mostrar_triangulo(n):
    print(f"\nTriangulo de Pascal (niveles 0 a {n}):")
    for i in range(n + 1):
        fila = [0] * (i + 1)
        print(' ' * ((n - i) * 2), end='')
        for j in range(i + 1):
            if j == 0 or j == i:
                fila[j] = 1
            else:
                val = 1
                for k in range(1, j + 1):
                    val = val * (i - k + 1) // k
                fila[j] = val
            print(f"{fila[j]:4}", end='')
        print(f"  | (n={i})")

def gen_coeficiente(n):
    coeficientes = [0] * (n + 1)
    for i in range(n + 1):
        val = 1
        for j in range(1, i + 1):
            val = val * (n - j + 1) // j
        coeficientes[i] = val
    return coeficientes

def muestra_pol(coeficientes, n):
    print("\nResultado del polinomio:")
    print(f"(x+1)^{n} = ", end='')
    for i in range(n, -1, -1):
        if i < n:
            print(" + ", end='')
        if i == 0:
            print(coeficientes[i], end='')
        elif i == 1:
            print(f"{coeficientes[i]}x", end='')
        else:
            print(f"{coeficientes[i]}x^{i}", end='')
    print()

def calc_pasos(coeficientes, n, x):
    total = 0.0
    print(f"\nPasos del calculo para f({x}) = (x+1)^{n}:")
    for i in range(n, -1, -1):
        potencia = pow(x, i)
        termino = coeficientes[i] * potencia
        total += termino
        print(f"Paso {n - i + 1}: {coeficientes[i]} * ({x}^{i}) = {coeficientes[i]} * {potencia} = {termino}")
    print(f"Resultado final f({x}) = {total}")

def main():
    print("--- Prueba Diagnostica: Problema 1 (UNEG) ---")
    try:
        n = int(input("Ingrese el valor de n (entero no negativo): "))
    except ValueError:
        print("Error: Debe ingresar un numero entero.")
        return
    
    if n < 0:
        print("Error: n debe ser no negativo.")
        return 1

    inicio = time.perf_counter()

    mostrar_triangulo(n)
    coeficientes = gen_coeficiente(n)
    muestra_pol(coeficientes, n)

    x = float(input("\nIngrese el valor de x para evaluar el polinomio: "))
    calc_pasos(coeficientes, n, x)

    fin = time.perf_counter()
    duracion = (fin - inicio) * 1000

    print("\n--------------------------------------------------")
    print(f"TIEMPO DE EJECUCION: {duracion:.4f} ms")
    print("--------------------------------------------------")

if __name__ == "__main__":
    main()

