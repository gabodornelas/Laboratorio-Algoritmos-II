#include <iostream>
using namespace std;
/*/
BSEARCH1 - Binary search
Se implementaron la estructura Nodo (con valor "x", posicion, color, apuntador a la izquierda, a la derecha y al padre y
sus respectivas inicializiaciones) y la clase Arbol, un arbol binario rojo-negro (con apuntador al nodo raiz y la
inicializacion, así como las funciones rotacion izquierda, rotacion derecha, revision, insertar y buscar)
/*/
struct Nodo{
  int x, posicion;    //la posicion es la del orden en que se resive el valor
  string color;
  Nodo *izq;
  Nodo *der;
  Nodo *papa;
  Nodo(){
    x = 0;
    color = "rojo";
    izq = NULL;
    der = NULL;
    papa = NULL;
  }
};

class Arbol{
  public:
    Nodo *raiz;
    Arbol(){
      raiz = NULL;
    }
  void rotacionizq(Nodo *fix){
    if(fix -> papa -> papa != NULL){    //Se chequea si el abuelo no es nulo
      if(fix -> papa -> papa -> izq == fix -> papa)    fix -> papa -> papa -> izq = fix;
      if(fix -> papa -> papa -> der == fix -> papa)    fix -> papa -> papa -> der = fix;
    }
    fix -> papa -> der = fix -> izq;
    //Se chequea que el hijo izquierdo de fix no es nulo
    if(fix -> izq != NULL)    fix -> izq -> papa = fix -> papa;
    fix -> izq = fix -> papa;
    Nodo *abuelo = fix -> papa -> papa;
    fix -> papa -> papa = fix;
    fix -> papa = abuelo;
    fix -> color = "negro";
    fix -> izq -> color = "rojo";
  }
  void rotacionder(Nodo *fix){
    if(fix -> papa -> papa != NULL){	//Se chequea si el abuelo no es nulo
      if(fix -> papa -> papa -> izq == fix -> papa)    fix -> papa -> papa -> izq = fix;
      if(fix -> papa -> papa -> der == fix -> papa)    fix -> papa -> papa -> der = fix;
    }
    fix -> papa -> izq = fix -> der;
    //Se chequea que el hijo derecho de fix no es nulo
    if(fix -> der != NULL)    fix -> der -> papa = fix -> papa;
    fix -> der = fix -> papa;
    Nodo *abuelo = fix -> papa -> papa;
    fix -> papa -> papa = fix;
    fix -> papa = abuelo;
    fix -> color = "negro";
    fix -> der -> color = "rojo";
    
  }
  void revision(Nodo *ult){
    Nodo *abuelo;
    while( (ult != raiz) and (ult -> papa != raiz) ){
      abuelo = ult -> papa -> papa;
      if(ult -> papa -> color == "rojo"){	//El papa es rojo
        if( ( (abuelo -> izq != NULL) and (abuelo -> izq -> color == "rojo") ) and ( (abuelo -> der != NULL) and (abuelo -> der -> color == "rojo") ) ){
          //El papa y el tio son no nulos y son rojos
          abuelo -> der -> color = "negro";
          abuelo -> izq -> color = "negro";
          if(abuelo != raiz)
            abuelo -> color = "rojo";
          ult = abuelo;
        }else{	//El tio es nulo o es negro
          if(ult -> papa == abuelo -> der){  //El papa es hijo derecho
            if(ult -> papa -> der == ult){ // ult es hijo derecho. Rotacion simple izq
              rotacionizq(ult -> papa);
              if(abuelo == raiz)    raiz = ult->papa;   //Cambia la raiz
            }else{ // ult es hijo izquierdo. Rotacion doble izq
              rotacionder(ult);
              rotacionizq(ult);
              if(abuelo == raiz)    raiz = ult; //Cambia la raiz
            }
          }else{	//El papa es hijo izquierdo
            if(ult -> papa -> izq == ult){ // ult es hijo izquierdo. Rotacion simple der
              rotacionder(ult -> papa);
              if(abuelo == raiz)    raiz = ult->papa;  //Cambia la raiz
            }else{ // ult es hijo derecho. Rotacion doble der
              rotacionizq(ult);
              rotacionder(ult);
              if(abuelo == raiz)    raiz = ult;  //Cambia la raiz
            }
          }
          return;
        }
      }else return;
    }
  }
  void insertar(int y, int pos){
    Nodo *nuevo_nodo = new Nodo;
    Nodo *padre;
    Nodo *aux = raiz;
    nuevo_nodo -> x = y;
    nuevo_nodo -> posicion = pos;
    if(raiz == NULL){   // Arbol vacío
      raiz = nuevo_nodo;    raiz -> color = "negro";
    }else{
      while(aux != NULL){
        padre = aux;
        if(nuevo_nodo -> x < aux -> x)    aux = aux -> izq;
        //Si son iguales se coloca a la derecha
        else    aux = aux -> der;
      }
      nuevo_nodo -> papa = padre;
      if(nuevo_nodo -> x < padre -> x)    nuevo_nodo -> papa -> izq = nuevo_nodo;
      else      nuevo_nodo -> papa -> der = nuevo_nodo;
      revision(nuevo_nodo);
    }
  }
  int find(Nodo *aux, int y){
    int resp;
    while(aux != NULL){
      if(aux -> x > y){
        aux = aux -> izq;
      }else{
        if(aux -> x < y){
          aux = aux -> der;
        }else{
          resp = find(aux->izq,y);	//Se chequea si y esta repetido, en tal caso estara a la izquierda
          if(resp == -1) 
            return aux -> posicion;
          else return resp;  
        }
      }
    }
    return -1;  //No lo encontro
  }
};

int main() 
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, q, val, i;
  Arbol tree;
  cin >> n >> q;
  for(i=0;i<n;i++){
    cin >> val;
    tree.insertar(val,i);
  }
  for(i=0;i<q;i++){
    cin >> val;
    cout << tree.find(tree.raiz,val) << "\n";
  }
  return 0;
}