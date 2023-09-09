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
            ult = i+1;
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
    }
    else{
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
        for(int i = actual; i<v.size();i++){
            res = res + abs(v[actual]-v[i]);
        }
        m2[m2.size()-1][actual] = res;
    }

}

int distribuir(int i, int ult, int k, vector<int> &v, vector<vector<vector<int>>> &m, vector<vector<int>> &m2,vector<vector<vector<decision>>> &m3 ){
    if(k==0){
        return  m2[m2.size()-1][ult];
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
    int cantTest;
    cin>>cantTest;
    for(int i = 0; i < cantTest;i++){
        int cantPuestos;
        int cantProvedurias;
        cin>>cantPuestos;
        cin>>cantProvedurias;
        vector<int> ubicaciones;
        for(int j = 0; j< cantPuestos;j++){
            int ub;
            cin>>ub;
            ubicaciones.push_back(ub);
        }
        vector<vector<vector<int>>> memoria(cantProvedurias+2, vector<vector<int>>(cantPuestos+1, vector<int>(cantPuestos+1, -1)));
        vector<vector<int>> memoria2(cantPuestos+3, vector<int>(cantPuestos+2,-1));
        vector<vector<vector<decision>>> memoria3(cantProvedurias+2, vector<vector<decision>>(cantPuestos+1, vector<decision>(cantPuestos+1, UNDEF)));
        int res = distribuir(0,-1,cantProvedurias,ubicaciones,memoria,memoria2,memoria3);
        vector<int> ubics = armarSol(memoria3,ubicaciones,cantProvedurias);
        cout<<res<<endl;
        for(int p = 0; p<ubics.size();p++){
            cout<<ubics[p]<<" ";
        }
        cout<<endl;
    }
};