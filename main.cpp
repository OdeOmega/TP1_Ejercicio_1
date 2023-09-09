#include <iostream>
#include <vector>

enum decision {poner_,noPoner_,UNDEF};
using namespace std;

vector<int> armarSol(vector<vector<vector<decision>>> &m3, vector<int> &v, int K){
    int ult = 0;
    vector<int> res = {};
    for(int i = 0; i < v.size();i++){
        if(m3[K][ult][i] == poner_){
            K = K-1;
            ult = i;
            res.push_back(v[i]);
        }
    }
    return res;
}

void calcular(int ult,int actual, vector<int> &v,vector<vector<int>> &m2, int & k) {
    if(ult == -1){
        int res = 0;
        for (int i = 0; i < actual; i++) {
            res = res + abs(v[actual] - v[i]);
        }
        m2[ult+1][actual] = res;
    } else{
        int res = 0;
        int ultVal = v[ult];
        int actualVal = v[actual];
        for (int i = ult; i < actual; i++) {
            int temp1 = abs(ultVal - v[i]);
            int temp2 = abs(actualVal - v[i]);
            res = res + min(temp1,temp2);
        }
        m2[ult+1][actual] = res;
    }
    if(k==1){
        int res = 0;
        for(int i = ult; i<v.size();i++){
            int temp1 = abs(v[ult] - v[i]);
            int temp2 = abs(v[actual] - v[i]);
            res = res + min(temp1,temp2);
        }
        m2[ult+2][actual] = res;
    }

}

int distribuir(int i, int ult, int k, vector<int> &v, vector<vector<vector<int>>> &m, vector<vector<int>> &m2,vector<vector<vector<decision>>> &m3 ){
    if(k==0){
        return 0;
    }
    else if( k < 0 || i == v.size() || (v.size()-i)< k){
        return 1000000000;
    }
    else{
        if(m2[ult+1][i] == -1){
            calcular(ult,i,v,m2,k);
        }
        if(m[k][ult+1][i] == -1){
            int poner = m2[ult+1][i] + distribuir(i+1,i,k-1,v,m,m2,m3);
            if(k == 1){
                poner = poner + m2[ult+2][i];
            }
            int no_poner = distribuir(i+1,ult,k,v,m,m2,m3);
            if(poner <= no_poner){
                m3[k][ult+1][i] = poner_;
                m[k][ult+1][i] = poner;
            } else{
                m3[k][ult+1][i] = noPoner_;
                m[k][ult+1][i] = no_poner;
            }
        }
        return m[k][ult+1][i];
    }

}

int main(){
    int N;
    int K;
    vector<int> V;
    N = 4;
    K = 2;
    V = {1,5,15,20};
    vector<vector<vector<int>>> memoria(K+2, vector<vector<int>>(N+1, vector<int>(N+1, -1)));
    vector<vector<int>> memoria2(N+2, vector<int>(N,-1));
    vector<vector<vector<decision>>> memoria3(K+2, vector<vector<decision>>(N+1, vector<decision>(N+1, UNDEF)));

    int res = distribuir(0,-1,K,V,memoria,memoria2,memoria3);
    vector<int> ubics = armarSol(memoria3,V,K);
    return 0;

};