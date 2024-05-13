#include <iostream>
using namespace std;
#include <vector>

bool ocurrencias(vector<int> cards,int y, int z){  
  int cont;
  for(int j=0; j < y; j++){
    cont=1;
    for(int k=j+1; k < y; k++){
      if (cards[j] == cards[k]){
        cont=cont+1;
      }
      if (cont == z){
        return true;
      }
    }
  }
  return false;
}

int main() 
{
  int x; int y; int z;
  vector<int> cards;
  cin >> x;
  for(int i=0; i < x; i++){
    cin >> y >> z;
    cards.resize(y);
    for(int j=0; j < y; j++){
      cin >> cards[j];
    }
    if (ocurrencias(cards,y,z) == true){
      cout << z-1 << endl;
    }else{
      cout << y << endl;
    }
  }
    return 0;
}