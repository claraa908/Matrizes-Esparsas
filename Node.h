#ifndef NODE_H
#define NODE_H
#include <iostream>
using namespace std;

struct Node{
    Node *direita; // Ponteiro para o elemento da direita
    Node *abaixo; // Ponteiro para o elemento abaixo
    int linhas; // Variável que guarda a posição da linha
    int colunas; // Variável que guarda a posição da coluna
    double valor; // Variável que guarda o valor do nó

    // Método construtor do nó
    Node(Node *direita, Node *abaixo, int linhas, int colunas, double valor){
        this->direita=direita;
        this->abaixo=abaixo;
        this->linhas=linhas;
        this->colunas=colunas;
        this->valor=valor;
    }

    // Método destrutor do nó
    ~Node(){
        direita=nullptr;
        abaixo=nullptr;
    }
};

#endif