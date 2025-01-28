#include <iostream>
#include <fstream>
#include "SparseMatrix.h"

int main(){
    SparseMatrix matriz(3,3);
    matriz.insert(1, 1, 99);
    matriz.insert(1, 3, 87);
    matriz.insert(1, 1, 100);
    matriz.insert(2, 1, 24);
    std::cout << matriz.get(1,1) << std::endl;
    std::fstream file("arquivo.txt");

    matriz.clear();
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