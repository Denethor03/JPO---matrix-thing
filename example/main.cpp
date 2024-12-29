#include <iostream>
#include "../include/matrix.hpp"
#include <cstdlib>

using std::cout;
using std::cin;
using namespace ms; // <- I hope you'll forgive my sins


int main(){
    cout<<"============================================================================\n";
    cout<<"Object \"Matrix\" can be initialized in 3 ways:\n";
    cout<<"1. By creating matrix with specific dimensions: Matrix<double> m1(3,3); \n";
    Matrix<double> m1(3,3);
    cout<<m1;
    cout<<"2. The same way, but with specific value: Matrix<double> m2(3,3,2.5);\n";
    Matrix<double> m2(3,3,2.5);
    cout<<m2;
    cout<<"3. Or by passing vector: Matrix<double> m3({{1,2,3},{1,2,3},{1,2,3}})\n";
    cout<<"In that case, every row must have the same length\n";
    Matrix<double> m3({{1,2,3},{4,5,6},{7,8,9}});
    cout<<m3;
    cout<<"All matrices can be displayed using \"cout<<\"\n";
    cout<<"[Enter to continue]";
    cin.get();
    cout<<"============================================================================\n";
    cout<<"Matrix elements can be accessed using [] operator: m3[0]:\n";
    cout<<m1[0]<<"   --- first row is displayed\n";
    cout<<"m1[0][2]\n";
    cout<<m1[0][2]<<"   --- 3rd element of first row\n";
    cout<<"It is possible to change value: m3[0] = {2,1,3}\n";
    m3[0] = {2,1,3};
    cout<<m3;
    cout<<"[Enter to continue]";
    cin.get();
    cout<<"============================================================================\n";
    cout<<"Every basic operation is supported (+,-,*,/ and = counterparts)\n";
    cout<<"Examples shown on m2 and m3 (excluding division)\n";
    cout<<"1. Addition:\n";
    cout<<(m2+m3);
    cout<<"2. Subtraction:\n";
    cout<<(m2-m3);
    cout<<"3. Multiplication:\n";
    cout<<(m2*m3);
    cout<<"4. Division: (divide m3 by eg. 3)\n";
    cout<<(m3/3);
    cout<<"[Enter to continue]";
    cin.get();
    cout<<"============================================================================\n";
    cout<<"We can multiply by single value as well. Works both ways: 2.0*m3:\n";
    cout<<(2.0*m3);
    cout<<"m3*2.0:\n";
    cout<<(m3*2);
    cout<<"[Enter to continue]";
    cin.get();
    cout<<"============================================================================\n";
    cout<<"It is possible to add column: m3.addColumn({0,0,0}):\n";
    m3.addColumn({0,0,0});
    cout<<m3;
    cout<<"Or row: m3.addRow({0,0,0,0}):\n";
    m3.addRow({0,0,0,0});
    cout<<m3;
    cout<<"We can reverse it by using remRow() remColumn() which remove last elements:\n";
    m3.remColumn();
    m3.remRow();
    cout<<m3;
    cout<<"[Enter to continue]";
    cin.get();
    cout<<"============================================================================\n";
    cout<<"Basic algorithm (very inefficient) is implemented to calculate determinant: m3.det():\n";
    cout<<m3.det()<<"\n";
    cout<<"Works only on square matrices\n";
    cout<<"It is also possible to transpose matrix; let's use that function on following matrix:\n";
    m3.addRow({3,3,2});
    cout<<m3;
    cout<<"After m3.transpose():\n";
    m3.transpose();
    cout<<m3;
    cout<<"[Enter to continue]";
    cin.get();
    cout<<"============================================================================\n";
    cout<<"Matrices can be of different types (int, float, etc., previously used double as example)\n";
    cout<<"They also accept ComplexNumber as type: Matrix<ComplexNumber> c1(3,3,complex1):\n";
    ComplexNumber<double> complex1(1,2);
    Matrix<ComplexNumber<double>> c1(3,3,complex1);
    cout<<c1;
    cout<<"Every operation described earlier work on that type, eg. multiplication (c1*c1):\n";
    cout<<(c1*c1);
    cout<<"or determinant (in that case 0):\n";
    cout<<c1.det()<<"\n";
    cout<<"Matrix of chars is also possible (for whatever reason you need that)\n";
    Matrix<char> ch1(3,3,'b');
    cout<<ch1;
    cout<<"[Enter to continue]";
    cin.get();
    cout<<"============================================================================\n";
    cout<<"There's also SquareMatrix and IdentityMatrix. They work very similiar to Matrix, but have some restrictions.\n";
    cout<<"SquareMatrix has every previous operation exept the ones that modify its dimensions\n";
    cout<<"IdentityMatrix cannot be modified, only used in different operations\n";
    IdentityMatrix<double> i1(4);
    cout<<"IdentityMatrix<double i1(4):\n";
    SquareMatrix<double> s1({{2,1,3},{4,2,1},{6,2,1}});
    cout<<i1;
    cout<<"SquareMatrix<double> s1({{2,1,3},{4,2,1},{6,2,1}}):\n";
    cout<<s1<<"\n";
    cout<<"There are more \"manual\" functions to get specific values, dimensions or to print matrix,\n";
    cout<<"but there's no point in showcasing them since they are used inside class or have alternatives\n";

}

