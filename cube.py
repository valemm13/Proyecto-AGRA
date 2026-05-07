from sys import stdin

def main():
    casos = int(stdin.readline())
    for caso in range(1,casos + 1):
        filas, columnas, A, B = map(int(stdin.readline().split()))

        grid = []

        for i in range(filas):
            grid.append(stdin.readline().strip())