#include <iostream>
#include "../src/matrix.hpp"
using std::cout;
using std::cin;
using std::endl;
using ms::Matrix;
using std::vector;

int main(){
    Matrix m1({                //m2({{},{},{}...}) or without ()
        {2,3,4,5},
        {1,2,3,5},
        {3,2,1,5},
        {2,3,1,5}
    });
    vector<vector<double>> vec = {                
        {2,3,1},
        {1,2,3},
        {3,2,4}
    };
    Matrix m2(vec);
   
   cout<<m1;  
}