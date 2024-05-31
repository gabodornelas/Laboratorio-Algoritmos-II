#include <iostream>
using namespace std;
#include <vector>
#include <utility>
 
class as{
  public:
    int valor;
    int posicion;
    long long score;
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
    score=score+stall[ini+a].valor;
    if(score >= 1000000000){
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
 
vector<int> removals(vector<as > stall, int n){
  vector<int> answer(n);
  answer[stall[n-1].posicion] = n-1;
  for(int y=n-1;y>0;y--){
    if(stall[y-1].score != 1000000000){
      if(stall[y].valor != stall[y-1].valor){
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
      par.score=par.valor;
      pares[j]=par;
    }
    mergesort(pares,0,n);
    vector<int> resp(n);
    resp=removals(pares,n);
    for(int j=0;j<n;j++){
      cout<<resp[j]<<" ";
    }
    cout<<endl;
  }
  return 0;
}