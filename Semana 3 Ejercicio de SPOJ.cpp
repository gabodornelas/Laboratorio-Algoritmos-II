#include <iostream>
using namespace std;
#include <vector>

void merge(vector<int> &stall, int ini, int fin, int med){
  int l=0, r=0;
  vector<int> izq(med-ini);
  vector<int> der(fin-med);
  for(int a=0;a<fin-ini;a++){
    if(a<(fin-med) ){
      der[a]=stall[med+a];
    }
    if(a<(med-ini) ){
      izq[a]=stall[ini+a];
    }
    if( (r<(fin-med)) and (l<(med-ini)) ){
      if(izq[l] < der[r]){
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
  }
}

void mergesort(vector<int> &stall, int ini, int fin){
  int rango;
  if(fin-ini>1){
    mergesort(stall,ini,(ini+fin)/2);
    mergesort(stall,(ini+fin)/2,fin);
    merge(stall,ini,fin,(ini+fin)/2);
  }
}

int busqbin(vector<int> stall, int i, int j, int med){
  int mid;
  if(i==j){
    return i;
  }else{  
    mid=(i+j)/2;
    if( (stall[mid]-stall[0]) < med ){
      return busqbin(stall,mid+1,j,med);
    }else{
      return busqbin(stall,i,mid,med);
    }
  }
}

bool cabe(vector<int> stall, int i, int n, int med, int c){
  int cont=2, fix=stall[i];
  for(int y=i+1;y<n;y++){
    if( (stall[y] - fix) >= med){
      cont++;
      fix=stall[y];
      if(cont==c){
        return true;
      }
    }
  }
  return false;
}

int maxmin(vector<int> stall, int n, int c, int max, int min){
  int point, resp=min, med;
  while(min<max){
    med=(min+max)/2;
    point = busqbin(stall,0,n-1,med);
    if(cabe(stall,point,n,med,c)){
      min=med+1;
      resp=med;
    }else{
      max=med;
    }
  }
  return resp;
}

int maximo(vector<int> stall, int n, int c){
  if( (stall[n-c+1]-stall[0]) < (stall[n-1]-stall[c-2]) ){
    return (stall[n-c+1]-stall[0]);
  }else{
    return (stall[n-1]-stall[c-2]);
  }
}

int minimo(vector<int> stall, int n, int max){
  int min=max;
  for(int m=1;m<n;m++){
    if( (stall[m]-stall[m-1]) < min){
      min=stall[m]-stall[m-1];
    }
  }
  return min;
}

int main() 
{
  int x,n,c,max,min;
  cin >> x;
  for(int i=0;i<x;i++){
    cin >> n >> c;
    vector<int> stall(n);
    for(int j=0; j<n; j++){
      cin >> stall[j];
    }
    mergesort(stall,0,n);
    if(c==2){
      cout<< stall[n-1] - stall[0] <<endl;
    }else{
      min=minimo(stall,n,stall[n-1]);
      if(c==n){
        cout<<min<<endl;
      }else{
        max = maximo(stall,n,c)+1;
        cout << maxmin(stall,n,c,max,min) << endl;
      }
    }
  }
  return 0;
}