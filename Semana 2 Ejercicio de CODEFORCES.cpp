#include <iostream>
using namespace std;
#include <vector>
//A. Sasha and the Beautiful Array
//Luego de recibir todos los valores, se ordenan de menor a mayor usando bubble sort y luego se hace una suma para determinar la "belleza" del arreglo.
int main() 
{
  int x,y,temp,suma;
  cin >> x;
  vector<int> arreglo;
  for(int k=0;k<x;k++){
    cin >> y;
    arreglo.resize(y);
    for(int m=0;m<y;m++){
      cin >> arreglo[m];
    }
    for(int i=0; i<y; i++){
      for(int j=y-1; j>i; j--){
        if(arreglo[j] < arreglo[j-1]){
          temp = arreglo[j];
          arreglo[j]= arreglo[j-1];
          arreglo[j-1] = temp;
        }
      }
    }
    suma=0;
    for(int g=1;g<y;g++){
      suma=suma + arreglo[g] - arreglo[g-1];
    }
    cout << suma << endl;
  }
  return 0;
}
