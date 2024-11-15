#include <iostream>
#include "../src/matrix.hpp"
using std::cout;
using std::cin;
using std::endl;
using ms::Matrix;
using std::vector;

int main(){
    Matrix m1({                //m2({{},{},{}...}) or without ()
        {2,3,4},
        {1,2,3},
        {3,2,1}
    });
    vector<vector<double>> vec = {                
        {2,3,4},
        {1,2,3},
        {3,2,1}
    };
    Matrix m2(vec);
    Matrix m3({                
        {2,3,4},
        {1,2,3}
    });
    m2 = m2*2;
    m2.printMatrix();
}