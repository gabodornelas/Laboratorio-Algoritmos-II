#include <iostream>
using namespace std;

struct Elem{
  int x;
  Elem *next;
  Elem(){
    x = 0;
    next = NULL;
  }
};

struct Pila{
  Elem *pri;
  Pila(){
    pri = NULL;
  }
  void apilar(int y){
    Elem *nuevo_elem = new Elem;
    nuevo_elem -> x = y;
    if(pri == NULL){
      pri = nuevo_elem;
    }else{
      nuevo_elem -> next = pri;
      pri = nuevo_elem;
    }
  }
  void desapilar(){
    if(pri != NULL)
      pri = pri -> next;
  }
};

int main() 
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t, caso, ax;
  Pila c;
  cin >> t;
  for(int i=0;i<t;i++){
    cin >> caso;
    if(caso==1){
      cin >> ax;
      c.apilar(ax);
    }else if(caso==2){
        c.desapilar();
        }else if(caso==3){
          if(c.pri != NULL) cout << c.pri -> x << "\n";
          else cout << "Empty!\n";
          }
  }
  return 0;
}