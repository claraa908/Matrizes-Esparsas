if(comando[0] == "criar" && comando.size() == 3){
            try{
                int n = stoi(comando[1]);
                int m = stoi(comando[2]);

                SparseMatrix* novaMatriz = new SparseMatrix(n, m);
                listaMatriz.push_back(novaMatriz);
                cout << "matriz " << listaMatriz.size() - 1 << " foi criada!" << endl;
                continue;
            }
            catch(const invalid_argument& e){
                cout << "erro: tipo do indice inserido e invalido, insira valores inteiros." << endl;
                continue;
            }catch(const out_of_range& e){
                cout << "erro: valores invalidos para criacao de matriz." << endl;
                continue;
            }
        }