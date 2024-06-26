#include <iostream>
using namespace std;
/*/
STACKEZ - Easy Stack
Se implementaron las estructuras elemento (con valor (inicializado en 0) y apuntador al siguiente (inicializado en nulo)) y cola (con un
primer elemento inicializado nulo, y los procedimientos, usando lista simplemente enlazada, de apilar (ubicando elementos al tope de la pila)
y desapilar (quitando el elemento del tope de la pila y eliminandolo) ). Luego, dependiendo del caso, 1, 2 o 3, se apila, desapila o imprime
el velor del primer elemento de la pila.
/*/

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
    if(pri == NULL){  // Pila Vacía
      pri = nuevo_elem;
    }else{
      nuevo_elem -> next = pri;
      pri = nuevo_elem;
    }
  }
  void desapilar(){
    if(pri != NULL){
      Elem *pointer = pri;
      pri = pri -> next;
      delete pointer;
    }
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
