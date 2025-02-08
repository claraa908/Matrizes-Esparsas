#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include "SparseMatrix.h"
using namespace std;

// Função responsável por ler um arquivo .txt e converter os dados
// fornecidos por ele em uma matriz esparsa
void readSparseMatrix(SparseMatrix*& m, string nome_do_arquivo){

    // Abre o arquivo usando o ftream
    fstream file(nome_do_arquivo);

    // Verifica se o arquivo está aberto adequadamente
    // Se não estiver, lança uma exceção
    if(!file.is_open()){
        throw runtime_error("Erro ao abrir o arquivo");
    }

    int x, y; // Variáveis para armazenar o número de linhas e colunas da matriz
    file >> x >> y; // Lê a primeira linha do documento, armazenando o número de
                    // de linhas e colunas nas variáveis
        
    // Inicializa a matriz m com o número de linhas e colunas lido no documento
    m=new SparseMatrix(x, y);

    // Ignora o caractere de nova linha após a leitura da primeira linha do documento
    file.ignore();

    string linha; // Variável para armazenar cada linha lida do documento
    
    int i, j; // Variáveis para armazenar o número de linhas e colunas
    double value; // Variável para armazenar o valor na posição i,j

    // Lê cada linha restante do documento
    while(getline(file, linha)){
        stringstream ss(linha); // Armazena a linha lida em uma stringstream

        ss >> i >> j >> value; // Passa os valores da stringstream para as 
                                // variáveis correspondentes

        m->insert(i, j, value); // Insere o valor lido na matriz m nas posições i, j
    }
}

// Função que soma duas matrizes
SparseMatrix* sum(SparseMatrix* &A, SparseMatrix* &B){

    // Verificação se as duas matrizes possuem o mesmo número de linhas e colunas
    // Se não tiverem, é lançada uma exceção
    if(A->getLinhas() == B->getLinhas() && A->getColunas() == B->getColunas()){
        // Cria uma nova matriz possuindo as dimensões da matriz A
        SparseMatrix* matrizSomada = new SparseMatrix(A->getLinhas(), A->getColunas());
            
            // Percorre a matriz recém criada
            for(int i = 1; i <= matrizSomada->getLinhas(); i++){
                for(int j = 1; j <= matrizSomada->getColunas(); j++){

                    double valorA = A->get(i, j); // Obtém o valor da matriz A na posição i,j
                    double valorB = B->get(i, j); // Obtém o valor da matriz B na posição i,j

                    double soma = valorA+valorB; // Faz a soma dos valores de A e B

                    matrizSomada->insert(i, j, soma); // Insere a soma na nova matriz
                }
            }

            return matrizSomada; // Retorna a nova matriz contendo a soma das matrizes A e B
        } else {

        throw out_of_range("Nao e possivel somar essas duas matrizes");
    }
    
}

// Função que subtrai duas matrizes
SparseMatrix* subtraction(SparseMatrix* &A, SparseMatrix* &B){

    // Verificação se as duas matrizes possuem o mesmo número de linhas e colunas
    // Se não tiverem, é lançada uma exceção
    if(A->getLinhas() == B->getLinhas() && A->getColunas() == B->getColunas()){
        // Cria uma nova matriz possuindo as dimensões da matriz A
        SparseMatrix* matrizSubtraida = new SparseMatrix(A->getLinhas(), A->getColunas());
            
            // Percorre a matriz recém criada
            for(int i = 1; i <= matrizSubtraida->getLinhas(); i++){
                for(int j = 1; j <= matrizSubtraida->getColunas(); j++){

                    double valorA = A->get(i, j); // Obtém o valor da matriz A na posição i,j
                    double valorB = B->get(i, j); // Obtém o valor da matriz B na posição i,j

                    double subtracao = valorA-valorB; // Faz a subtração dos valores de A e B

                    matrizSubtraida->insert(i, j, subtracao); // Insere a subtração na nova matriz
                    
                }
            }

            return matrizSubtraida; // Retorna a nova matriz contendo a subtração das matrizes A e B
        } else {

        throw out_of_range("Nao e possivel subtrair essas duas matrizes");
    }
    
}

// Função que multiplica duas matrizes
SparseMatrix* multiply(SparseMatrix* &A, SparseMatrix* &B){

    // Verifica se o número de colunas da matriz A é igual ao número de linhas da matriz B
    // Se não for, uma exceção é lançada
    if(A->getColunas() == B->getLinhas()){

        // Cria uma nova matriz com a quantidade de linhas de A e a de colunas de B
        SparseMatrix* matrizMultiplicada = new SparseMatrix(A->getLinhas(), B->getColunas());

        double soma = 0; // Variável para acumular a soma dos produtos

        // Percorre a matriz recém criada
        for(int i = 1; i <= matrizMultiplicada->getLinhas(); i++){
            for(int j = 1; j <= matrizMultiplicada->getColunas(); j++){

                soma = 0; // Reseta a soma dos produtos a cada repetição do laço

                // Percorre o número de colunas da matriz A
                for(int k = 1; k <= A->getColunas(); k++){ 
                    double valorA = A->get(i, k); // Armazena o valor de A na posição i, k
                    double valorB = B->get(k, j); // Armazena o valor de B na posição k, j

                    double mult = valorA * valorB; // Multiplica os valores de A e B

                    soma += mult; // Soma o resultado da multiplicação no acumulador
                }

                matrizMultiplicada->insert(i, j, soma); // Insere o resultado da soma do acumulador na nova matriz
            }
        }

        return matrizMultiplicada; // Retorna a nova matriz com a multiplicação de A e B


    } else {
        throw out_of_range("Nao e possivel multiplicar essas duas matrizes");
    }
    
    
}

// Função que transforma os comandos feitos no terminal em um vetor
vector<string> lerComando(){
    string frase; // variavel que vai armazenar o comando digitado
    vector<string> comando; // vetor que vai armazenar os comandos
    string aux; // auxiliar que vai receber cada comando do sstream separado por espaço
    getline(cin, frase); // leitura do comando digitado

    stringstream ss(frase); // inicializa o ss com a string digitada
    // joga no vetor cada palavra separada por espaço
    while(ss >> aux){ 
        comando.push_back(aux);
    }

    // retorna um vetor com os comandos
    return comando;
}

// funçao que exibe o cabeçalho dos comandos disponíveis
void mostrarAjuda(){
    cout << "=====================================================================================================" << endl;
    cout << "|sair ----------------------------------------------------------------------------- fecha o programa|" << endl;
    cout << "|criar n m ------------------------------------------------ cria uma matriz com n linhas e m colunas|" << endl;
    cout << "|mostrar i --------------------------------------------------- mostra a matriz na posicao i do vetor|" << endl;
    cout << "|soma i j ----------------------------------- soma uma matriz na posicao i com a matriz na posicao j|" << endl;
    cout << "|sub i j --------------------------------- subtrai uma matriz na posicao i com a matriz na posicao j|" << endl;
    cout << "|mult i j ----------------------------- multiplica uma matriz na posicao i com a matriz na posicao j|" << endl;
    cout << "|limpar i ----------------------------------------------------- limpa a matriz na posicao i do vetor|" << endl;
    cout << "|ler m.txt ------------------------------ cria uma matriz sparsa baseada no arquivo com nome 'm.txt'|" << endl;
    cout << "|remover i n m ------------------ remove uma valor na posicao (n, m) da matriz na posicao i do vetor|" << endl;
    cout << "|atualizar i n m valor ----------- coloca um valor na posicao (n, m) da matriz na posicao i do vetor|" << endl;
    cout << "|listar ------------------------------------------------------- lista as matrizes que estao no vetor|" << endl;
    cout << "|apagarTudo --------------------------------------------- apaga todas as matrizes atuais do programa|" << endl;
    cout << "=====================================================================================================" << endl;
}

int main(){
    cout << "Seja bem-vinde ao sistema de Matrizes Esparsas!" << endl;
    cout << "Digite 'ajuda' para ver a lista de comandos disponiveis" << endl; 

    // um vetor de ponteiros para objetos do tipo SparseMatrix que vai armazenar as matrizes
    vector<SparseMatrix*> listaMatriz;

    // laço while principal que vai rodar os comandos escritos pelo usuário no terminal
    while(true){
        // vetor de string que chama a função que vai conter os comandos do usuario
        // que vai resetar a cada iteração para receber novos comandos
        vector<string> comando = lerComando();

        // verificação para saber se o usuário não escreveu algo
        // e solicitar um comando
        if(comando.empty()){
            cout << "Escreva um comando valido." << endl;
            continue;
        }
        
        // verifica se a primeira posição do vetor está escrito 'ajuda' 
        // e retorna o cabeçalho contendo os de comandos
        // após o retorno ele reinicia o laço while para receber um novo comando
        if(comando[0] == "ajuda"){
            mostrarAjuda();
            continue;
        }

        // comando sair que encerra o laço while caso o usuário escreva o comando 'sair'
        if(comando[0] == "sair"){
            cout << "Encerrando sistema..." << endl;
            break;
        }

        // comando criar
        // primeiro ele verifica se o usuario usou o comando criar e verifica o tamanho do comando para ver se está de acordo com o exigido
        if(comando[0] == "criar" && comando.size() == 3){
            // usa o try-catch para quando houver uma exceção avisar o usuário mas não sair do laço while
            try{
                // verifica se os valores n e m são realmente inteiros antes do stoi, já que ele não verifica e converte direto
                if((comando[1].find(".") != string::npos || comando[1].find(",") != string::npos) &&
                 (comando[2].find(".") != string::npos || comando[2].find(",") != string::npos)){
                    throw invalid_argument("valor int nao inserido");
                }

                //converte de string para inteiro
                int n = stoi(comando[1]);
                int m = stoi(comando[2]);

                // cria um ponteiro apontando para uma nova matriz e guarda esse ponteiro na ultima posição do vetor de matrizes
                SparseMatrix* novaMatriz = new SparseMatrix(n, m);
                listaMatriz.push_back(novaMatriz);
                cout << "matriz " << listaMatriz.size() - 1 << " foi criada com sucesso!" << endl;
                continue;
            }
            // aqui no catch ele vai exibir ou exeção de valores não inteiros ou a exeção do construtor de indices invalidos
            catch(const invalid_argument& e){
                cout << "erro: tipo do indice inserido e invalido, insira valores inteiros." << endl;
                continue;
            }catch(const out_of_range& e){
                cout << "erro: valores invalidos para criacao de matriz." << endl;
                continue;
            }
        }

        // comando mostrar matriz
        // faz a verificação do comando digitado pelo usuario e usa o try-catch para avisar se há exeções sem sair do while
        if(comando[0] == "mostrar" && comando.size() == 2){
            try{
                // verifica se o valor é inteiro já que a conversão do stoi não verifica
                if(comando[1].find(".") != string::npos || comando[1].find(",") != string::npos){
                    throw invalid_argument("valor int nao inserido");
                }

                //converte string para inteiro
                int i = stoi(comando[1]);
                
                // verifica se a lista para matriz está preenchida
                // se não, verifica se o valor digitado corresponde a uma matriz da lista
                // caso seja ele chama a função print e imprime a matriz no terminal
                // caso não ele avisa que não há matrizes na posição solicitada
                if(listaMatriz.empty()){
                    cout << "sua lista de matriz esta vazia, adicione uma matriz." << endl;
                    continue;
                }else if(i == 0 || i < listaMatriz.size()){
                    listaMatriz[i]->print();
                    continue;
                }else{
                    cout << "nao existe matriz nessa posicao, digite uma posicao valida." << endl;
                    continue;
                }
                
            //catch que notifica o erro quando o indice não é inteiro
            }catch(const invalid_argument& e){
                cout << "erro: tipo do indice inserido e invalido, insira valores inteiros." << endl;
                continue;
            }
        }

        // comando soma
        // faz a verificação do comando digitado pelo usuario e usa o try-catch para avisar se há exeções sem sair do while
        if(comando[0] == "soma" && comando.size() == 3){
            try{
                // verifica antes da conversão se os valores são inteiros
                if((comando[1].find(".") != string::npos || comando[1].find(",") != string::npos) &&
                (comando[2].find(".") != string::npos || comando[2].find(",") != string::npos)){
                    throw invalid_argument("valor int nao inserido");
                }

                // converte os valores de string para inteiro
                int i = stoi(comando[1]);
                int j = stoi(comando[2]);

                // verifica se o valor digitado é uma posição válida na lista de matrizes
                // caso não seja avisa que uma das posições de matrizes pedida é invalida para o vetor de matrizes
                // caso seja, cria um ponteiro que recebe o resultado da função somar que foi chamada
                if(i < listaMatriz.size() && j < listaMatriz.size()){
                    SparseMatrix* aux = sum(listaMatriz[i], listaMatriz[j]);
                    cout << "soma das matrizes " << i << " e " << j << endl;
                    aux->print();

                    // string que vai ser usada na hora de verificar se salva ou não a matriz gerada pela soma
                    string conf; 
                    cout << "deseja salvar essa matriz na sua lista? (s/n)" << endl;
                    
                    // laço while que vai rodar os comandos
                    while (true) {
                        cin >> conf; // inicialização da variavel de comando
            
                        // se 's' coloca a matriz gerada na última posição do vetor de matrizes
                        // dá um cin.ignore() para não ler o espaço do enter na próxima digitação e sai do interno laço
                        // se 'n' apenas deleta o ponteiro
                        // se o usuario digitar errado avisa e pede para escrever novamente
                        if (conf == "s") {
                            listaMatriz.push_back(aux);
                            cout << "matriz salva na posicao " << listaMatriz.size() - 1 << "!" << endl;
                            cin.ignore();
                            break;
                        } else if (conf == "n") {
                            delete aux;
                            cout << "matriz descartada." << endl;
                            cin.ignore();
                            break;
                        } else {
                            cout << "entrada invalida, digite 's' para salvar ou 'n' para descartar." << endl;
                        }
                    }
                    continue;

                }else{
                    cout << "uma das matrizes nao existe, insira uma matriz valida." << endl;
                    continue;
                }
            }
            // esses catchs vão notificar ou a exeção do valor não ser inteiro ou a exeção da função somar
            catch(const invalid_argument& e){
                cout << "erro: tipo do indice inserido e invalido, insira valores inteiros." << endl;
                continue;
            }catch(const out_of_range& e){
                cout << "erro: as matrizes nao podem ser somadas." << endl;
                continue;
            }
        }

        // comando de subtração
        //faz a verificação do comando digitado pelo usuario e usa o try-catch para avisar se há exeções sem sair do while    
        if(comando[0] == "sub" && comando.size() == 3){
            try{
                // verifica antes da conversão se os valores são inteiros
                if((comando[1].find(".") != string::npos || comando[1].find(",") != string::npos) &&
                (comando[2].find(".") != string::npos || comando[2].find(",") != string::npos)){
                    throw invalid_argument("valor int nao inserido");
                }

                // converte os valores de string para inteiro
                int i = stoi(comando[1]);
                int j = stoi(comando[2]);

                // verifica se o valor digitado é uma posição válida na lista de matrizes
                // caso não seja avisa que uma das posições de matrizes pedida é invalida para o vetor de matrizes
                // caso seja, cria um ponteiro que recebe o resultado da função subtração que foi chamada
                if(i < listaMatriz.size() && j < listaMatriz.size()){
                    SparseMatrix* aux = subtraction(listaMatriz[i], listaMatriz[j]);
                    cout << "subtracao das matrizes " << i << " e " << j << endl;
                    aux->print();

                    // string que vai ser usada na hora de verificar se salva ou não a matriz gerada pela soma
                    string conf;
                    cout << "deseja salvar essa matriz na sua lista? (s/n)" << endl;
                    
                    // laço while que vai rodar os comandos
                    while (true) {
                        cin >> conf; // inicialização da variavel de comando
            
                        // se 's' coloca a matriz gerada na última posição do vetor de matrizes
                        // dá um cin.ignore() para não ler o espaço do enter na próxima digitação e sai do interno laço
                        // se 'n' apenas deleta o ponteiro
                        // se o usuario digitar errado avisa e pede para escrever novamente
                        if (conf == "s") {
                            listaMatriz.push_back(aux);
                            cout << "matriz salva na posicao " << listaMatriz.size() - 1 << "!" << endl;
                            cin.ignore();
                            break;
                        } else if (conf == "n") {
                            delete aux;
                            cout << "matriz descartada." << endl;
                            cin.ignore();
                            break;
                        } else {
                            cout << "entrada invalida, digite 's' para salvar ou 'n' para descartar." << endl;
                        }
                    }
                    continue;

                }else{
                    cout << "uma das matrizes nao existe, insira uma matriz valida." << endl;
                    continue;
                }
            }
            // esses catchs vão notificar ou a exeção do valor não ser inteiro ou a exeção da função subtrair
            catch(const invalid_argument& e){
                cout << "erro: tipo do indice inserido e invalido, insira valores inteiros." << endl;
                continue;
            }catch(const out_of_range& e){
                cout << "erro: as matrizes nao podem ser subtraidas." << endl;
                continue;
            }
        }

        // comando multiplicar
        //faz a verificação do comando digitado pelo usuario e usa o try-catch para avisar se há exeções sem sair do while    
        if(comando[0] == "mult" && comando.size() == 3){
            try{
                // verifica antes da conversão se os valores são inteiros
                if((comando[1].find(".") != string::npos || comando[1].find(",") != string::npos) &&
                (comando[2].find(".") != string::npos || comando[2].find(",") != string::npos)){
                    throw invalid_argument("valor int nao inserido");
                }

                // converte os valores de string para inteiro
                int i = stoi(comando[1]);
                int j = stoi(comando[2]);

                // verifica se o valor digitado é uma posição válida na lista de matrizes
                // caso não seja avisa que uma das posições de matrizes pedida é invalida para o vetor de matrizes
                // caso seja, cria um ponteiro que recebe o resultado da função multiplicar que foi chamada
                if(i < listaMatriz.size() && j < listaMatriz.size()){
                    SparseMatrix* aux = multiply(listaMatriz[i], listaMatriz[j]);
                    cout << "multiplicacao das matrizes " << i << " e " << j << endl;
                    aux->print();

                    // string que vai ser usada na hora de verificar se salva ou não a matriz gerada pela soma
                    string conf;
                    cout << "deseja salvar essa matriz na sua lista? (s/n)" << endl;
                    
                    //laço while que vai rodar os comandos
                    while (true) {
                        cin >> conf; // inicialização da variavel de comando
            
                        // se 's' coloca a matriz gerada na última posição do vetor de matrizes
                        // dá um cin.ignore() para não ler o espaço do enter na próxima digitação e sai do interno laço
                        // se 'n' apenas deleta o ponteiro
                        // se o usuario digitar errado avisa e pede para escrever novamente
                        if (conf == "s") {
                            listaMatriz.push_back(aux);
                            cout << "matriz salva na posicao " << listaMatriz.size() - 1 << "!" << endl;
                            cin.ignore();
                            break;
                        } else if (conf == "n") {
                            delete aux;
                            cout << "matriz descartada." << endl;
                            cin.ignore();
                            break;
                        } else {
                            cout << "entrada invalida, digite 's' para salvar ou 'n' para descartar." << endl;
                        }
                    }
                    continue;

                }else{
                    cout << "uma das matrizes nao existe, insira uma matriz valida." << endl;
                    continue;
                }
            }
            // esses catchs vão notificar ou a exeção do valor não ser inteiro ou a exeção da função multiplicar
            catch(const invalid_argument& e){
                cout << "erro: tipo do indice inserido e invalido, insira valores inteiros." << endl;
                continue;
            }catch(const out_of_range& e){
                cout << "erro: as matrizes nao podem ser multiplicadas." << endl;
                continue;
            }
        }

        // comando limpar
        // faz a verificação do comando digitado pelo usuario e usa o try-catch para avisar se há exeções sem sair do while    
        if(comando[0] == "limpar" && comando.size() == 2){
            try{
                // verifica antes da conversão se o valor é inteiro
                if(comando[1].find(".") != string::npos || comando[1].find(",") != string::npos){
                    throw invalid_argument("valor int nao inserido");
                }

                // converte de string para inteiro
                int i = stoi(comando[1]);

                // verifica se a lista está vazia, se não for o caso
                // verifica se a posição da matriz pedida está na lista 
                // caso esteja chama a função clear e notifica que a limpeza deu certo
                // se não, avisa que a matriz não existe naquela posição
                if(listaMatriz.empty()){
                    cout << "sua lista de matriz esta vazia, adicione uma matriz." << endl;
                    continue;
                }else if(i == 0 || i < listaMatriz.size()){
                    listaMatriz[i]->clear();
                    cout << "matriz " << i << " foi limpa com sucesso." << endl;
                    continue;
                }else{
                    cout << "nao existe matriz nessa posicao, digite uma posicao valida." << endl;
                    continue;
                }
            }
            //esse catch é apenas para notificar que o valor da posição pedida não é um valor inteiro
            catch(const invalid_argument& e){
                cout << "erro: tipo do indice inserido e invalido, insira valores inteiros." << endl;
                continue;
            }  
        }

        // comando remover
        // faz a verificação do comando digitado pelo usuario e usa o try-catch para avisar se há exeções sem sair do while
        if(comando[0] == "remover" && comando.size() == 4){
            try{
                // verifica antes da conversão se os valores são inteiros
                if((comando[1].find(".") != string::npos || comando[1].find(",") != string::npos) &&
                (comando[2].find(".") != string::npos || comando[2].find(",") != string::npos) && 
                (comando[3].find(".") != string::npos || comando[3].find(",") != string::npos)){
                    throw invalid_argument("valor int nao inserido");
                }

                // converte os valores de string para inteiro
                int i = stoi(comando[1]);
                int n = stoi(comando[2]);
                int m = stoi(comando[3]);

                // verifica se a lista está vazia, se não for o caso
                // verifica se a posição da matriz pedida está na lista
                // caso esteja chama a função remove e notifica que a remoção deu certo
                // se não, avisa que a matriz não existe naquela posição
                if(listaMatriz.empty()){
                    cout << "sua lista de matriz esta vazia nao ha o que remover." << endl;
                    continue;
                }else if(i == 0 || i < listaMatriz.size()){
                    listaMatriz[i]->remove(n, m);
                    cout << "valor removido com sucesso." << endl;
                    continue;
                }else{
                    cout << "nao existe matriz nessa posicao, digite uma posicao valida." << endl;
                    continue;
                }
            }
            // esses catchs vão notificar ao usuário caso os valores digitados não sejam inteiros
            // caso a posição em que se pede a remoção não exista
            // ou caso não haja nó para remover
            catch(const invalid_argument& c){
                cout << "erro: tipo do indice inserido e invalido, insira valores inteiros." << endl;
                continue;
            }catch(const out_of_range& c){
                cout << "erro: posicao da matriz invalida." << endl;
                continue;
            }catch(const runtime_error& c){
                cout << "erro: nao ha no nessa posicao da matriz." << endl;
                continue;
            }
        }

        // comando de apagarTudo
        // faz a verificação do comando digitado pelo usuario
        if(comando[0] == "apagarTudo"){
            // caso a lista esteja vazia avisa que não tem o que apagar
            if(listaMatriz.empty()){
                cout << "nao ha matrizes no vetor para serem removidas." << endl;
                continue;
            }

            // caso tenha algo, vai chamar o destrutor para cada ponteiro
            // para liberar a memória de cada matriz da lista
            for(int i = 0; i < listaMatriz.size(); i++){
                delete listaMatriz[i];
            }

            // limpa a lista e notifica que deu certo
            listaMatriz.clear();
            cout << "lista de matrizes apagada com sucesso!" << endl;
            continue;
        }


        // comando ler
        // faz a verificação do comando digitado pelo usuario e usa o try-catch para avisar se há exeções sem sair do while
        if(comando[0] == "ler" && comando.size() == 2){
            try{
                // cria um ponteiro para uma matriz default
                SparseMatrix *matriz;

                // chama a função de ler documento colocando o ponteiro apontando uma matriz existente
                readSparseMatrix(matriz, comando[1]);
                // insere essa matriz na lista e notifica o usuário que o comando deu certo
                listaMatriz.push_back(matriz);
                cout << "matriz do arquivo foi inserida na posicao " << listaMatriz.size()-1 << " com sucesso!" << endl;
                continue;
            }
            // esse catch notifica o usuário de que o arquivo digitado não pode ser lido caso digite um valor inválido
            catch(const runtime_error& e){
                cout << "erro: arquivo nao pode ser lido." << endl;
                continue;
            }  
        }

        // comando atualizar
        // faz a verificação do comando digitado pelo usuario e usa o try-catch para avisar se há exeções sem sair do while
        if(comando[0] == "atualizar" && comando.size() == 5){
            try{
                // verifica antes da conversão se os valores são inteiros e se o valor que vai ser inserido é double
                if((comando[1].find(".") != string::npos || comando[1].find(",") != string::npos) &&
                (comando[2].find(".") != string::npos || comando[2].find(",") != string::npos) && 
                (comando[3].find(".") != string::npos || comando[3].find(",") != string::npos) &&
                (comando[4].find(".") == string::npos || comando[4].find(",") == string::npos)){
                    throw invalid_argument("valor int ou double nao inserido");
                }

                // converte os valores de string para int e double
                int i = stoi(comando[1]);
                int n = stoi(comando[2]);
                int m = stoi(comando[3]);
                double value = stod(comando[4]);

                // verifica se a lista está vazia, se não for o caso
                // verifica se a posição da matriz pedida está na lista
                // caso esteja chama a função inserte para inserir o valor e notifica que a atualização deu certo
                // se não, avisa que a matriz não existe naquela posição
                    if(listaMatriz.empty()){
                        cout << "sua lista de matriz esta vazia, adicione uma matriz." << endl;
                        continue;
                    }else if(i == 0 || i < listaMatriz.size()){
                        listaMatriz[i]->insert(n, m, value);
                        cout << "posicao (" << n << ", " << m << ") da matriz " << i << " foi atualizada com o valor" << value << " com sucesso!" << endl;
                        continue;
                    }else{
                        cout << "nao existe matriz nessa posicao, digite uma posicao valida." << endl;
                        continue;
                    }
            }
            // esses catchs vão notificar ao usuário caso os valores digitados não sejam inteiro ou double
            // ou se a posição que se deseja atualizar não exista na matriz
            catch(const invalid_argument& e){
                cout << "erro: valores invalidos para atualizacao de matriz. Verifique se indice e posicao passados sao inteiros e o valor double." << endl;
                continue;
            }catch(const out_of_range& e){
                cout << "erro: posicao da matriz invalida." << endl;
                continue;
            }
        }

        // comando listas
        // faz a verificação do comando digitado pelo usuario
        if(comando[0] == "listar"){       
            // verifica se a lista não está vazia
            if(listaMatriz.empty()){
                cout << "nao ha nenhuma matriz registrada, insira uma matriz na lista." << endl;
                continue;
            }

            // Define o tamanho padrão de cada coluna da tabela que é mostrada no terminal
            int tamanho_coluna = 10;

            // Define a largura total da tabela mostrada no terminal
            int largura_total = tamanho_coluna * 4 + 5;
            
            // Imprime uma linha reta pontilhda no terminal
            for(int i = 0; i < largura_total; ++i){
                cout << "-";
            }

            // Quebra de linha
            cout << "\n";

            // Cabeçalho da tabela que aparece no terminal
            cout << "|" << setw(tamanho_coluna) << left << "Index" << "|";
            cout << setw(tamanho_coluna) << left << "Nome" << "|";
            cout << setw(tamanho_coluna) << left << "Dimensao" << "|";
            cout << setw(tamanho_coluna) << left << "Elementos" << "|";
            

            // Quebra de linha
            cout << "\n";

            // Percorre a lista de matrizes
            for(int i = 0; i < listaMatriz.size(); i++){

                // Criação de strings com as informações que aparecem na tabela de matrizes
                string nome = ("Matriz " + to_string(i));
                string dimensao = (to_string(listaMatriz[i]->getLinhas()) + " x " + to_string(listaMatriz[i]->getColunas()));
                string elementos = (to_string(listaMatriz[i]->getQntNos()));

                // Imprime uma barra no início de cada linha
                cout << "|" << setw(tamanho_coluna) << left << i << "|";

                // Formatação das colunas
                cout << setw(tamanho_coluna) << left << nome << "|";
                cout << setw(tamanho_coluna) << left << dimensao << "|";
                cout << setw(tamanho_coluna) << left << elementos << "|";
                cout << endl;
            }

            // Imprime uma linha reta pontilhda no terminal
            for(int i = 0; i < largura_total; ++i){
                cout << "-";
            }
            // Quebra de linha
            cout << "\n";
            continue;
        }

        // caso o que foi digitado não passar por nenhum comando avisa ao usuário que o comando passado é inválido
        cout <<  "comando invalido. Cheque 'ajuda' para ver os comandos disponiveis" << endl;
    }

    return 0;
}