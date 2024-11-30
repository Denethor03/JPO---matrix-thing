#include <iostream>
#include "../src/matrix.hpp"

using namespace std;
using namespace ms;


int main(){
    Matrix m1({                //m2({{},{},{}...}) or without ()
      {1,3,4},
      {3,4,1},
      {9,1,3}
    });
    vector<vector<double>> vec = {                
      {1,2,3},
      {4,5,2},
      {7,8,9}
    };
    Matrix s1(vec);
    cout<<s1.det();
  
}