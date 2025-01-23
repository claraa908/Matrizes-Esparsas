#include <iostream>
#include <fstream>
#include "SparseMatrix.h"

int main(){
    SparseMatrix matriz(1, 2);
    std::cout << matriz.get(1,2) << std::endl;
    std::cout << 9 << std::endl;
    std::fstream file("arquivo.txt");

    if(file.is_open()){
        int x, y;
        file >> x;
        file >> y;
        std::cout << x + y << " " << x << " " << y << std::endl;
    }

    if(matriz.empty()){
        cout<<"vazia";
    }
}

//! soma, multiplicação de matrizes e mais uns coiso, na main;