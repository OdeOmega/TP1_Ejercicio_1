#include <iostream>
#include <vector>

enum decision {poner,noPoner,UNDEF};
using namespace std;

vector<int> armarSol(vector<vector<vector<decision>>> &m3, vector<int> &v, int K){
    int ult = 0;
    vector<int> res = {};
    for(int i = 0; i < v.size();i++){
        if(m3[i][K][ult] == poner){
            K = K-1;
            ult = i;
            res.push_back(v[i]);
        }
    }
    return res;
}

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




int distribuir(int i,int ult, int &N, int K, int &Kinicial, vector<int> &V, vector<vector<vector<int>>> &m,vector<vector<int>> &m2,vector<vector<vector<decision>>> &m3){
    if(Kinicial == 1){
        int temp1 = calcularPrim(N/2,V,m2);
        int temp2 = calcularUlt(N/2,V,m2);
        m3[i][K][ult] = poner;
        return temp1 + temp2;
    }
    else if((N-i)<K) {
        int termin = 10000000;
        return termin;
    }
    else if(K == Kinicial){
        int temp1 = calcularPrim(i,V,m2);
        int noPonerla = distribuir(i+1,ult,N,K,Kinicial,V,m,m2,m3);
        int ponerla = temp1 + distribuir(i+1,i,N,K-1,Kinicial,V,m,m2,m3);
        if (min(ponerla,noPonerla) == ponerla){
            m3[i][K][ult] = poner;
        }
        if (min(ponerla,noPonerla) == noPonerla){
            m3[i][K][ult] = noPoner;
        }
        return min(ponerla,noPonerla);
    }
    else if(K == 1 && i < N){
        int temp1 = calcularUlt(i,V,m2);
        if(m2[ult][i] == -1){
            calcular(ult,i,V,m2);
        }
        int noPonerla = distribuir(i+1,ult,N,K,Kinicial,V,m,m2,m3);
        int ponerla = m2[ult][i] + temp1;
        if(m[i][K][ult] != -1){
            m[i][K][ult] = min(min(noPonerla,ponerla),m[i][K][ult]);
        }
        if(m[i][K][ult] == -1){
            m[i][K][ult] = min(noPonerla,ponerla);
        }
        if (min(ponerla,noPonerla) == ponerla){
            m3[i][K][ult] = poner;
        }
        if (min(ponerla,noPonerla) == noPonerla){
            m3[i][K][ult] = noPoner;
        }
        return m[i][K][ult];
    }
    else if(i < N && K > 0) {
        if(m2[ult][i] == -1){
            calcular(ult,i,V,m2);
        }
        int noPonerla = distribuir(i+1,ult,N,K,Kinicial,V,m,m2,m3);
        int ponerla = m2[ult][i] + distribuir(i+1,i,N,K-1,Kinicial,V,m,m2,m3);
        if(m[i][K][ult] != -1){
            m[i][K][ult] = min(min(noPonerla,ponerla),m[i][K][ult]);
        }
        if(m[i][K][ult] == -1){
            m[i][K][ult] = min(noPonerla,ponerla);
        }
        if (min(ponerla,noPonerla) == ponerla){
            m3[i][K][ult] = poner;
        }
        if (min(ponerla,noPonerla) == noPonerla){
            m3[i][K][ult] = noPoner;
        }
        if(ponerla == noPonerla){
            m3[i][K][ult] = noPoner;
        }
        return m[i][K][ult];
        }
}


int main(){
    int N;
    int K;
    vector<int> V;
    N = 4;
    K = 2;
    V = {1,5,15,20};
    vector<vector<vector<int>>> memoria(N+1, vector<vector<int>>(K+1, vector<int>(N+1, -1)));
    vector<vector<int>> memoria2(N, vector<int>(N,-1));
    vector<vector<vector<decision>>> memoria3(N+1, vector<vector<decision>>(K+1, vector<decision>(N+1, UNDEF)));

    int res = distribuir(0,0,N,K,K,V,memoria,memoria2,memoria3);
    vector<int> ubics = armarSol(memoria3,V,K);
    return 0;
}