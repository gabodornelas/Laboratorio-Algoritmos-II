#include <iostream>
using namespace std;
#include <vector>

/*/RKS - RK Sorting

Se crea la clase "numeros" que contiene valor, cantidad y posición de los valores en el arreglo original.

A medida que el codigo recibe valores, si no ha recibido valores iguales a ese genera un "numeros" (con el valor, la cantidad de
ocurrencias y la posición original) que guarda en un nuevo vector de "numeros", y si ya se recibieron valores iguales a ese, los
busca en el vector de "numeros" y le suma a la cuenta de ocurrencias. Luego de eso ordena con quicksort el nuevo arreglo (por
cantidad de ocurrencias) de mayor a menor, revisando que en los casos de cantidad de ocurrencias iguales, tengan prioridad las
posiciones más bajas (los que aparecen primero). Luego se imprime el resultado esperado.
/*/

class numeros{
  public:
    int valor;
    int cantidad;
    int posicion;
};
//revisa si el elemento ya fue recibido
bool esta(vector<int> message, int i){
  for(int j=0; j<i; j++){
    if(message[i]==message[j]) return true;
  }
  return false;
}
//particiona el arreglo con los mayores a la izquierda y los menores a la derecha, dando prioridad a las posiciones menores para
//los casos iguales
int parte(vector<numeros > &A, int i, int n){
  int q;
  numeros x,temp;
  x = A[n];  //pivote
  q = i-1;
  for(int j=i;j<n;j++){
    if( A[j].cantidad >= x.cantidad){        //cantidad mayor o igual
      if(A[j].cantidad == x.cantidad){       //cantidad igual
        if(A[j].posicion < x.posicion){      //posicion menor
          q++;
          temp = A[j]; A[j] = A[q]; A[q] = temp; // swap
        }
      }else{  //cantidad mayor
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
  cin >> x >> y;
  vector<int> message(x);
  vector<numeros > cuantos;
  numeros par;
  for(int i=0; i<x; i++){
    cin >> message[i];
    if (esta(message,i)==false){
      cont++; // cuenta cuantos elementos distintos hay.
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
  //imprime
  for(int i=0; i<cont; i++){
    for(int k=0; k<cuantos[i].cantidad; k++){
      cout << cuantos[i].valor <<" ";
    }
  }
  return 0;
}
