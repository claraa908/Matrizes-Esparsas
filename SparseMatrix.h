#ifndef SPARSE_MATRIZ_H
#define SPARSE_MATRIZ_H
#include "Node.h"
#include <iostream>
#include <stdexcept>

//socoroooo

class SparseMatrix{
    //comentar o código!!!!
    private:
    Node * h_lin;
    Node * h_col;
    int m_size;
    
    public:
    SparseMatrix(int lin, int col){
        if(lin>0 && col>0){
            h_lin = new Node(nullptr, nullptr, 0, 0, 0);
            h_col = new Node(nullptr, nullptr, 0, 0, 0);
            
            h_lin->abaixo = h_lin;
            h_col->direita = h_col;

            for(int i=1;i<=lin;i++){
                push_back_linha(i);
            }

            for(int i = 1; i <= col; i++){
                push_back_coluna(i);
            }

            m_size=0;
            
        }else{
            throw std::out_of_range("um ou mais índices menores que 0");
        }
    }

    void push_back_linha(int linha){
        Node *auxLinha=new Node(nullptr, nullptr, linha, 0, 0);

        Node *atual = h_lin;

        while(atual->abaixo != h_lin){
            atual=atual->abaixo;
        }

        atual->abaixo=auxLinha;
        auxLinha->abaixo=h_lin; 
    }

    void push_back_coluna(int coluna){
        Node *auxCol = new Node(nullptr, nullptr, 0, coluna, 0);

        Node *atual = h_col;

        while(atual->direita != h_col){
            atual = atual->direita;
        }

        atual->direita = auxCol;
        auxCol->direita= h_col;
    }
    
    //u ia uuu ia i i aaa
    void insert(int i, int j, double value){
        if(j <= 0 || i <= 0){
            throw std::out_of_range("Um ou mais índices são menores ou iguais a 0");
        }

        if(value!=0){
            
        }
        Node *aux=new Node(h_col, h_lin, 0, 0, 0);

        while(aux->colunas!=j){
            aux=aux->direita;
        }
    }

    double get(int i, int j){
        if(j <= 0 || i <= 0){
            throw std::out_of_range("Um ou mais índices são menores ou iguais a 0");
        }
        Node *auxCol = h_col->direita;
        
        while(auxCol != h_col && auxCol->colunas!=j){
            auxCol = auxCol->direita;
        }

        if(auxCol == h_col){
            return 0;
        }
        
        //! Verificar se o nó aponta para si mesmo
        //! Se ele apontar para si mesmo, é porque não há nós embaixo dele
        //! Se não prossegue.
        if(auxCol->abaixo == auxCol){
            return 0;
        }

        Node* auxLin = auxCol->abaixo;
        
        while(auxLin != auxCol && auxLin->linhas!=i){
            auxLin= auxLin->abaixo;
        }

        if(auxLin == auxCol){
            return 0;
        }

        return auxLin->valor;
    }
    
    void print();

    ∼SparseMatrix(){

    }

};
#endif