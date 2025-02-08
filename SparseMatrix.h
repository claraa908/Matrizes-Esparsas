#ifndef SPARSE_MATRIZ_H
#define SPARSE_MATRIZ_H
#include "Node.h"
#include <iostream>
#include <stdexcept>
#include <iomanip>

/*
* @authors 
* Alana Maria Sousa Augusto - 564976
* Clara Cruz Alves - 568563
*/

class SparseMatrix{
    private:
    Node * h_lin; // ponteiro head das linhas
    Node * h_col; // ponteiro head de colunas
    int numLinhas; // variável que recebe a quantidade total de linhas da matriz
    int numColunas; // variável que recebe a quantidade total de colunas da matriz
    int m_size; // variavel que guarda o tamanho total da matriz
    int m_node; // variavel que guarda quantos nodes há na matriz

    // Método auxiliar do Construtor que insere cada nó 
    // nó sentinela que representa as linhas de acordo
    // com o número de linhas passado como parâmetro.
    // Esse método será chamado várias vezes no Construtor
    // em uma estrutura de repetição.
    void push_back_linha(int linha){
        // Nó auxiliar que vai ajudar a inserir os nós sentinelas de acordo com o número de linhas
        Node *auxLinha = new Node(nullptr, nullptr, linha, 0, 0);

        // Nó que representa a posição atual da lista de linhas
        Node *atual = h_lin;

        // Percorre atual até que a posição abaixo esteja apontando
        // para h_lin (que representa o início de tudo)
        while(atual->abaixo != h_lin){
            atual = atual->abaixo;
        }

        // A posição abaixo de atual recebe o ponteiro auxiliar de linha
        atual->abaixo = auxLinha;
        // Faz a posição abaixo apontar de volta para h_lin (lista circular)
        auxLinha->abaixo = h_lin;
        // Faz a posição a direita apontar de volta para auxLinha (lista circular)
        auxLinha->direita = auxLinha;
    }

    // Método auxiliar do Construtor que insere cada nó
    // nó sentinela que representa as colunas de acordo
    // com o número de colunas passado como parâmetro
    // Esse método será chamado várias vezes no Construtor
    // em uma estrutura de repetição.
    void push_back_coluna(int coluna){
        // Nó auxiliar que vai ajudar a inserir os nós sentinelas de acordo com o número de colunas
        Node *auxCol = new Node(nullptr, nullptr, 0, coluna, 0);

        // Nó que representa a posição atual da lista de colunas
        Node *atual = h_col;

        // Percorre atual até que a posição a direita esteja apontando
        // para h_col (que representa o início de tudo)
        while(atual->direita != h_col){
            atual = atual->direita;
        }

        // A posição abaixo de atual recebe o ponteiro auxiliar de coluna
        atual->direita = auxCol;
        // Faz a posição a direita apontar de volta para h_col (lista circular)
        auxCol->direita = h_col;
        // Faz a posição abaixo apontar de volta para auxCol (lista circular)
        auxCol->abaixo =auxCol;
    }
    
    public:
    // Método construtor da Matriz Esparsa
    SparseMatrix(int lin, int col){
        // Inicializa numLinhas e numColunas
        numLinhas = lin;
        numColunas = col;

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
            throw std::out_of_range("um ou mais indices menores que 0");
        }
    }

    // Construtor Default
    SparseMatrix(){
        h_lin = new Node(nullptr, nullptr, 0, 0, 0);
        h_col = new Node(nullptr, nullptr, 0, 0, 0);

        h_lin->abaixo = h_lin;
        h_col->direita = h_col;
    }
    
    // Função que cria um novo nó dentro da matriz, recebendo de parâmetro a posição de linha e coluna
    // e o valor do nó
    void insert(int i, int j, double value){
        // Primeiro verifica se a posição passada é válida e se está dentro do tamanho da matriz
        if(j <= 0 || i <= 0 || i > numLinhas || j > numColunas ){
            throw std::out_of_range("Indices Invalidos");
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

    // Função para remover nó de determinada posição da matriz
    void remove(int i, int j){
        // Verifica se os indices estão dentro dos limites válidos da matriz
        if(i <= 0 || j <= 0 || i > numLinhas || j > numColunas){
            throw std::out_of_range("Índices Inválidos");
        }

        // Ponteiro de linhas que vai percorrer a lista até encontrar a linha correspondente
        // quando encontrar o cabeçalho quer dizer que a linha não existe
        Node *lin = h_lin->abaixo;
        while (lin != h_lin && lin->linhas != i){
            lin = lin->abaixo;
        }

        // Se a linha nao for encontrada, entao nao tem elementos nela
        if(lin == h_lin){
            throw runtime_error("nao ha no nessa posicao");
        }

        Node *aux = lin; // Ponteiro auxliar que vai se movimentar pela linha até encontrar j
        Node *prev = aux; // Ponteiro que vai ficar com uma posição anterior ao auxiliar para facilitar a remoção

        // Percorre a linha até encontrar j se o nó não existir aux estará no início da linha
        while(aux->direita != lin && aux->colunas != j){
            prev = aux;
            aux = aux->direita;
        }

        // Se percorreu a linha e não encontrou a coluna então não há nó
        if(aux->colunas != j){
            throw runtime_error("nao ha no nessa posicao");
        }

        // Se aux for encontrado, ajusta o ponteiro para direita de prev 
        // para ignorar aux e conectar prev ao próximo nó
        // removendo aux da linha.
        prev->direita = aux->direita;

        // Ponteiro de colunas que vai percorrer a lista até encontrar a coluna correspondente
        // se col encontrar o inicio do cabeçalho quer dizer que a coluna não existe
        Node *col = h_col->direita;
        while (col != h_col && col->colunas != j){
            col = col->direita;
        }

        // Se a coluna não foi encontrada, então não tem elementos nela
        if (col == h_col) {
            throw std::runtime_error("Não há nó nessa posição");
        }

        // Percorre a coluna para encontrar o nó de aux na posição i
        aux = col;
        prev = aux;
        while(aux->abaixo != col && aux->linhas != i){
            prev = aux;
            aux = aux->abaixo;
        }

        // Se percorreu a coluna e não encontrou a linha então o nó não existe.
        if(aux->linhas != i){
            throw runtime_error("nao ha no nessa posicao");
        }

        // Ajusta o prev para apontar para o valor que aux aponta, para poder removê-lo da coluna
        prev->abaixo = aux->abaixo;

        // Atualiza o contador de nós
        m_node--;

        // Deleta o nó
        delete aux;
    }

    // Função que retorna um determinado valor da matriz na posição dos índices fornecidos
    const double get(int i, int j) const{
        // Verifica se os índices ultrapassam os limites da matriz
        // Se ultrapassar, lança uma exceção
        if(j <= 0 || i <= 0 || i > numLinhas || j > numColunas ){
            throw std::out_of_range("Indices Invalidos");
        }
        // Ponteiro para percorrer as linhas
        Node *auxLin = h_lin;
        
        // Laço que percorre as linhas até chegar na linha fornecida nos parâmetros
        while(auxLin->linhas != i){
            auxLin = auxLin->abaixo;
        }
        
        // Verifica se tem algum nó na linha fornecida
        // Se não tiver, retorna 0
        if(auxLin->direita == auxLin){
            return 0;
        }

        // Ponteiro para percorrer as colunas
        // Obs: Esse ponteiro já está na linha fornecida
        Node *auxCol = auxLin->direita;

        // Laço que percorre as colunas até chegar na coluna fornecida nos parâmetros
        /*Como o auxCol já estava apontando para a posição da linha, ao final do laço
        o auxCol estará apontando diretamente para o nó que corresponde ao índice fornecido*/
        while(auxCol->colunas != j && auxCol != auxLin){
            auxCol = auxCol->direita;
        }

        // Retorna o valor do nó na posição do índice fornecido
        return auxCol->valor;
    }

    // Função que imprime a matriz no terminal
    void print(){
        // Variável que define o tamanho da coluna no terminal
        int tamanho_coluna = 8;
        // Variável que armazena o largura total da matriz
        int largura_total = tamanho_coluna * numColunas + numColunas+1;

        // Imprime uma linha reta pontilhda no terminal
        for(int i = 0; i < largura_total; ++i){
            std::cout << "-";
        }
        // Quebra de linha
        std::cout << "\n";

        // For dentro de um For que percorre a matriz por inteiro
        // Chama a função get(int i, int j) para pegar o valor de cada posição da matriz
        for(int i = 1; i <= numLinhas; i++){
            // Imprime uma barra no início de cada linha
            std::cout << "|";
            for(int j = 1; j <= numColunas; j++){
                // Formatação das colunas
                std::cout << std::setw(tamanho_coluna) << std::fixed << std::setprecision(1) << get(i, j) << "|";
            }
            std::cout << "\n";
        }

        // Imprime uma linha reta pontilhada no terminal
        for(int i = 0; i < largura_total; ++i){
            std::cout << "-";
        }
        cout << endl;
    }

    // Função que retorna o número de linhas da matriz
    int getLinhas(){
        return numLinhas;
    }

    // Função que retorna o número de colunas da matriz
    int getColunas(){
        return numColunas;
    }

    // Função que retorna a quantidade de nós
    int getQntNos(){
        return m_node;
    }

    // Função que limpa a matriz apagando todos os nós e zerando os valores
    void clear(){
        // Começa da primeira linha de dados abaixo do cabeçalho
        Node* linhaAtual = h_lin->abaixo; // Ponteiro que percorre as linhas da matriz

        // Enquanto não voltar ao cabeçalho da linha percorre ela
        while (linhaAtual != h_lin) {
            // Ponteiro auxiliar para percorrer os nós da linha
            Node* noAtual = linhaAtual->direita;

            // Percorre todos os nós da linha
            while (noAtual != linhaAtual && noAtual != nullptr) { // Enquanto não voltar ao cabeçalho da linha
                Node* proximo = noAtual->direita; // Guarda a posição do próximo nó antes de remover o atual

                // Encontra o nó anterior na linha para poder removê-lo
                Node* prev = linhaAtual;
                while (prev->direita != noAtual) { 
                    prev = prev->direita;
                }
                prev->direita = noAtual->direita; // Ajusta o ponteiro da linha para ignorar o nó atual

                // Encontra a coluna correspondente ao nó atual
                Node* colAtual = h_col->direita;
                while (colAtual != h_col && colAtual->colunas != noAtual->colunas) { 
                    colAtual = colAtual->direita;
                }

                // Encontra o nó anterior na coluna para poder removê-lo
                Node* colPrev = colAtual;
                while (colPrev->abaixo != noAtual) { 
                    colPrev = colPrev->abaixo;
                }
                colPrev->abaixo = noAtual->abaixo; // Ajusta o ponteiro da coluna para ignorar o nó atual

                // Remove o nó da matriz
                delete noAtual;

                // Atualiza o ponteiro para continuar percorrendo a linha
                noAtual = proximo;
            }

            // Avança para a próxima linha
            linhaAtual = linhaAtual->abaixo;
        }

        // Percorre toda a matriz e garante que os valores sejam zerados
        Node* linha = h_lin->abaixo;
        while (linha != h_lin) { 
            Node* no = linha->direita;
            while (no != linha) { 
                no->valor = 0; // Zera o valor do nó
                no = no->direita;
            }
            linha = linha->abaixo;
        }

        // Atualiza o contador de nós
        m_node = 0;
    }

    // Método destrutor da matriz esparsa
    ~SparseMatrix(){
        // Percorre a matriz removendo todos os nós
        Node* linhaAtual = h_lin->abaixo; // Começa a partir da primeira linha de dados
        while (linhaAtual != h_lin) { // Enquanto não voltar ao cabeçalho da linha
            Node* noAtual = linhaAtual->direita; // Ponteiro auxiliar para percorrer os nós da linha

            // Percorre e remove todos os nós da linha
            while (noAtual != linhaAtual) { // Enquanto não voltar ao cabeçalho da linha
                Node* proximo = noAtual->direita; // Guarda a posição do próximo nó antes de remover o atual
                delete noAtual; // Remove o nó atual da memória
                noAtual = proximo; // Atualiza o ponteiro para continuar percorrendo a linha
            }

            // Armazena a próxima linha antes de deletar a linha atual
            Node* proximaLinha = linhaAtual->abaixo; 
            delete linhaAtual; // Remove a linha atual
            linhaAtual = proximaLinha; // Avança para a próxima linha
        }

        // Percorre e remove os cabeçalhos das colunas
        Node* colunaAtual = h_col->direita; // Começa pelo primeiro cabeçalho de coluna
        while (colunaAtual != h_col) { // Enquanto não voltar ao cabeçalho da coluna
            Node* proximaColuna = colunaAtual->direita; // Guarda a próxima coluna antes de remover a atual
            delete colunaAtual; // Remove a coluna atual
            colunaAtual = proximaColuna; // Avança para a próxima coluna
        }

        // Remove os cabeçalhos principais da matriz
        delete h_lin;
        delete h_col;
    }
};

#endif