#include <iostream>
#include <vector>

using namespace std;

int calcularPrim(int ult, vector<int> &v,vector<vector<int>> &m2) {
    int res = 0;
    int ultVal = v[ult];
    for (int i = 0; i < ult; i++) {
        res = res + abs(ultVal - v[i]);
    }
    return res;
}

void calcular(int ult,int actual, vector<int> &v,vector<vector<int>> &m2) {
    int res = 0;
    int ultVal = v[ult];
    int actualVal = v[actual];
    for (int i = ult; i < actual; i++) {
        int temp1 = abs(ultVal - v[i]);
        int temp2 = abs(actualVal - v[i]);
        res = res + min(temp1,temp2);
    }
    m2[ult][actual] = res;
}


int calcularUlt(int ult, vector<int> &v,vector<vector<int>> &m2) {
    int res = 0;
    int ultVal = v[ult];
    for (int i = ult; i < v.size(); i++) {
        res = res + abs(ultVal - v[i]);
    }
    return res;
}




int distribuir(int i,int ult, int &N, int K, int &Kinicial, vector<int> &V, vector<vector<vector<int>>> &m,vector<vector<int>> &m2,vector<int> &ubs){
    if(Kinicial == 1){
        int temp1 = calcularPrim(N/2,V,m2);
        int temp2 = calcularUlt(N/2,V,m2);
        return temp1 + temp2;
    }
    else if((N-i)<K) {
        //int a = std::numeric_limits<int>::max();
        int termin = 10000000;
        return termin;
    }
    else if(K == Kinicial){
        int temp1 = calcularPrim(i,V,m2);
        int noPonerla = distribuir(i+1,ult,N,K,Kinicial,V,m,m2,ubs);
        int ponerla = temp1 + distribuir(i+1,i,N,K-1,Kinicial,V,m,m2,ubs);
        ubs[0] = V[i];
        return min(ponerla,noPonerla);
    }
    else if(K == 1 && i < N){
        int temp1 = calcularUlt(i,V,m2);
        if(m2[ult][i] == -1){
            calcular(ult,i,V,m2);
        }
        int noPonerla = distribuir(i+1,ult,N,K,Kinicial,V,m,m2,ubs);
        int ponerla = m2[ult][i] + temp1;
        if(m[i][K][ult] != -1){
            m[i][K][ult] = min(min(ponerla,noPonerla),m[i][K][ult]);
        }
        if(m[i][K][ult] == -1){
            m[i][K][ult] = min(ponerla,noPonerla);
        }
        return m[i][K][ult];
    }
    else if(i < N && K > 0) {
        if(m2[ult][i] == -1){
            calcular(ult,i,V,m2);
        }
        int noPonerla = distribuir(i+1,ult,N,K,Kinicial,V,m,m2,ubs);
        int ponerla = m2[ult][i] + distribuir(i+1,i,N,K-1,Kinicial,V,m,m2,ubs);
        if(m[i][K][ult] != -1){
            m[i][K][ult] = min(min(ponerla,noPonerla),m[i][K][ult]);
        }
        if(m[i][K][ult] == -1){
            m[i][K][ult] = min(ponerla,noPonerla);
        }
        ubs[i] = V[i];
        return m[i][K][ult];
        }
}


int main(){
    int N;
    int K;
    vector<int> V;
    N = 5;
    K = 3;
    V = {1,5,15,20,27};
    vector<vector<vector<int>>> memoria(N, vector<vector<int>>(K, vector<int>(N, -1)));
    vector<vector<int>> memoria2(N, vector<int>(N,-1));

    vector<int> ubics(K,-1);
    int res = distribuir(0,0,N,K,K,V,memoria,memoria2,ubics);

    return 0;
}