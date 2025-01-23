#include <iostream>
#include <fstream>
#include "SparseMatrix.h"

int main(){
    SparseMatrix matriz(4, 5);
    std::cout << matriz.get(1,1) << std::endl;
    std::cout << 9 << std::endl;
    std::fstream file("arquivo.txt");

    matriz.print();

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