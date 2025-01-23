#ifndef SPARSE_MATRIZ_H
#define SPARSE_MATRIZ_H
#include "Node.h"
#include <iostream>
#include <stdexcept>

class SparseMatrix{
    //comentar o código!!!!
    private:
    Node * h_lin;
    Node * h_col;
    int numLinhas;
    int numColunas;
    int m_size;
    
    public:
    SparseMatrix(int lin, int col){
        numLinhas=lin;
        numColunas=col;
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
        auxLinha->direita=auxLinha;
    }

    void push_back_coluna(int coluna){
        Node *auxCol = new Node(nullptr, nullptr, 0, coluna, 0);

        Node *atual = h_col;

        while(atual->direita != h_col){
            atual = atual->direita;
        }

        atual->direita = auxCol;
        auxCol->direita= h_col;
        auxCol->abaixo=auxCol;
    }
    
    void insert(int i, int j, double value){
        if(j <= 0 || i <= 0){
            throw std::out_of_range("Um ou mais índices são menores ou iguais a 0");
        }

        if(value != 0){
            if(this->get(i, j) == 0){
                Node *lin = h_lin->abaixo;
                Node *col = h_col->direita;

                while (lin != h_lin && lin->linhas != i){
                    lin = lin->abaixo;
                }

                while (col != h_col && col->colunas != j){
                    col = col->direita;
                }

                Node* aux = new Node(nullptr, nullptr, i, j, value);

                Node* linAtual = lin;
                while (linAtual->direita != lin && linAtual->direita->colunas < j){
                    linAtual = linAtual->direita;
                }
                aux->direita = linAtual->direita;
                linAtual->direita = aux;

                Node* colAtual = col;
                while(colAtual->abaixo != col && colAtual->abaixo->linhas < i){
                    colAtual = colAtual->abaixo;
                }
                aux->abaixo = colAtual->abaixo;
                colAtual->abaixo = aux;

                m_size++;
            }else{
                Node* auxLin = h_lin->abaixo;
                while (auxLin != h_lin && auxLin->linhas != i) {
                    auxLin = auxLin->abaixo;
                }

                Node* auxCol = auxLin->direita;
                while(auxCol->colunas!=j && auxCol!=auxLin){
                    auxCol= auxCol->direita;
                }

                auxCol->valor = value;
            }
        }
    }


    double get(int i, int j){
        if(j <= 0 || i <= 0 || i>numLinhas || j>numColunas ){
            throw std::out_of_range("Índices Inválidos");
        }
        Node *auxLin = h_lin;
        
        while(auxLin->linhas!=i){
            auxLin=auxLin->abaixo;
        }
        
        if(auxLin->direita==auxLin){
            return 0;
        }

        Node *auxCol=auxLin->direita;

        while(auxCol->colunas!=j && auxCol!=auxLin){
            auxCol= auxCol->direita;
        }

        return auxCol->valor;
    }
    
    void print();

    

    void clear(){
    
    }

    bool empty(){
        if(!h_lin || !h_col){
            return true;
        }

        Node *aux=h_lin->abaixo;

        while(aux!=h_lin){
            if(aux->direita!=h_col){
                return false;
            }
            aux=aux->abaixo;
        }

        return true;
    }

    void pop_back_linha(Node *aux){
        
        Node *prev=nullptr;
        aux=h_lin->abaixo;

        while(aux->direita!=h_col){
            prev=aux;
            aux=aux->direita;
        }

        prev->direita=h_col;
        
        delete aux;

   }

   void pop_back_coluna(Node *aux){
        Node *prev=nullptr;
        aux=h_col->direita;

        while(aux->abaixo!=h_lin){
            prev=aux;
            aux=aux->abaixo;
        }

        prev->abaixo=h_lin;

        delete aux;
   }

};
#endif