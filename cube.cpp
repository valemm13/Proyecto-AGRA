#include <iostream>
#include <climits>
#include <queue>
#include <map>
#include <vector>
using namespace std;

// Funcion que hace la rotacion dependiendo la direccion
int rotacion(int carasOro, int movimiento[6]){
    int nuevoArray[6];
    int arrayOriginal[6];

    int x = carasOro;
    for(int i = 0; i < 6; i++){
        arrayOriginal[i] = x % 2;
        x /= 2;
    }

    for(int i = 0; i < 6; i++){
        if(movimiento[i] != -1){
            nuevoArray[movimiento[i]] = arrayOriginal[i];
        }else{
            nuevoArray[i] = arrayOriginal[i];
        }
    }

    int ans = 0;
    for(int i = 5; i >= 0; i--){
        ans = ans * 2 + nuevoArray[i];
    }

    return ans;
}

// Funciones para el movimiento del cubo
int norte(int carasOro){ 
    int movimientoNorte[6] = {3,2,0,1,-1,-1};
    int ans = rotacion(carasOro,movimientoNorte);
    return ans;
}

int sur(int carasOro){ 
    int movimientoSur[6] = {2,3,1,0,-1,-1};
    int ans = rotacion(carasOro,movimientoSur);
    return ans;
}

int este(int carasOro){
    int movimientoEste[6] = {5,4,-1,-1,0,1};
    int ans = rotacion(carasOro,movimientoEste);

    return ans;

}

int oeste(int carasOro){ 
    int movimientoOeste[6] = {4,5,-1,-1,1,0};
    int ans = rotacion(carasOro,movimientoOeste);

    return ans;
}

// Estado
struct state{
    pair<int, int> posicion;
    int carasOro;
    int celdasOro;
};

// struct para comparar los estados en el mapa
struct classComp{
    bool operator()(const state& est1, const state& est2) const {
        bool ans = est1.celdasOro < est2.celdasOro;
        if(est1.posicion != est2.posicion)
            ans = est1.posicion < est2.posicion;
        else if(est1.carasOro != est2.carasOro)
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

int dijkstra(vector<string> &grid, state &estadoInicial, int A, int B){
    map<state, int, classComp> dist;
    dist[estadoInicial] = 0;
    vector<pair<int,int>> direccion = {{-1,0}, {0,-1},{1,0},{0,1}};
    priority_queue<pair<int,state>, vector<pair<int,state>>, cmp> pq;
    pq.push({0,estadoInicial});
    bool flag = false;
    int costoFinal = INT_MAX;

    while(!pq.empty() && !flag){
        int du = pq.top().first;
        state estadoActual = pq.top().second;
        pq.pop();

        if(dist[estadoActual] == du){
            if(estadoActual.celdasOro == 0 && estadoActual.carasOro == 63){
                flag = true;
                costoFinal = du;
            }
            else{
                for(int d = 0; d < 4; d++){
                    int nuevor = estadoActual.posicion.first + direccion[d].first;
                    int nuevoc = estadoActual.posicion.second + direccion[d].second;

                    int nr = estadoActual.posicion.first;
                    int nc = estadoActual.posicion.second;
                    int nuevaOrientacion; 

                    if (0 <= nuevor && nuevor < grid.size() && 0 <= nuevoc && nuevoc < grid[0].size()){
                        nr = nuevor;
                        nc = nuevoc; 

                        if(d == 0) 
                            nuevaOrientacion = norte(estadoActual.carasOro);
                        else if(d == 1) 
                            nuevaOrientacion = oeste(estadoActual.carasOro);
                        else if(d == 2) 
                            nuevaOrientacion = sur(estadoActual.carasOro);
                        else 
                            nuevaOrientacion = este(estadoActual.carasOro);

                        int costo = 0;
                        int nuevasCeldasOro = estadoActual.celdasOro;
                        int nuevasCarasOro = nuevaOrientacion;

                        bool celdaTiene = (estadoActual.celdasOro & (1 << (nr * grid[0].size() + nc)));
                        bool caraTiene = (nuevasCarasOro & 1);

                        if(celdaTiene && !caraTiene){
                            costo = B;
                            nuevasCeldasOro = nuevasCeldasOro ^ (1 << (nr * grid[0].size() + nc));
                            nuevasCarasOro = (nuevasCarasOro ^ 1);
                        }
                        else if(!celdaTiene && caraTiene){
                            costo = A;
                            nuevasCeldasOro = nuevasCeldasOro ^ (1 << (nr * grid[0].size() + nc));
                            nuevasCarasOro = (nuevasCarasOro ^ 1);
                        }
                        else{
                            costo = A;
                        }

                        state nuevoEstado = {{nr,nc}, nuevasCarasOro, nuevasCeldasOro};

                        if(dist.find(nuevoEstado) == dist.end() || du + costo < dist[nuevoEstado]){
                            dist[nuevoEstado] = du + costo;
                            pq.push({du + costo, nuevoEstado});
                        }
                        
                    }
                }
            }
        }
    }
    return costoFinal;
}

int main(){

    int casos;
    cin >> casos;

    for(int i = 0; i < casos; i++){
        int filas, columnas, A, B;
        cin >> filas >> columnas >> A >> B;

        vector<string> grid(filas);

        for(int j = 0; j < filas; j++){
            cin >> grid[j];
        }

        int carasOro = 0;
        int celdasOro = 0;
        pair<int,int> posicionInicial;

        for(int i = 0; i < filas; i++){
            for(int j = 0; j < columnas; j++){
                if(grid[i][j] == 'G')
                    celdasOro = celdasOro ^ (1 << (i * columnas + j));
                if(grid[i][j] == 'S')
                    posicionInicial = {i,j};
            }
        }
        
        state estadoInicial = {posicionInicial, carasOro, celdasOro};
        int costo = dijkstra(grid, estadoInicial, A, B);

        if(costo != INT_MAX)
            printf("Screw you guys, I got all the gold for %d cost!", costo);
        else
            printf("Oh my God, they killed Kenny!");
        
        printf("\n");
    }
    return 0;
}