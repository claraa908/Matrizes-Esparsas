#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include "SparseMatrix.h"
using namespace std;

void readSparseMatrix(SparseMatrix*& m, string nome_do_arquivo){

    fstream file(nome_do_arquivo);

    if(!file.is_open()){
        cout<<"Erro ao abrir o arquivo!!"<<endl;
    }

    int x, y;
    file >> x >> y;
        
    m=new SparseMatrix(x, y);

    file.ignore();
    string linha;
    
    int i, j;
    double value;
    while(getline(file, linha)){
        stringstream ss(linha);
        ss >> i >> j >> value;
        
        m->insert(i, j, value);
    }
}

int main(){

    SparseMatrix *matriz;

    readSparseMatrix(matriz, "m2.txt");

    matriz->print();

    matriz->clear();
    matriz->print();
}
