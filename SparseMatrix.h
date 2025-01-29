#ifndef SPARSE_MATRIZ_H
#define SPARSE_MATRIZ_H
#include "Node.h"
#include <iostream>
#include <stdexcept>

class SparseMatrix{
    private:
    Node * h_lin; // ponteiro head das linhas
    Node * h_col; // ponteiro head de colunas
    int numLinhas; // variável que recebe a quantidade total de linhas da matriz
    int numColunas; // variável que recebe a quantidade total de colunas da matriz
    int m_size; // variavel que guarda o tamanho total da matriz
    int m_node; // variavel que guarda quantos nodes há na matriz
    
    public:
    // Método construtor da Matriz Esparsa
    SparseMatrix(int lin, int col){

        // Inicializa numLinhas e numColunas
        numLinhas=lin;
        numColunas=col;

        // Verifica se tamanho para o cabeçalho é válido
        if(lin>0 && col>0){
            //Caso seja válido
            // Inicializa os ponteiros h_lin e h_col como sentinelas
            h_lin = new Node(nullptr, nullptr, 0, 0, 0);
            h_col = new Node(nullptr, nullptr, 0, 0, 0);
            
            // Os cabeçalhos apontam para si mesmos de forma circular
            h_lin->abaixo = h_lin;
            h_col->direita = h_col;

            // Laço que percorre uma coluna adicionando os nós sentinelas para cada linha
            // chamando a função push_back_linha
            for(int i = 1; i <= lin; i++){
                push_back_linha(i);
            }

            // Laço que percorre uma linha adicionando os nós sentinelas para cada coluna
            // chamando a função push_back_coluna
            for(int i = 1; i <= col; i++){
                push_back_coluna(i);
            }

            // Inicializa o tamanho de otal da matriz e a quantidade de nós
            m_size = numLinhas * numColunas;
            m_node = 0;
        }else{
            // Caso o tamanho passado seja inválido, lança uma exceção
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
    
    // Função que cria um novo nó dentro da matriz, recebendo de parâmetro a posição de linha e coluna
    // e o valor que o nó vai receber
    void insert(int i, int j, double value){

        // Primeiro verifica se a posição passada é válida e se está dentro do tamanho da matriz
        if(j <= 0 || i <= 0 || i > numLinhas || j > numColunas ){
            throw std::out_of_range("Índices Inválidos");
        }

        // Verifica se o valor passado é diferente de zero
        if(value != 0){

            // Verifica se na posição passada existe um nó ou não
            // Caso não exista, ele vai criar um novo nó e atualizar os ponteiros
            if(this->get(i, j) == 0){
                
                // Cria dois nós que apontam para as linhas e colunas válidas (1,1)
                Node *lin = h_lin->abaixo; 
                Node *col = h_col->direita;
                
                // Laço que percorre o cabeçalho até encontrar linha referente a i
                // ou até retornar ao inicio 
                while (lin != h_lin && lin->linhas != i){
                    lin = lin->abaixo;
                }

                // Laço que percorre o cabeçalho até encontrar a coluna referente a j
                // ou até retornar ao inicio
                while (col != h_col && col->colunas != j){
                    col = col->direita;
                }

                // Quando chegar na posição desejada cria um novo nó para armazená-la
                Node* aux = new Node(nullptr, nullptr, i, j, value);

                // Percorre a linha para direita até encontrar a posição correta de j para inserir o nó
                Node* linAtual = lin;
                while (linAtual->direita != lin && linAtual->direita->colunas < j){
                    linAtual = linAtual->direita;
                }

                // Quando estiver na posição exata atualiza o ponteiro para direita de aux e linAtual
                aux->direita = linAtual->direita;
                linAtual->direita = aux;

                // Percorre a coluna para baixo até encontrar a posição correta de i para inserir o nó
                Node* colAtual = col;
                while(colAtual->abaixo != col && colAtual->abaixo->linhas < i){
                    colAtual = colAtual->abaixo;
                }

                // Assim que estiver na posição exata atualiza o ponteiro abaixo de aux e colAtual
                aux->abaixo = colAtual->abaixo;
                colAtual->abaixo = aux;

                // atualiza o contador de nodes
                m_node++;
            }else{
                // Caso exista um nó na posição passada no parâmetro ele vai atualizar o nó

                // Laço que percorre o cabeçalho de linha até a posição i
                Node* auxLin = h_lin->abaixo;
                while (auxLin != h_lin && auxLin->linhas != i) {
                    auxLin = auxLin->abaixo;
                }
                
                // Laço que percorre a linha até encontrar a posição da coluna j
                Node* auxCol = auxLin->direita;
                while(auxCol != auxLin && auxCol->colunas != j){
                    auxCol= auxCol->direita;
                }
                
                // Quando o nó estiver exatamente na posição existente
                // atualiza para o valor passado nos parâmetros
                auxCol->valor = value;
            }
        }
    }

    //Função que retorna um determinado valor da matriz na posição dos índices fornecidos
    double get(int i, int j){

        //Verifica se os índices ultrapassam os limites da matriz
        //Se ultrapassar, lança uma exceção
        if(j <= 0 || i <= 0 || i>numLinhas || j>numColunas ){
            throw std::out_of_range("Índices Inválidos");
        }
        //Ponteiro para percorrer as linhas
        Node *auxLin = h_lin;
        
        //Laço que percorre as linhas até chegar na linha fornecida nos parâmetros
        while(auxLin->linhas!=i){
            auxLin=auxLin->abaixo;
        }
        
        //Verifica se tem algum nó na linha fornecida
        //Se não tiver, retorna 0
        if(auxLin->direita==auxLin){
            return 0;
        }

        //Ponteiro para percorrer as colunas
        //Obs: Esse ponteiro já está na linha fornecida
        Node *auxCol=auxLin->direita;

        //Laço que percorre as colunas até chegar na coluna fornecida nos parâmetros
        /*Como o auxCol já estava apontando para a posição da linha, ao final do laço
        o auxCol estará apontando diretamente para o nó que corresponde ao índice fornecido*/
        while(auxCol->colunas!=j && auxCol!=auxLin){
            auxCol= auxCol->direita;
        }

        //Retorna o valor do nó na posição do índice fornecido
        return auxCol->valor;
    }

    //Função que imprime a matriz no terminal
    void print(){
        //For dentro de um For que percorre a matriz como inteira
        //Chama a função get(int i, int j) para pegar o valor de cada posição da matriz
        for(int i=1;i<=numLinhas;i++){
            for(int j=1;j<=numColunas;j++){
                std::cout<<get(i, j)<<" ";
            }
            std::cout<<"\n";
        }
    }

    ~SparseMatrix() {
    // Percorre todas as linhas
        Node* linhaAtual = h_lin->abaixo;
        while (linhaAtual != h_lin) {
            Node* noAtual = linhaAtual->direita;

        // Remove todos os nós da linha atual
            while (noAtual != linhaAtual) {
                Node* proximo = noAtual->direita;
                delete noAtual;
                noAtual = proximo;
        }

        // Avança para a próxima linha e remove o nó da linha atual
            Node* proximaLinha = linhaAtual->abaixo;
            delete linhaAtual;
            linhaAtual = proximaLinha;
        }

    // Remove os nós das colunas (sentinelas)
        Node* colunaAtual = h_col->direita;
        while (colunaAtual != h_col) {
            Node* proximaColuna = colunaAtual->direita;
            delete colunaAtual;
            colunaAtual = proximaColuna;
        }

    // Remove os cabeçalhos
        delete h_lin;
        delete h_col;
    }
};

#endif