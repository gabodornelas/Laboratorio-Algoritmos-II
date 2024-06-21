#include <iostream>
using namespace std;

struct Elem{
  int x;
  Elem *next;
  Elem *prev;
  Elem(){
    x = 0;
  }
};

struct Cola{
  Elem *pri;
  Cola(){
    pri = NULL;
  }
  void encolar(int y){
    Elem *nuevo_elem = new Elem;
    nuevo_elem -> x = y;
    if(pri == NULL){
      pri = nuevo_elem;
      pri -> next = pri;
      pri -> prev = pri;
    }else{
      pri -> prev -> next = nuevo_elem;
      nuevo_elem -> prev = pri -> prev;
      pri -> prev = nuevo_elem;
      nuevo_elem -> next = pri;
    }
  }
  void desencolar(){
    if(pri != NULL){
      if(pri -> next != pri){
        pri -> prev -> next = pri -> next;
        pri -> next -> prev = pri -> prev;
        pri = pri -> next;
      }else{
        pri = NULL;
      }
    }
  }
};

int main() 
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t, caso, ax;
  Cola c;
  cin >> t;
  for(int i=0;i<t;i++){
    cin >> caso;
    if(caso==1){
      cin >> ax;
      c.encolar(ax);
    }else if(caso==2){
        c.desencolar();
        }else if(caso==3){
          if(c.pri != NULL) cout << c.pri -> x << "\n";
          else cout << "Empty!\n";
          }
  }
  return 0;
}























