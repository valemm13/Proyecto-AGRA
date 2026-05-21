from sys import stdin
from heapq import heappush,heappop
INF = float('inf')

def norte(orientacion):
    abajo, arriba, norte, sur, este, oeste = orientacion
    return norte,sur,abajo,arriba,este,oeste

def sur(orientacion):
    abajo, arriba, norte, sur, este, oeste = orientacion
    return sur,norte,arriba,abajo,este,oeste

def este(orientacion):
    abajo, arriba, norte, sur, este, oeste = orientacion
    return este,oeste,norte,sur,abajo,arriba   


def oeste(orientacion):
    abajo, arriba, norte, sur, este, oeste = orientacion 
    return oeste,este,norte,sur,arriba,abajo
 

def dijkstra(grid, estadoInicial, A, B):
    dist = {}
    dist[estadoInicial] = 0
    pqueue = list()
    
    heappush(pqueue, (0, estadoInicial))

    while len(pqueue) != 0:
        du,u = heappop(pqueue)

        if(dist[u] == du):
            """for v,duv in G[u]:
                if du + duv < dist[v]:
                    dist[v] = du + duv
                    pred[u] = u
                    heappush(pqueue,(dist[v],v))"""

    return dist

def main():
    casos = int(stdin.readline())
    for caso in range(1,casos + 1):
        filas, columnas, A, B = map(int,stdin.readline().split())

        grid = []

        for i in range(filas):
            grid.append(stdin.readline().strip())

        orientacionInicial = (1, 6, 5, 4, 3, 2)
        oros = []
        posicionInicialCubo = ()
        carasOro = tuple(False for _ in range(6))

        for i in range(filas):
            for j in range(columnas):
                if grid[i][j] == "G":
                    oros.append((i,j))
                if grid[i][j] == "S":
                    posicionInicialCubo = (i,j)

        celdasOro = tuple(oros)

        estadoInicial = (posicionInicialCubo, orientacionInicial, carasOro, celdasOro)

        dijkstra(grid,estadoInicial,A,B)


""" FALTA!!!
1. Logica de rotacion del cubo
2. Logica intercambio de oro
3. Calculo de los costos dependiendo el movimiento
4. Condicion de parar cuando la celdasOro este vacia
"""