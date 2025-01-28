#include <iostream>
#include <fstream>
#include "SparseMatrix.h"

int main(){
    SparseMatrix matriz(3,3);
    matriz.insert(1, 1, 99);
    matriz.insert(1, 2, 87);
    matriz.insert(1, 3, 100);
    matriz.insert(2, 1, 54);
    matriz.insert(2, 2, 13);
    matriz.insert(2, 3, 256);
    matriz.insert(3, 1, 224);
    matriz.insert(3, 2, 22);
    matriz.insert(3, 3, 315);
    matriz.remove(1,1);
    std::cout << matriz.get(1,1) << std::endl;
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