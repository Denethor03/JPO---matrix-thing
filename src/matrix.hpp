#pragma once
#include <vector>
#include "../lib/complex.hpp"
#include <iostream>


namespace ms{
    template <typename T>
    class Matrix{
        private:
            std::vector<std::vector<T>> m_matrix{};
            int m_rows {0};
            int m_columns {0};
            
            void updateDimensions(){
                m_rows = m_matrix.size();
                m_columns = m_matrix[0].size();
            }
        protected:
            const std::vector<std::vector<T>>& getMatrix()const{
                return m_matrix; 
            }
        public:
            Matrix(const int& r,const int& c) : m_matrix(r,std::vector<T>(c)) {
                if(r <= 0 || c <= 0){ 
                    throw std::invalid_argument("Matrix dimensions cannot be less than 0");
                }
                updateDimensions();
            }
            Matrix(const int& r,const int& c,const T& val): m_matrix(r,std::vector<T>(c,val)){
                if(r <= 0 || c <= 0){ 
                    throw std::invalid_argument("Matrix dimensions cannot be less than 0");
                }
                updateDimensions();
    
            }
            Matrix(const std::vector<std::vector<T>>& matrix) : m_matrix(matrix){
               // std::cout<<"Test";
                int t_len = matrix[0].size();
                for(int i{}; i<matrix.size(); i++){
                    if(t_len != matrix[i].size()){
                        throw std::invalid_argument("Matrix is not a rectangle uhh idk");
                    }
                }
                updateDimensions();
            }
            
            T getVal(const int& r,const int& c)const{
                return m_matrix[r][c];
            }
            
            void setVal(const int& r,const int& c,const T& val){
                m_matrix[r][c] = val;
            }

            int getRows()const{
                return m_rows;
            }
            

            int getColumns()const{
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

            void addRow(const std::vector<T>& vec){
                if(vec.size()!=m_columns){
                    std::cout<<"Cannot add row: wrong size\n";
                }
                else{
                    m_matrix.push_back(vec);
                    updateDimensions();
                    
                }
            }

            void addColumn(const std::vector<T>& vec){
                if(vec.size()!=m_rows){
                    throw std::invalid_argument("Cannot add column: wrong size");
                }else{
                    for(int i{}; i<m_rows; i++){
                        m_matrix[i].push_back(vec[i]);
                    }
                }
                updateDimensions();
            }

            T det(){
                if(m_rows!=m_columns){
                    throw std::invalid_argument("Cannot calculate determinant: matrix dimensions are not equal");
                }else
                if(m_rows==1){
                    return m_matrix[0][0];
                }else
                if(m_rows==2){
                    return m_matrix[0][0]*m_matrix[1][1]-m_matrix[0][1]*m_matrix[1][0];
                }else{
                    T determinant {0};
                    for(int i {}; i<m_columns; i++){
                        Matrix temp(m_rows-1,m_rows-1);   
                        for(int row {1};row<m_columns; row++){
                            int column {0};
                            for(int col{0}; col< m_columns; col++){
                                if(col==i){
                                    continue;
                                }
                                temp[row-1][column] = m_matrix[row][col];
                                column++;

                            }
                        }
                        
                        determinant += (i%2==0 ? T(1) : T(-1))*m_matrix[0][i]*temp.det();
                    }
                    return determinant;
                }
            }

            Matrix& transpose(void){
                Matrix temp(m_columns,m_rows);
                for(int i{}; i<m_rows; i++){
                    for(int j{}; j<m_columns; j++){
                        temp[j][i] = m_matrix[i][j];
                    }
                }
                *this = temp;
                updateDimensions();
                return *this;
            }
            Matrix operator+(const Matrix& other)const{
                Matrix temp_matrix(m_rows,m_columns);
                if(m_columns != other.m_columns || m_rows != other.m_rows){
                   throw std::invalid_argument("Cannot add matrices: dimensions don't match");
                }
                else{
                    
                    for(int i {}; i<m_rows; i++){
                        for(int j {}; j<m_columns; j++){
                            temp_matrix[i][j] = m_matrix[i][j] + other[i][j];
                        } 
                    } 
                }
                return temp_matrix;
            }

            Matrix& operator+=(const Matrix& other){
                if(m_columns != other.m_columns || m_rows != other.m_rows){
                   throw std::invalid_argument("Cannot add matrices: dimensions don't match\n");
                }
                else{
                    
                    for(int i {}; i<m_rows; i++){
                        for(int j {}; j<m_columns; j++){
                            m_matrix[i][j] += other[i][j];
                        } 
                    } 
                }
                return *this;
            }

             Matrix operator-(const Matrix& other)const{
                Matrix temp_matrix(m_rows,m_columns);
                if(m_columns != other.m_columns || m_rows != other.m_rows){
                   throw std::invalid_argument("Cannot add matrices: dimensions don't match");
                }
                else{
                    
                    for(int i {}; i<m_rows; i++){
                        for(int j {}; j<m_columns; j++){
                            temp_matrix[i][j] = m_matrix[i][j] - other[i][j];
                        } 
                    } 
                }
                return temp_matrix;
            }

            Matrix& operator-=(const Matrix& other){
                if(m_columns != other.m_columns || m_rows != other.m_rows){
                   throw std::invalid_argument("Cannot add matrices: dimensions don't match\n");
                }
                else{
                    
                    for(int i {}; i<m_rows; i++){
                        for(int j {}; j<m_columns; j++){
                            m_matrix[i][j] -= other[i][j];
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
                        if(m_matrix[i][j] != other[i][j]){ 
                            return false;
                        }       
                    } 
                }
                return true;
            }

            bool operator!=(const Matrix& other)const{
                return !operator==(other);
            }

            Matrix operator*(const T& other)const{
                Matrix temp_matrix(m_rows,m_columns);
                for(int i {}; i<m_rows; i++){
                        for(int j {}; j<m_columns; j++){
                            temp_matrix[i][j] = m_matrix[i][j]*other;
                        } 
                    }
                return temp_matrix;
            }

             Matrix& operator*=(const T& other){
                for(int i {}; i<m_rows; i++){
                        for(int j {}; j<m_columns; j++){
                            m_matrix[i][j]*=other;
                        } 
                    }
                return *this;
            }

            Matrix operator/(const T& other)const{
                Matrix temp_matrix(m_rows,m_columns);
                for(int i {}; i<m_rows; i++){
                        for(int j {}; j<m_columns; j++){
                            temp_matrix[i][j] = m_matrix[i][j]/other;
                        } 
                    }
                return temp_matrix;
            }

            Matrix operator/=(const T& other){
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
                        os<<matrix[i][j]<<" ";
                    }
                    os<<std::endl;
                }
                return os;
            }

            Matrix operator*(const Matrix& other)const{
                Matrix result(m_rows,other.m_columns);
                if(m_columns!=other.m_rows){
                     throw std::invalid_argument("Cannot multiply matrices: number of columns must be equal to number of rows.");
                }else{
                   
                    for(int i{}; i<m_rows;i++){
                        for(int j{};j<m_columns;j++){
                            for(int k{};k<m_columns;k++){
                                result[i][j] += m_matrix[i][k]*other[k][j];
                            }
                        }
                   } 
                }
                return result;
            }
            Matrix& operator*=(const Matrix& other){
                Matrix result(m_rows,other.m_columns);
                if(m_columns!=other.m_rows){
                     throw std::invalid_argument("Cannot multiply matrices: number of columns must be equal to number of rows.");
                }else{           
                    for(int i{}; i<m_rows;i++){
                        for(int j{};j<m_columns;j++){
                            for(int k{};k<m_columns;k++){
                                result[i][j] += m_matrix[i][k]*other[k][j];
                            }
                        }
                   }
                   *this = result;
                   return *this; 
                }
            }

            std::vector<T>& operator[](const int& index){
                if(index <0 || index >= m_rows){
                    throw std::invalid_argument("Index out of bounds");
                }
                return m_matrix[index];
            }
            const std::vector<T>& operator[](const int& index)const{  //makes using [] on other possible
                if(index <0 || index >= m_rows){
                    throw std::invalid_argument("Index out of bounds");
                }
                return m_matrix[index];
            }
            template <typename U>
            friend Matrix<U> operator*(const U& scalar, const Matrix<U>& matrix);
    };
    
    template <typename T>
    Matrix<T> operator*(const T& scalar, const Matrix<T>& matrix){
        Matrix<T> temp_matrix = matrix;
        for(int i {}; i<matrix.m_rows; i++){
            for(int j {}; j<matrix.m_columns; j++){
                temp_matrix[i][j] = matrix[i][j]*scalar;
            } 
        }
        return temp_matrix;
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec){
        for(int i {}; i<vec.size(); i++){
                    
                os<<vec[i]<<" ";
            }
            os<<std::endl;
                
        return os;
    }
    template <typename T>
    class SquareMatrix : public Matrix<T>{
        private:
            using Matrix<T>::addColumn;
            using Matrix<T>::addRow;
        public:
            SquareMatrix(const int& size) : Matrix<T>(size,size){}
            SquareMatrix(const int& size,const int& value) : Matrix<T>(size,size,value){}
            SquareMatrix(const std::vector<std::vector<T>>& matrix): Matrix<T>(matrix){
                if(matrix.size()!=matrix[0].size()){
                    throw std::invalid_argument("Matrix dimensions don't match");
                }
            }
    };
    template <typename T>
    class IdentityMatrix : public SquareMatrix<T>{
        private:
            using Matrix<T>::setVal;
            using Matrix<T>::operator*=;
            using Matrix<T>::operator*;
            using Matrix<T>::operator+;
            using Matrix<T>::operator+=;
            using Matrix<T>::operator-;
            using Matrix<T>::operator-=;
            using Matrix<T>::operator/;
            using Matrix<T>::operator/=;
        public:
            IdentityMatrix(const int& size) : SquareMatrix<T>(size){
                for(int i{}; i<size; i++){
                    setVal(i,i,1);
                }
            }
            const std::vector<T>& operator[](const int& index)const{
                if(index <0 || index >= this->getRows()){  // "->" used bcs something something templates
                    throw std::invalid_argument("Index out of bounds");
                }
                return this->getMatrix()[index];
            }
            
    };

    
}

