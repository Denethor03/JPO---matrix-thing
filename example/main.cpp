#include <iostream>
#include "../src/matrix.hpp"

using namespace std;
using namespace ms;


int main(){
    Matrix m1({                //m2({{},{},{}...}) or without ()
      {1,3,4,1},
      {3,4,1,2},
      {9,1,3,5},
      {2,3,1,6}
    });
    vector<vector<double>> vec = {                
        {1,2,3},
        {4,5,6},
        {7,8,9}
    };
    Matrix m3(vec);
    cout<<det(m1)<<endl;
}