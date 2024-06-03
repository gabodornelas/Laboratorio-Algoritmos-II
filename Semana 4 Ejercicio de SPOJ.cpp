#include <iostream>
using namespace std;
#include <vector>

/*/MATRMUL0 - Matrix Multiplication 2K
Utilizando vectores copiamos las matrices A y B, si n no es algúna potencia de 2, se busca (con busqueda binaria) la potencia de
2 más próxima en una ista de potencias de 2 y se rellenan con 0 las matrices desde n hasta esa potencia de 2. Luego implementamos
el algoritmo de Strassen (AporB) para obtener la multiplicación de A por B, y finalmente copiamos la matriz resultante de la
multiplicación en C.

Nota: SPOJ no me aceptó la solución por limite de tiempo a partir del test 3, probando por mi cuenta en ideone concluí que para n
entre 129 y 256 se tardaba aprox 5s, por lo tanto para números más grandes se excedía del tiempo. Sin embargo, sé que mi solución
resuelve el problema, aunque no en el tiempo estipulado.
Me gustaría saber cuál era la solución más eficiente y me disculpo por fallar esta semana :(.
/*/

//Algoritmo de Strassen
vector<vector<long long> > AporB(vector<vector<long long> > A, vector<vector<long long> > B, uint32_t n){
	if(n==1){		//caso base
  		vector<long long> Cf(1);
  		Cf[0]=A[0][0]*B[0][0];
  		vector<vector<long long> > C(1);
  		C[0]=Cf;
    		return C;
  	}else{				//Defino cuadrantes
  		vector<vector<long long> > A00(n/2), A01(n/2), A10(n/2), A11(n/2), B00(n/2), B01(n/2), B10(n/2), B11(n/2);
	  	vector<long long> A00f(n/2), A01f(n/2), A10f(n/2), A11f(n/2), B00f(n/2), B01f(n/2), B10f(n/2), B11f(n/2);
					//defino sumas
		vector<vector<long long> > S1(n/2), S2(n/2), S3(n/2), S4(n/2), S5(n/2), S6(n/2), S7(n/2), S8(n/2), S9(n/2), S10(n/2);
		vector<long long> S1f(n/2), S2f(n/2), S3f(n/2), S4f(n/2), S5f(n/2), S6f(n/2), S7f(n/2), S8f(n/2), S9f(n/2), S10f(n/2); 
		for(uint32_t i=0;i<n/2;i++){
			//Saca los 4 cuadrantes
			for(uint32_t j=0;j<n/2;j++){
				A00f[j] = A[i][j];		A01f[j] = A[i][j+n/2];
				A10f[j] = A[i+n/2][j];		A11f[j] = A[i+n/2][j+n/2];
				B00f[j] = B[i][j];		B01f[j] = B[i][j+n/2];
				B10f[j] = B[i+n/2][j];		B11f[j] = B[i+n/2][j+n/2];
			}
			A00[i] = A00f;		A01[i] = A01f;
			A10[i] = A10f;		A11[i] = A11f;
			B00[i] = B00f;		B01[i] = B01f;
			B10[i] = B10f;		B11[i] = B11f;
      			//Saca las sumas o restas
     			for(uint32_t j=0;j<n/2;j++){
				S1f[j] = B01[i][j] - B11[i][j];		S2f[j] = A00[i][j] + A01[i][j];
			        S3f[j] = A10[i][j] + A11[i][j];		S4f[j] = B10[i][j] - B00[i][j];
				S5f[j] = A00[i][j] + A11[i][j];		S6f[j] = B00[i][j] + B11[i][j];
				S7f[j] = A01[i][j] - A11[i][j];		S8f[j] = B10[i][j] + B11[i][j];
				S9f[j] = A00[i][j] - A10[i][j];		S10f[j] = B00[i][j] + B01[i][j];
			}
			S1[i] = S1f;	S2[i] = S2f;	S3[i] = S3f;	S4[i] = S4f;	S5[i] = S5f;
			S6[i] = S6f;	S7[i] = S7f;	S8[i] = S8f;	S9[i] = S9f;	S10[i] = S10f;
		}
			//Defino Ms
		vector<vector<long long> > M1(n/2), M2(n/2), M3(n/2), M4(n/2), M5(n/2), M6(n/2), M7(n/2);
		M1 = AporB(A00, S1, n/2);
		M2 = AporB(S2, B11, n/2);
		M3 = AporB(S3, B00, n/2);
		M4 = AporB(A11, S4, n/2);
		M5 = AporB(S5, S6, n/2);
		M6 = AporB(S7, S8, n/2);
		M7 = AporB(S9, S10, n/2);
		    //Defino la C resultante de unir de vuelta los 4 cuadrantes
    		vector<vector<long long> > C(n);
    		vector<long long> C1f(n), C2f(n);
   		for(uint32_t i=0;i<n/2;i++){
      			for(uint32_t j=0;j<n/2;j++){
			        C1f[j] = M5[i][j] + M4[i][j] + M6[i][j] - M2[i][j];
			        C1f[j+n/2] = M1[i][j] + M2[i][j];
			        C2f[j] = M3[i][j] + M4[i][j];
			        C2f[j+n/2] = M5[i][j] + M1[i][j] - M3[i][j] - M7[i][j];
			}
      			C[i] = C1f;
			C[i+n/2] = C2f;
    		}
    		return C;
	}
}
//busqueda binaria
uint32_t busqbin(vector<uint32_t> stall, int i, int j, uint32_t n){
	int mid;
  	if(i==j){
    		return i;
  	}else{  
    		mid=(i+j)/2;
    		if( (stall[mid]) < n ){
      			return busqbin(stall,mid+1,j,n);
		}else{
      			return busqbin(stall,i,mid,n);
    		}
  	}
}

int main() 
{
  uint32_t n, i, j, d1, p1, r1, m1, d2, p2, m2, r2, A[n][n], B[n][n];
  long long C[n][n], V[n];
  //here you need to read n, p1, d1, r1, m1, p2, d2, r2, m2 from input.
  cin >> n >> p1 >> d1 >> r1 >> m1 >> p2 >> d2 >> r2 >> m2;
  //done
  for (i=0; i<n; ++i)
    for (j=0; j<n; ++j) {
        d1 = d1 * p1 + r1;
        d2 = d2 * p2 + r2;
        A[i][j] = d1 >> (32 - m1);
        B[i][j] = d2 >> (32 - m2);
    }
  //here you need to calculate C=A*B
	//vector de números potencia de dos hasta 2048
  vector<uint32_t> potenciadedos(12);
  potenciadedos[0]=1;   potenciadedos[1]=2;   potenciadedos[2]=4;   potenciadedos[3]=8;   potenciadedos[4]=16;   potenciadedos[5]=32;
  potenciadedos[6]=64;   potenciadedos[7]=128;   potenciadedos[8]=256;   potenciadedos[9]=512;   potenciadedos[10]=1024;
  potenciadedos[11]=2048;
  
  uint32_t m = potenciadedos[busqbin(potenciadedos,0,11,n)];
  vector<vector<long long> > Am(m), Bm(m), Cm(m);
  vector<long long> Af(m), Bf(m);
	//se copia a los vectores A y B en los vectores Am y Bm
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      Af[j] = A[i][j];
      Bf[j] = B[i][j];
	}
    Bm[i] = Bf;
    Am[i] = Af;
  }
  for(i=0;i<m;i++){
  	Af[i] = 0;
  }
	//se rellena con filas de 0 de ser necesario
  for(i=n;i<m;i++){
    Am[i] = Af;
    Bm[i] = Af;
  }
  //Llamada al algoritmo de strassen
  Cm = AporB(Am,Bm,m);
	//Se copia Cm en C
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      C[i][j] = Cm[i][j];
    }
  }
  //done
  for (i=0; i<n; ++i) {
    V[i] = 0;
    for (j=0; j<n; ++j)
      V[i] ^= C[i][j];
  }
  //here you need to output V[0], V[1], ..., V[n-1], separated by spaces.
  for(uint32_t v=0;v<n;v++){
    cout << V[v]<<" ";
  }
  //done
  return 0;
}
