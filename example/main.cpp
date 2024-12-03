#include <iostream>
#include "../src/matrix.hpp"

using namespace std;
using namespace ms;


int main(){
    Matrix<double> m1({
      {2,3,4},
      {1,3,2},
      {1,1,1}
    });
    m1.addRow({1,3,4});
    IdentityMatrix<double> i1(3);
    cout<<i1;
}