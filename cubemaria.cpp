#include <iostream>
#include <set>
#include <queue>
#include <array>
#include <map>
#include <vector>
#include <climits>
using namespace std;

// Funciones para el movimiento del cubo
array<int,6> norte(array<int,6> orientacion){
    int abajo=orientacion[0], arriba=orientacion[1], nor=orientacion[2], 
        sur=orientacion[3], este=orientacion[4], oeste=orientacion[5];
    return {nor, sur, abajo, arriba, este, oeste};
}

array<int,6> sur(array<int,6> orientacion){
    int abajo=orientacion[0], arriba=orientacion[1], nor=orientacion[2], 
        sur=orientacion[3], este=orientacion[4], oeste=orientacion[5];
    return {sur, nor, arriba, abajo, este, oeste};
}

array<int,6> este(array<int,6> orientacion){
    int abajo=orientacion[0], arriba=orientacion[1], nor=orientacion[2], 
        sur=orientacion[3], este=orientacion[4], oeste=orientacion[5];
    return {este, oeste, nor, sur, abajo, arriba};
}

array<int,6> oeste(array<int,6> orientacion){
    int abajo=orientacion[0], arriba=orientacion[1], nor=orientacion[2], 
        sur=orientacion[3], este=orientacion[4], oeste=orientacion[5];
    return {oeste, este, nor, sur, arriba, abajo};
}

// Estado
struct state{
    pair<int, int> posicion;
    array<int,6> orientacion;
    int carasOro;
    int celdasOro;
};

// struct para comparar los estados en el mapa
struct classComp{
    bool operator()(const state& est1, const state& est2) const{

        bool ans = est1.celdasOro < est2.celdasOro;
        if(est1.posicion != est2.posicion)
            ans = est1.posicion < est2.posicion;
        if(est1.orientacion != est2.orientacion)
            ans = est1.orientacion < est2.orientacion;
        if(est1.carasOro != est2.carasOro)
            ans = est1.carasOro < est2.carasOro;
        return ans;
    }
};

// Functor para la priority queue que se utilizara en dijkstra
struct cmp{
    bool operator()(const pair<int,state>& a, const pair<int,state>& b) const{
        return a.first > b.first; 
    }
};

map<state, int, classComp> dist;

map<state, int, classComp> dijkstra(vector<string> grid, state estadoInicial, int A, int B){
    dist[estadoInicial] = 0;
    vector<pair<int,int>> direccion = {{-1,0}, {0,-1},{1,0},{0,1}};
    priority_queue<pair<int,state>, vector<pair<int,state>>, cmp> pq;
    pq.push({0,estadoInicial});

    while(!pq.empty()){
        int du = pq.top().first;
        state estadoActual = pq.top().second;
        pq.pop();

        if(dist[estadoActual] == du){
            for(int d = 0; d < 4; d++){
                int nuevor = estadoActual.posicion.first + direccion[d].first;
                int nuevoc = estadoActual.posicion.second + direccion[d].second;

                int nr = estadoActual.posicion.first;
                int nc = estadoActual.posicion.second;
                array<int,6> nuevaOrientacion; 

                if (0 <= nuevor && nuevor < grid.size() && 0 <= nuevoc && nuevoc < grid[0].size()){
                    nr = nuevor;
                    nc = nuevoc;

                    if(d == 0) 
                        nuevaOrientacion = norte(estadoActual.orientacion);
                    else if(d == 1) 
                        nuevaOrientacion = oeste(estadoActual.orientacion);
                    else if(d == 2) 
                        nuevaOrientacion = sur(estadoActual.orientacion);
                    else 
                        nuevaOrientacion = este(estadoActual.orientacion);

                    int caraAbajo = nuevaOrientacion[0];

                    bool tieneOroCara = (estadoActual.carasOro & (1 << caraAbajo));
                    bool tieneOroCelda = (estadoActual.celdasOro & (1 << (nr*grid[0].size() + nc)));
                    
                    int costo = 0;

                    int nuevasCarasOro = estadoActual.carasOro;
                    int nuevasCeldasOro = estadoActual.celdasOro;

                    if(tieneOroCara && !tieneOroCelda){
                        costo = A;
                        nuevasCarasOro ^= (1 << caraAbajo); // Hacer corrimiento de bits para quitar el oro de la cara
                        nuevasCeldasOro ^= (1 << (nr*grid[0].size() + nc)); // Hacer corrimiento de bits para poner la celda en 1
                    }
                    else if(!tieneOroCara && tieneOroCelda){
                        costo = B;
                        nuevasCarasOro ^= (1 << caraAbajo); // Hacer corrimiento de bits para poner el oro en la cara
                        nuevasCeldasOro ^= (1 << (nr*grid[0].size() + nc)); // Hacer corrimiento de bits para quitar la celda del oro
                
                    }
                    else{
                        costo = A;
                    }

                    state nuevoEstado = {{nr,nc}, nuevaOrientacion, nuevasCarasOro, nuevasCeldasOro};

                    if(dist.find(nuevoEstado) == dist.end() || du + costo < dist[nuevoEstado]){
                        dist[nuevoEstado] = du + costo;
                        pq.push({du + costo, nuevoEstado});
                    }
                    
                }
            }
        }
    }
    return dist;
}

int main(){

    int casos;
    cin >> casos;
    dist.clear();
    
    for(int i = 0; i < casos; i++){
        int filas, columnas, A, B;
        cin >> filas >> columnas >> A >> B;

        vector<string> grid(filas);

        for(int j = 0; j < filas; j++){
            cin >> grid[j];
        }

        array<int,6> orientacionInicial = {1, 6, 5, 4, 3, 2};
        int carasOro = 0;
        int celdasOro = 0;
        pair<int,int> posicionInicial;

        for(int i = 0; i < filas; i++){
            for(int j = 0; j < columnas; j++){
                if(grid[i][j] == 'G')
                    celdasOro |= (1 << (i * columnas + j));
                if(grid[i][j] == 'S')
                    posicionInicial = {i,j};
            }
        }
        
        state estadoInicial = {posicionInicial, orientacionInicial, carasOro, celdasOro};
        map<state, int, classComp> dist = dijkstra(grid, estadoInicial, A, B);

        int ans = INT_MAX;
        for(map<state,int,classComp>:: iterator it = dist.begin(); it != dist.end(); it++){
            if(it->first.celdasOro == 0){
                if(it->second < ans){
                    ans = it->second;
                }
            }
        }

        if(ans != INT_MAX)
            printf("Screw you guys, I got all the gold for %d cost!", ans);
        else
            printf("Oh my God, they killed Kenny!");
        
        printf("\n");
    }
    return 0;
}