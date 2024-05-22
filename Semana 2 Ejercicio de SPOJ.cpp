#include <iostream>
using namespace std;
#include <vector>
#include <utility>
//RKS - RK Sorting
// A medida que el codigo recibe valores, si no ha recibido valores iguales a ese genera 
//un par ordenado (con el valor y la cantidad de ocurrencuas) que guarda en un nuevo arreglo de pares, y si ya se 
//recibieron valores iguales a ese, los busca en el arreglo de pares y le suma a la cuenta de ocurrencias.
//Luego de eso ordena con bubblesort el nuevo arreglo (por cantidad de ocurrencias) de mayor a menor, para luego imprimir el resultado
//esperado

bool esta(vector<int> message, int i){
  for(int j=0; j<i; j++){
    if(message[i]==message[j]) return true;
  }
  return false;
}

int main() 
{
  int x, y, cont=0;
  pair<int,int> temp;
  cin >> x >> y;
  vector<int> message(x);
  vector<pair<int,int>> cuantos;
  for(int i=0; i<x; i++){
    cin >> message[i];
    if (esta(message,i)==false){
      pair<int,int> par;
      cont++; // cuenta cuantos elementos distintos hay.
      cuantos.resize(cont);
      par.first=message[i]; par.second=1;
      cuantos[cont-1] = par;
    }else{  //recibió un valor repetido, lo busca para sumarle a la cuenta.
      for(int j=0; j<cont;j++){
        if (cuantos[j].first == message[i]) cuantos[j].second++;
      }
    }
  }
  for(int i=0; i<cont; i++){  //ordena
    for(int j=cont-1; j>i; j--){
      if(cuantos[j].second > cuantos[j-1].second){
        temp = cuantos[j];
        cuantos[j]= cuantos[j-1];
        cuantos[j-1] = temp;
      }
    }
  }
  for(int i=0; i<cont; i++){
    for(int k=0; k<cuantos[i].second; k++){
      cout << cuantos[i].first << " ";
    }
  }
  return 0;
}
