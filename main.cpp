#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <iomanip>
#include "SparseMatrix.h"
using namespace std;

void readSparseMatrix(SparseMatrix*& m, string nome_do_arquivo){

    fstream file(nome_do_arquivo);

    if(!file.is_open()){
        throw out_of_range("Erro ao abrir o arquivo");
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

// Função que soma duas matrizes
SparseMatrix* sum(SparseMatrix* &A, SparseMatrix* &B){

    // Verificação se as duas matrizes possuem o mesmo número de linhas e colunas
    if(A->getLinhas()==B->getLinhas()&&A->getColunas()==B->getColunas()){
        SparseMatrix* matrizSomada=new SparseMatrix(A->getLinhas(), A->getColunas());
            
            for(int i=1;i<=A->getLinhas();i++){
                for(int j=1;j<=A->getColunas();j++){

                    double valorA=A->get(i, j);
                    double valorB=B->get(i, j);

                    double soma=valorA+valorB;

                    matrizSomada->insert(i, j, soma);
                    
                }
            }

            return matrizSomada;
        } else {

        throw out_of_range("Nao e possivel somar essas duas matrizes");
    }
    
}

// Função que subtrai duas matrizes
SparseMatrix* subtraction(SparseMatrix* &A, SparseMatrix* &B){

    // Verificação se as duas matrizes possuem o mesmo número de linhas e colunas
    if(A->getLinhas()==B->getLinhas()&&A->getColunas()==B->getColunas()){
        SparseMatrix* matrizSubtraida=new SparseMatrix(A->getLinhas(), A->getColunas());
            
            for(int i=1;i<=A->getLinhas();i++){
                for(int j=1;j<=A->getColunas();j++){

                    double valorA=A->get(i, j);
                    double valorB=B->get(i, j);

                    double subtracao=valorA-valorB;

                    matrizSubtraida->insert(i, j, subtracao);
                    
                }
            }

            return matrizSubtraida;
        } else {

        throw out_of_range("Nao e possivel subtrair essas duas matrizes");
    }
    
}

SparseMatrix* multiply(SparseMatrix* &A, SparseMatrix* &B){

    if(A->getColunas()==B->getLinhas()){

        SparseMatrix* matrizMultiplicada=new SparseMatrix(A->getLinhas(), B->getColunas());

        double soma=0;

        for(int i=1;i<=A->getLinhas();i++){
            for(int j=1;j<=B->getColunas();j++){

                soma=0;

                for(int k=1;k<=A->getColunas();k++){
                    double valorA=A->get(i, k);
                    double valorB=B->get(k, j);

                    double mult=valorA*valorB;

                    soma+=mult;
                }

                matrizMultiplicada->insert(i, j, soma);
            }
        }

        return matrizMultiplicada;


    } else {
        throw out_of_range("Nao e possivel multiplicar essas duas matrizes");
    }
    
    
}

vector<string> lerComando(){
    string frase;
    getline(cin, frase);
    stringstream ss(frase);
    vector<string> comando;
    string aux;

    while(ss >> aux){
        comando.push_back(aux);
    }

    return comando;
}

//!    PELO AMOR DE DEUS ARRUMA ESSA LISTA DE COMANDOS
void mostrarAjuda(){
    cout << "=======================================================================================" << endl;
    cout << "sair ---------------------------------------------------------------- fechar o programa" << endl;
    cout << "criar n m ----------------------------------- criar uma matriz com n linhas e m colunas" << endl;
    cout << "mostrar i --------------------------------------- mostra a matriz na posicao i do vetor" << endl;
    cout << "soma i j ----------------------- soma uma matriz na posicao i com a matriz na posicao j" << endl;
    cout << "sub i j --------------------- subtrai uma matriz na posicao i com a matriz na posicao j" << endl;
    cout << "mult i j ----------------- multiplica uma matriz na posicao i com a matriz na posicao j" << endl;
    cout << "limpar i ----------------------------------- remove o valor da posicao (n, m) da matriz" << endl;
    cout << "remover i n m ------------------------------------------- limpa uma matriz na posicao i" << endl;
    cout << "ler m.txt ------------------ cria uma matriz sparsa baseada no arquivo com nome 'm.txt'" << endl;
    cout << "atualizar i n m valor --------------- coloca um valor na matriz i na linha n e coluna m" << endl;
    cout << "apagarTudo --------------------------------- apaga todas as matrizes atuais do programa" << endl;
    cout << "=======================================================================================" << endl;
}

int main(){
    cout << "Seja bem-vinde ao sistema de Matrizes Esparsas!" << endl;
    cout << "Digite 'ajuda' para ver a lista de comandos disponiveis" << endl; 
    vector<SparseMatrix*> listaMatriz;

    while(true){
        vector<string> comando;
        comando = lerComando();

        if(comando.empty()){
            cout << "Escreva um comando valido" << endl;
            continue;
        }

        if(comando[0] == "ajuda"){
            mostrarAjuda();
            continue;
        }

        if(comando[0] == "sair"){
            cout << "Encerrando sistema..." << endl;
            break;
        }

        if(comando[0] == "criar" && comando.size() == 3){
            try{
                int n = stoi(comando[1]);
                int m = stoi(comando[2]);

                SparseMatrix* novaMatriz = new SparseMatrix(n, m);
                listaMatriz.push_back(novaMatriz);
                cout << "matriz " << listaMatriz.size() - 1 << " criada!" << endl;
                continue;
            }
            catch(const invalid_argument& e){
                cout << "erro: tipo do indice inserido e invalido" << endl;
            }
        }

        if(comando[0] == "mostrar" && comando.size() == 2){
            try{
                int i = stoi(comando[1]);
                if(listaMatriz.empty()){
                    cout << "sua lista de matriz esta vazia, adicione uma matriz" << endl;
                    continue;
                }else if(i == 0 || i < listaMatriz.size()){
                    listaMatriz[i]->print();
                    continue;
                }else{
                    cout << "nao existe matriz nessa posicao, digite uma posicao valida" << endl;
                    continue;
                }
            }catch(const invalid_argument& e){
                cout << "erro: tipo do indice inserido e invalido" << endl;
            }
        }

        if(comando[0] == "soma" && comando.size() == 3){
            try{
                int i = stoi(comando[1]);
                int j = stoi(comando[2]);

                if(i < listaMatriz.size() && j < listaMatriz.size()){
                    SparseMatrix* aux = sum(listaMatriz[i], listaMatriz[j]);

                    string conf;
                    cout << "deseja salvar essa matriz na sua lista? (s/n)" << endl;
                    
                    while (true) {
                        cin >> conf;
            
                        if (conf == "s") {
                            listaMatriz.push_back(aux);
                            cout << "matriz salva na posicao " << listaMatriz.size() - 1 << "!" << endl;
                            break;
                        } else if (conf == "n") {
                            delete aux;
                            cout << "matriz descartada." << endl;
                            break;
                        } else {
                            cout << "entrada invalida, digite 's' para salvar ou 'n' para descartar." << endl;
                        }
                    }

                }else{
                    cout << "uma das matrizes nao existe, insira uma matriz valida" << endl;
                    continue;
                }
            }catch(const invalid_argument& e){
                cout << "erro: tipo dos indices inseridos sao invalidos" << endl;
            }catch(const out_of_range& b){
                cout << "erro: matrizes nao podem ser somadas";
                continue;
            }
        }

        if(comando[0] == "sub" && comando.size() == 3){
            try{
                int i = stoi(comando[1]);
                int j = stoi(comando[2]);

                if(i < listaMatriz.size() && j < listaMatriz.size()){
                    SparseMatrix* aux = subtraction(listaMatriz[i], listaMatriz[j]);

                    string conf;
                    cout << "deseja salvar essa matriz na sua lista? (s/n)" << endl;
                    
                    while (true) {
                        cin >> conf;
            
                        if (conf == "s") {
                            listaMatriz.push_back(aux);
                            cout << "matriz salva na posicao " << listaMatriz.size() - 1 << "!" << endl;
                            break;
                        } else if (conf == "n") {
                            delete aux;
                            cout << "matriz descartada." << endl;
                            break;
                        } else {
                            cout << "entrada invalida, digite 's' para salvar ou 'n' para descartar." << endl;
                        }
                    }

                }else{
                    cout << "uma das matrizes nao existe, insira uma matriz valida" << endl;
                    continue;
                }
            }catch(const invalid_argument& e){
                cout << "erro: tipo dos indices inseridos sao invalidos" << endl;
            }catch(const out_of_range& b){
                cout << "erro: matrizes nao podem ser somadas";
                continue;
            }
        }

        if(comando[0] == "mult" && comando.size() == 3){
            try{
                int i = stoi(comando[1]);
                int j = stoi(comando[2]);

                if(i < listaMatriz.size() && j < listaMatriz.size()){
                    SparseMatrix* aux = multiply(listaMatriz[i], listaMatriz[j]);

                    string conf;
                    cout << "deseja salvar essa matriz na sua lista? (s/n)" << endl;
                    
                    while (true) {
                        cin >> conf;
            
                        if (conf == "s") {
                            listaMatriz.push_back(aux);
                            cout << "matriz salva na posicao " << listaMatriz.size() - 1 << "!" << endl;
                            break;
                        } else if (conf == "n") {
                            delete aux;
                            cout << "matriz descartada." << endl;
                            break;
                        } else {
                            cout << "entrada invalida, digite 's' para salvar ou 'n' para descartar." << endl;
                        }
                    }

                }else{
                    cout << "uma das matrizes nao existe, insira uma matriz valida" << endl;
                    continue;
                }
            }catch(const invalid_argument& e){
                cout << "erro: tipo dos indices inseridos sao invalidos" << endl;
                
            }catch(const out_of_range& b){
                cout << "erro: matrizes nao podem ser multiplicadas" << endl;
                continue;
            }
        }

        if(comando[0] == "limpar" && comando.size() == 2){
            try{
                int i = stoi(comando[1]);
                if(listaMatriz.empty()){
                    cout << "sua lista de matriz esta vazia, adicione uma matriz" << endl;
                    continue;
                }else if(i == 0 || i < listaMatriz.size()){
                    listaMatriz[i]->clear();
                    continue;
                }else{
                    cout << "nao existe matriz nessa posicao, digite uma posicao valida" << endl;
                    continue;
                }
            }catch(const invalid_argument& e){
                cout << "erro: tipo do indice e invalido" << endl;
                continue;
            }  
        }

        if(comando[0] == "remover" && comando.size() == 4){
            try{
                int i = stoi(comando[1]);
                int n = stoi(comando[2]);
                int m = stoi(comando[3]);

                if(listaMatriz.empty()){
                    cout << "sua lista de matriz esta vazia nao ha o que remover" << endl;
                    continue;
                }else if(i == 0 || i < listaMatriz.size()){
                    listaMatriz[i]->remove(n, m);
                    continue;
                }else{
                    cout << "nao existe matriz nessa posicao, digite uma posicao valida" << endl;
                    continue;
                }
            }catch(const invalid_argument& c){
                cout << "erro: valor do indice ou das posicoes e invalido" << endl;
                continue;
            }catch(const out_of_range& b){
                cout << "erro: indice(s) invalido(s)";
            }
        }

        if(comando[0] == "removerTudo"){
           
            if(listaMatriz.empty()){
                cout<<"nao ha nada para remover"<<endl;
                continue;
            }

            for(int i=0;i<listaMatriz.size();i++){
                listaMatriz.pop_back();
            }

            cout<<"lista de matrizes apagada"<<endl;
            continue;
            
            
        }

        if(comando[0] == "ler" && comando.size() == 2){
            try{
                SparseMatrix *matriz;
                readSparseMatrix(matriz, comando[1]);
                listaMatriz.push_back(matriz);
                cout << "matriz do arquivo inserida" <<  endl;
                continue;
            }catch(const out_of_range& b){
                cout << "erro: arquivo nao pode ser lido" << endl;
                continue;
            }  
        }

        if(comando[0] == "atualizar" && comando.size() == 5){
            try{
                int i = stoi(comando[1]);
                int n = stoi(comando[2]);
                int m = stoi(comando[3]);
                double value = stod(comando[4]);
                    if(listaMatriz.empty()){
                        cout << "sua lista de matriz esta vazia, adicione uma matriz" << endl;
                        continue;
                    }else if(i == 0 || i < listaMatriz.size()){
                        listaMatriz[i]->insert(n, m, value);
                        cout << "posicao (" << n << ", " << m << ") da matriz " << i << " foi atualizada com " << value << endl;
                        continue;
                    }else{
                        cout << "nao existe matriz nessa posicao, digite uma posicao valida" << endl;
                        continue;
                    }
            }catch(const invalid_argument& e){
                cout << "erro: tipo do indice ou posicao ou valor inserido e invalido" << endl;
            }catch(const out_of_range& b){
                cout << "erro: indice(s) invalido(s)" << endl;
                continue;
            }
        }

        if(comando[0] == "index"){
            
            if(listaMatriz.empty()){
                cout<<"nao ha nenhuma matriz registrada, insira uma matriz na lista"<<endl;
                continue;
            }

            int tamanho_coluna=6;
            int largura_total=tamanho_coluna*2+3;
            
            // Imprime uma linha reta pontilhda no terminal
            for(int i=0;i<largura_total;++i){
                std::cout<<"-";
            }
            // Quebra de linha
            std::cout<<"\n";

            for(int i=0;i<listaMatriz.size();i++){
                cout<<i<<"|";
                cout<<setw(tamanho_coluna)<<fixed<<"Matriz "<<i<<"|";
                cout<<endl;
                
            }

            // Imprime uma linha reta pontilhda no terminal
            for(int i=0;i<largura_total;++i){
                std::cout<<"-";
            }
            // Quebra de linha
            std::cout<<"\n";

        }
    }
}