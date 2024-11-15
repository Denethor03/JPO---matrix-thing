#include <iostream>
#include "../src/matrix.hpp"
using std::cout;
using std::cin;
using std::endl;

int main(){
    ms::ComplexNumber<int> c1(2.3,3);
    ms::ComplexNumber<double> c2(2,3);
    cout<<c1;
}