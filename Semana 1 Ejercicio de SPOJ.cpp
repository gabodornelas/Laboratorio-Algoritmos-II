#include <iostream>
using namespace std;

int main() 
{
  int x;
  while(true){
    cin >> x;
    if (x != 42){
      cout << x << endl;
    }else{
      break;
    }
  }
    return 0;
}