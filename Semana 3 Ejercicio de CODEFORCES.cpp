#include <iostream>
using namespace std;
#include <vector>
#include <utility>

/*/
B. Collecting Game
Se define la clase "as", con lo elementos "valor" (el valor del elemento del arreglo), "posicion" (la posición original del elemento en el arreglo) y "score" (luego de ordenar la lista,
score tendrá la suma de los elementos anteriores al elemento actual más el elemento actual). Si el score supera a 1.000.000.000, se deja como score a 1.000.000.000

Luego de recibir los valores, se ordena con mergesort, se le asigna como respuesta del último elemento, su posición, es decir, si son n elementos, el último supera a n-1 elementos,
y luego desde la posición n-1 hasta la posición 1, se verifica que el score del elemento actual sea distinto de 1.000.000.000, si no lo es, la resp del anterior será la misma que la
del elemento actual, se verifica que el valor del elemento actual sea distinto al valor del elemento anterior, si no lo es, la resp del anterior será la misma que la del elemento actual,
se verifica el score del elemento anterior y si este supera al valor del elemento actual, entonces la respuesta del anterior será la misma que la del elemento actual, si no, entonces la
respuesta del anterior será su posición. Las respuestas se guardan en otro arreglo en las mismas posiciones que tenían los elementos originalmente, para eso se asignó "posición".
Al final se recorre el arreglo de respuesta imprimiendo los resultados esperados.
/*/

class as{
  public:
    int valor;           //el valor del elemento del arreglo
    int posicion;        //la posición original del elemento en el arreglo
    long long score;     //la suma de los elementos anteriores al elemento actual (luego de ordenar la lista) más el elemento actual
};
 
void merge(vector<as > &stall, int ini, int fin, int med){
  int l=0, r=0;
  long long score=0;
  vector<as > izq(med-ini);
  vector<as > der(fin-med);
  for(int a=0;a<fin-ini;a++){
    if(a<(fin-med) ){
      der[a]=stall[med+a];
    }
    if(a<(med-ini) ){
      izq[a]=stall[ini+a];
    }
    if( (r<(fin-med)) and (l<(med-ini)) ){
      if(izq[l].valor < der[r].valor){
        stall[ini+a]=izq[l];
        l++;
      }else{
        stall[ini+a]=der[r];
        r++;
      }
    }else{
      if(l<(med-ini)){
        stall[ini+a] = izq[l];
        l++;
      }else{
        if(r<(fin-med)){
          stall[ini+a] = der[r];
          r++;
        }
      }
    }
   //En cada llamada a merge se asignan scores con los ordenes de los subarreglos, es decir, no necesariamente el orden final, pero no afectan el resultado final ya que se
   //cambia el score con cada llamada, por lo tanto cuando mezcle las 2 ultimas mitades dará como resultado la lista ordenada, y por lo tanto
   //cada elemento tendrá su score esperado
    score=score+stall[ini+a].valor;    
    if(score >= 1000000000){           //Si el score supera a 1.000.000.000, se deja como score a 1.000.000.000
      score=1000000000;
    }
    stall[ini+a].score=score;
  }
}
 
void mergesort(vector<as > &stall, int ini, int fin){
  int rango;
  if(fin-ini>1){
    mergesort(stall,ini,(ini+fin)/2);
    mergesort(stall,(ini+fin)/2,fin);
    merge(stall,ini,fin,(ini+fin)/2);
  }
}
 //Desde n-1 hasta 1, verifica el score del elemento anterior, retorna el vector respuesta
vector<int> removals(vector<as > stall, int n){
  vector<int> answer(n);
  answer[stall[n-1].posicion] = n-1;
  for(int y=n-1;y>0;y--){
    if(stall[y-1].score != 1000000000){   //caso base
      if(stall[y].valor != stall[y-1].valor){     //caso base
        if( (stall[y-1].score) >= stall[y].valor ){
          answer[stall[y-1].posicion] = answer[stall[y].posicion];
        }else{
          answer[stall[y-1].posicion] = y-1;
        }
      }else{
        answer[stall[y-1].posicion] = answer[stall[y].posicion];
      }
    }else{
      answer[stall[y-1].posicion] = answer[stall[y].posicion];
    }
  }
  return answer;
}
 
int main() 
{
  int t,n,x;
  cin >> t;
  as par;
  for(int i=0;i<t;i++){
    cin >> n;
    vector<as > pares(n);
    for(int j=0;j<n;j++){
      cin >> par.valor;
      par.posicion=j;
      par.score=par.valor;   //score momentáaneo
      pares[j]=par;
    }
    mergesort(pares,0,n);    //ordena
    vector<int> resp(n);
    resp=removals(pares,n);
    for(int j=0;j<n;j++){
      cout<<resp[j]<<" ";
    }
    cout<<endl;
  }
  return 0;
}
