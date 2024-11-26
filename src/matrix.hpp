#pragma once
#include <vector>
#include <initializer_list>
#include "../lib/complex.hpp"
#include <iostream>
namespace ms{
    class Matrix{
        private:
            std::vector<std::vector<double>> m_matrix;
            int m_rows = m_matrix.size();
            int m_columns = m_matrix[0].size();
            void updateDimensions(){
                m_rows = m_matrix.size();
                m_columns = m_matrix[0].size();
            }
        public:
            Matrix(int r, int c) : m_matrix(r,std::vector<double>(c)){}
            Matrix(int r, int c, double val) : m_matrix(r,std::vector<double>(c,val)){}
            Matrix(std::initializer_list<std::vector<double>> matrix) : m_matrix(matrix){}
            Matrix(std::vector<std::vector<double>> matrix) : m_matrix(matrix){}
            
            double getVal(int r, int c)const{
                return m_matrix[r][c];
            }
            void setVal(int r, int c, double val){
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
                   std::cout<<"Cannot add matrices: dimensions don't match\n";
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
                   std::cout<<"Cannot add matrices: dimensions don't match\n";
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
                   std::cout<<"Cannot add matrices: dimensions don't match\n";
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
                   std::cout<<"Cannot add matrices: dimensions don't match\n";
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

            friend Matrix operator*(const double& scalar, const Matrix& matrix);

            

            void addColumn(const std::vector<double>& vec){
                if(vec.size()!=m_rows){
                    std::cout<<"Cannod add column: wrong size\n";
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
                    std::cout<<"Cannot multiply matrices: number of columns must be equal to number of rows\n";
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
            IdentityMatrix(int size) : Matrix(size,size){
                for(int i{}; i<size; i++){
                    setVal(i,i,1);
                }
            }
    };
}
