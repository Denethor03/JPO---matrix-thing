#pragma once
#include <vector>
#include <initializer_list>
#include "../lib/complex.hpp"
#include <iostream>
namespace ms{
    class Matrix{
        private:
            std::vector<std::vector<double>> m_matrix{};
            int m_rows {0};
            int m_columns {0};
            
            void updateDimensions(){
                m_rows = m_matrix.size();
                m_columns = m_matrix[0].size();
            }
        public:
            Matrix(const int& r,const int& c) : m_matrix(r,std::vector<double>(c)) {
                if(r <= 0 || c <= 0){ 
                    throw std::invalid_argument("Matrix dimensions cannot be less than 0");
                }
                updateDimensions();
            }
            Matrix(const int& r,const int& c,const double& val): m_matrix(r,std::vector<double>(c,val)){
                if(r <= 0 || c <= 0){ 
                    throw std::invalid_argument("Matrix dimensions cannot be less than 0");
                }
                updateDimensions();
    
            }
            Matrix(const std::vector<std::vector<double>>& matrix) : m_matrix(matrix){
               // std::cout<<"Test";
                int t_len = matrix[0].size();
                for(int i{}; i<matrix.size(); i++){
                    if(t_len != matrix[i].size()){
                        throw std::invalid_argument("Matrix is not a rectangle uhh idk");
                    }
                }
                updateDimensions();
            }
            
            double getVal(const int& r,const int& c)const{
                return m_matrix[r][c];
            }
            void setVal(const int& r,const int& c,const double& val){
                m_matrix[r][c] = val;
            }
            double getRows()const{
                return m_rows;
            }
            double getColumns()const{
                return m_columns;
            }
            void printMatrix()const{
                for(int i {}; i<m_rows; i++){
                    for(int j {}; j<m_columns; j++){
                        std::cout<<m_matrix[i][j]<<" ";
                    }
                    std::cout<<"\n";
                }
            }
            void addRow(const std::vector<double>& vec){
                if(vec.size()!=m_columns){
                    std::cout<<"Cannot add row: wrong size\n";
                }
                else{
                    m_matrix.push_back(vec);
                    updateDimensions();
                    
                }
            }
            Matrix operator+(const Matrix& other)const{
                std::vector<std::vector<double>> temp_vector(m_rows,std::vector<double>(m_columns));
                if(m_columns != other.m_columns || m_rows != other.m_rows){
                   throw std::invalid_argument("Cannot add matrices: dimensions don't match");
                }
                else{
                    
                    for(int i {}; i<m_rows; i++){
                        for(int j {}; j<m_columns; j++){
                            temp_vector[i][j] = m_matrix[i][j] + other.m_matrix[i][j];
                        } 
                    } 
                }
                return Matrix(temp_vector);
            }

            Matrix& operator+=(const Matrix& other){
                std::vector<std::vector<double>> temp_vector(m_rows,std::vector<double>(m_columns));
                if(m_columns != other.m_columns || m_rows != other.m_rows){
                   throw std::invalid_argument("Cannot add matrices: dimensions don't match\n");
                }
                else{
                    
                    for(int i {}; i<m_rows; i++){
                        for(int j {}; j<m_columns; j++){
                            m_matrix[i][j] += other.m_matrix[i][j];
                        } 
                    } 
                }
                return *this;
            }

             Matrix operator-(const Matrix& other)const{
                std::vector<std::vector<double>> temp_vector(m_rows,std::vector<double>(m_columns));
                if(m_columns != other.m_columns || m_rows != other.m_rows){
                   throw std::invalid_argument("Cannot add matrices: dimensions don't match");
                }
                else{
                    
                    for(int i {}; i<m_rows; i++){
                        for(int j {}; j<m_columns; j++){
                            temp_vector[i][j] = m_matrix[i][j] - other.m_matrix[i][j];
                        } 
                    } 
                }
                return Matrix(temp_vector);
            }

            Matrix& operator-=(const Matrix& other){
                std::vector<std::vector<double>> temp_vector(m_rows,std::vector<double>(m_columns));
                if(m_columns != other.m_columns || m_rows != other.m_rows){
                   throw std::invalid_argument("Cannot add matrices: dimensions don't match\n");
                }
                else{
                    
                    for(int i {}; i<m_rows; i++){
                        for(int j {}; j<m_columns; j++){
                            m_matrix[i][j] -= other.m_matrix[i][j];
                        } 
                    } 
                }
                return *this;
            }

            bool operator==(const Matrix& other)const{
                if(m_rows != other.m_rows || m_columns != other.m_columns){
                    return false;
                }
                for(int i {}; i<m_rows; i++){
                    for(int j {}; j<m_columns; j++){
                        if(m_matrix[i][j] != other.m_matrix[i][j]){ 
                            return false;
                        }       
                    } 
                }
                return true;
            }

            bool operator!=(const Matrix& other)const{
                return !operator==(other);
            }

            Matrix operator*(const double& other)const{
                std::vector<std::vector<double>> temp_vector(m_rows,std::vector<double>(m_columns));
                for(int i {}; i<m_rows; i++){
                        for(int j {}; j<m_columns; j++){
                            temp_vector[i][j] = m_matrix[i][j]*other;
                        } 
                    }
                return Matrix(temp_vector);
            }

             Matrix& operator*=(const double& other){
                for(int i {}; i<m_rows; i++){
                        for(int j {}; j<m_columns; j++){
                            m_matrix[i][j]*=other;
                        } 
                    }
                return *this;
            }

            Matrix operator/(const double& other)const{
                std::vector<std::vector<double>> temp_vector(m_rows,std::vector<double>(m_columns));
                for(int i {}; i<m_rows; i++){
                        for(int j {}; j<m_columns; j++){
                            temp_vector[i][j] = m_matrix[i][j]/other;
                        } 
                    }
                return Matrix(temp_vector);
            }

            Matrix operator/=(const double& other){
                for(int i {}; i<m_rows; i++){
                        for(int j {}; j<m_columns; j++){
                            m_matrix[i][j]/=other;
                        } 
                    }
                return *this;
            }

            friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix){
                for(int i {}; i<matrix.m_rows; i++){
                    for(int j {}; j<matrix.m_columns; j++){
                        os<<matrix.m_matrix[i][j]<<" ";
                    }
                    os<<std::endl;
                }
                return os;
            }

                  

            void addColumn(const std::vector<double>& vec){
                if(vec.size()!=m_rows){
                    throw std::invalid_argument("Cannot add column: wrong size");
                }else{
                    for(int i{}; i<m_rows; i++){
                        m_matrix[i].push_back(vec[i]);
                    }
                }
                updateDimensions();
            }

            Matrix operator*(const Matrix& other){
                std::vector<std::vector<double>> result(m_rows,std::vector<double>(other.m_columns));
                if(m_columns!=other.m_rows){
                     throw std::invalid_argument("Cannot multiply matrices: number of columns must be equal to number of rows.");
                }else{
                   
                    for(int i{}; i<m_rows;i++){
                        for(int j{};j<m_columns;j++){
                            for(int k{};k<m_columns;k++){
                                result[i][j] += m_matrix[i][k]*other.m_matrix[k][j];
                            }
                        }
                   } 
                }
                return Matrix(result);
            }

            friend double det(const Matrix& matrix);
            friend Matrix operator*(const double& scalar, const Matrix& matrix);
    };

    Matrix operator*(const double& scalar, const Matrix& matrix){
        std::vector<std::vector<double>> temp_vector(matrix.m_rows,std::vector<double>(matrix.m_columns));
        for(int i {}; i<matrix.m_rows; i++){
            for(int j {}; j<matrix.m_columns; j++){
                temp_vector[i][j] = matrix.m_matrix[i][j]*scalar;
            } 
        }
        return Matrix(temp_vector);
    }

    class IdentityMatrix : public Matrix{
        public:
            IdentityMatrix(const int& size) : Matrix(size,size){
                for(int i{}; i<size; i++){
                    setVal(i,i,1);
                }
            }
    };
    
    double det(const Matrix& matrix){
        if(matrix.m_rows!=matrix.m_columns){
            throw std::invalid_argument("Cannot calculate determinant: matrix dimensions are not equal");
        }else
        if(matrix.m_rows==1){
            return matrix.m_matrix[0][0];
        }else
        if(matrix.m_rows==2){
            return matrix.m_matrix[0][0]*matrix.m_matrix[1][1]-matrix.m_matrix[0][1]*matrix.m_matrix[1][0];
        }else{
            double determinant {0};
            for(int i {}; i<matrix.m_columns; i++){
                std::vector<std::vector<double>> temp (matrix.m_rows-1,std::vector<double>(matrix.m_rows-1));   
                for(int row {1};row<matrix.m_columns; row++){
                    int column {0};
                    for(int col{0}; col< matrix.m_columns; col++){
                        if(col==i){
                            continue;
                        }
                        temp[row-1][column] = matrix.m_matrix[row][col];
                        column++;

                    }
                }
                Matrix subMatrix(temp);
                determinant += (i%2==0 ? 1 : -1)*matrix.m_matrix[0][i]*det(subMatrix);
            }
            return determinant;
        }
        
    }
}
