#include <iostream>
#include <fstream>
#include "SparseMatrix.h"

int main(){
    SparseMatrix matriz(3,3);
    matriz.insert(1, 1, 99);
    matriz.insert(1, 3, 87);
    matriz.insert(1, 1, 100);
    matriz.insert(2, 1, 24);
    matriz.insert(1,2, 17);
    std::cout << matriz.get(1,1) << std::endl;
    std::fstream file("arquivo.txt");

    matriz.print();

    if(file.is_open()){
        int x, y;
        file >> x;
        file >> y;
        std::cout << x + y << " " << x << " " << y << std::endl;
    }
}

//! soma, multiplicação de matrizes e mais uns coiso, na main;