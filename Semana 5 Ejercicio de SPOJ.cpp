#include <iostream>
using namespace std;
#include <vector>
#include <utility>
/*/RKS - RK Sorting
A medida que el codigo recibe valores, si no ha recibido valores iguales a ese genera un par ordenado
(con el valor y la cantidad de ocurrencuas) que guarda en un nuevo arreglo de pares, y si ya se recibieron
valores iguales a ese, los busca en el arreglo de pares y le suma a la cuenta de ocurrencias. Luego de eso
ordena con quicksort el nuevo arreglo (por cantidad de ocurrencias) de mayor a menor, para luego imprimir
el resultado esperado.
/*/

class numeros{
  public:
    int valor;
    int cantidad;
    int posicion;
};

bool esta(vector<int> message, int i){
  for(int j=0; j<i; j++){
    if(message[i]==message[j]) return true;
  }
  return false;
}

int parte(vector<numeros > &A, int i, int n){
  int q, cont=0;
  numeros x,temp, igual;
  x = A[n];  //pivote
  q = i-1;
  for(int j=i;j<n;j++){
    if( A[j].cantidad >= x.cantidad){
      if(A[j].cantidad == x.cantidad){
        if(A[j].posicion < x.posicion){
          q++;
          temp = A[j]; A[j] = A[q]; A[q] = temp; // swap
        }
      }else{
        cont=0;
        q++;
        temp = A[j]; A[j] = A[q]; A[q] = temp; // swap
      }
    }
  }
  temp = A[n]; A[n] = A[q+1]; A[q+1] = temp; // swap
  return q+1;
}

void quicksort(vector<numeros > &A, int i, int n){
  int q;
  if(i < n){
    q = parte(A,i,n);
    quicksort(A,i,q-1);
    quicksort(A,q+1,n);
  }
}

int main() 
{
  int x, y, cont=0;
  pair<int,int> temp;
  cin >> x >> y;
  vector<int> message(x);
  vector<numeros > cuantos;
  for(int i=0; i<x; i++){
    cin >> message[i];
    if (esta(message,i)==false){
      numeros par;
      cont++; // cuenta cuantos elementos distintos hay, son y elementos.
      cuantos.resize(cont);
      par.valor=message[i]; par.cantidad=1; par.posicion=i;
      cuantos[cont-1] = par;
    }else{  //recibió un valor repetido, lo busca para sumarle a la cuenta.
      for(int j=0; j<cont;j++){   //busca hasta cont
        if (cuantos[j].valor == message[i]){ cuantos[j].cantidad++; break;}
      }
    }
  }
  //ordena
  quicksort(cuantos,0,cont-1);
  
  for(int i=0; i<cont; i++){
    for(int k=0; k<cuantos[i].cantidad; k++){
      cout << cuantos[i].valor <<" ";
    }
  }
  return 0;
}