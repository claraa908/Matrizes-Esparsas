#ifndef NODE_H
#define NODE_H
#include <iostream>
using namespace std;

struct Node{
    //comentar o código!!!!
    Node *direita;
    Node *abaixo;
    int linhas;
    int colunas;
    double valor;

    Node(Node *direita, Node *abaixo, int linhas, int colunas, double valor){
        this->direita=direita;
        this->abaixo=abaixo;
        this->linhas=linhas;
        this->colunas=colunas;
        this->valor=valor;
    }
};

#endif