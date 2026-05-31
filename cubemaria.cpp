//Maria Isabel Solis Y Valerie Marmolejo Molina

#include <iostream>
#include <vector>
#include <string>

using namespace std;

//variables globales
int R, C; //filas y columnas del grid

struct state {
    int fila, col; //posicion del cubo en el grid
    int caras[6]; //caras del cubo
    bool oroEnCara[6]; //si la cara tiene oro o no 
    vector<pair<int, int>> oroEnGrid; //coordenadas del oro en el grid 



    bool operator<(const state other) const {
        bool ans = false; 
        bool diferencia = false; //para saber cuando no se sigue comparando

        //si aun no se ha encontrado la diferencia entonces se siguen comparando las variables del struct
        if (diferencia == false && fila != other.fila){
            ans = fila < other.fila;
            diferencia = true; //ya se encontro la diferencia entonces se detien la comparacion
        }
        if (diferencia == false && col != other.col){
            ans = col < other.col;
            diferencia = true;
        }
        for (int i = 0; i < 6; i++){
            if (diferencia == false && caras[i] != other.caras[i]){
                ans = caras[i] < other.caras[i];
                diferencia = true;
            }
        }
        for (int i = 0; i < 6; i++){
            if (diferencia == false && oroEnCara[i] != other.oroEnCara[i]){
                ans = oroEnCara[i] < other.oroEnCara[i];
                diferencia = true;
            }
        }
        if (diferencia == false){ 
            ans = oroEnGrid < other.oroEnGrid;
        }

        return ans;
    }
};

//movemos el cubo al norte
void moverNorte(state &s){
    int ans = s.caras[0]; //cara de abajo temporal 
    s.caras[0] = s.caras[2]; //la cara de abajo ahora es la de atras
    s.caras[2] = s.caras[1]; //la cara de atras ahora es la de arriba
    s.caras[1] = s.caras[3]; //la cara de arriba ahora es la de adelante 
    s.caras[3] = ans; //la cara de adelante ahora es la de abajo

    s.fila = s.fila - 1; //se mueve el cubo hacia el norte si el cuba antes estaba en la fila 5, si se mueve al norte pasa a estar en la fila 4

}

//movemos el cubo al sur
void moverSur(state &s){
    int ans = s.caras[0]; // cara de abajo temporal 
    s.caras[0] = s.caras[3]; // la cara de abajo ahora es la de adelante
    s.caras[3] = s.caras[1]; // la cara de adelante ahora es la de arriba
    s.caras[1] = s.caras[2]; // la cara de arriba ahora es la de atras
    s.caras[2] = ans; // la cara de atras ahora es la de abajo

    s.fila = s.fila + 1; //se mueve el cubo hacia el sur si el cuba antes estaba en la fila 5, si se mueve al sur pasa a estar en la fila 6


}

//movemos el cubo al este 
void moverEste(state &s){
    int ans = s.caras[0]; // cara de abajo temporal 
    s.caras[0] = s.caras[4]; // la cara de abajo ahora es la de la izquierda
    s.caras[4] = s.caras[1]; // la cara de la izquierda ahora es la de arriba
    s.caras[1] = s.caras[5]; // la cara de arriba ahora es la de la derecha
    s.caras[5] = ans; // la cara de la derecha ahora es la de abajo

    s.col = s.col + 1; //se mueve el cubo hacia el este si el cuba antes estaba en la columna 5, si se mueve al este pasa a estar en la columna 6

}

//movemos el cubo al oeste 
void moverOeste(state &s){
    int ans = s.caras[0]; // cara de abajo temporal 
    s.caras[0] = s.caras[5]; // la cara de abajo ahora es la de la derecha
    s.caras[5] = s.caras[1]; // la cara de la derecha ahora es la de arriba
    s.caras[1] = s.caras[4]; // la cara de arriba ahora es la de la izquierda
    s.caras[4] = ans; // la cara de la izquierda ahora es la de abajo

    s.col = s.col - 1; //se mueve el cubo hacia el oeste si el cuba antes estaba en la columna 5, si se mueve al oeste pasa a estar en la columna 4

}

//la funcion se asegura de que el cubo no se salga del grid dependiendo del tamaño de este R siendo filas y C columnas
bool esValido(int f, int c){
    if(f < 0 || f >= R || c < 0 || c >= C){
        return false;
    }
    return true;
}


int main(){

    int casos; 
    cin >> casos;

    cin >> R >> C; //filas y columnas del grid

    



}
