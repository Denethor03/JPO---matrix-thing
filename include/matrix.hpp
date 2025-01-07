/** 
 * Simple matrix library supporting different variable types with basic
 * operations (+,-,*,/,+=...). Contains 3  types: Matrix, SquareMatrix and IdentityMatrix. 
 * Supports complex numbers.
 * NOTE: library is not split into .h and .cpp files since it's template class.
 */

#pragma once
#include <vector>
#include "complex.hpp"
#include <iostream>


namespace ms{
    template <typename T>
    class Matrix{
        private:
            std::vector<std::vector<T>> m_matrix{}; ///< vector of vectors storing matrix
            int m_rows {0}; ///< dimensions stored here in m_rows and m_columns
            int m_columns {0};
            
            /**
             * updateDimensons() is used in constructors and functions modifying dimensions
             * of matrix. Updates m_rows and m_columns private members.
             */
            void updateDimensions(){
                m_rows = m_matrix.size();
                m_columns = m_matrix[0].size();
            }
        protected:
            const std::vector<std::vector<T>>& getMatrix()const{ ///< this is for use in derived classes to acces m_matrix
                return m_matrix; 
            }
        public:
            
            /**
             * 3 types of constructor allowing to create matirx with specific dimensions and default value (0),
             * with specific dimensions and specific value or to use vector of vectors when creating object. 
             * Matrix dimensions cannot be less than 1. Every column must have equal length.
             */  
            Matrix(const int& r,const int& c) : m_matrix(r,std::vector<T>(c)) {
                if(r <= 0 || c <= 0){ 
                    throw std::invalid_argument("Matrix dimensions cannot be less than 1");
                }
                updateDimensions();
            }
            Matrix(const int& r,const int& c,const T& val): m_matrix(r,std::vector<T>(c,val)){
                if(r <= 0 || c <= 0){ 
                    throw std::invalid_argument("Matrix dimensions cannot be less than 1");
                }
                updateDimensions();
    
            }
            Matrix(const std::vector<std::vector<T>>& matrix) : m_matrix(matrix){
                int t_len = matrix[0].size();
                for(int i{}; i<matrix.size(); i++){
                    if(t_len != matrix[i].size()){
                        throw std::invalid_argument("Matrix is not a rectangle uhh idk");
                    }
                }
                updateDimensions();
            }
            
            T getVal(const int& r,const int& c)const{ ///< getter of specific value in matrix
                return m_matrix[r][c];
            }
            
            void setVal(const int& r,const int& c,const T& val){ ///< setter
                m_matrix[r][c] = val;
            }

            int getRows()const{ ///< getters of matrix dimensions, also used in derived classes
                return m_rows;
            }
            

            int getColumns()const{
                return m_columns;
            }

            void printMatrix()const{ ///< function to print matrix
                for(int i {}; i<m_rows; i++){
                    for(int j {}; j<m_columns; j++){
                        std::cout<<m_matrix[i][j]<<" ";
                    }
                    std::cout<<"\n";
                }
            }
            
            /**
             * addRow, remRow, addColumn, remColumn - functions used to modify matrix dimensions.
             * When adding row, vector size must be equal to number of columns. When adding column,
             * vector size must be equal to number of rows. remRow and remColumn remove last row
             * and last column. updateDimensions() called in every function to update m_rows and m_columns
             */
            void addRow(const std::vector<T>& vec){
                if(vec.size()!=m_columns){
                    throw std::invalid_argument("Cannot add row: wrong size");
                }
                else{
                    m_matrix.push_back(vec);
                    updateDimensions();
                    
                }
            }
            
            void remRow(){
                if(m_rows==1){
                    throw std::invalid_argument("Cannot remove more rows");
                }else{
                    m_matrix.pop_back();
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
            
            void remColumn(){
                if(m_columns == 1){
                    throw std::invalid_argument("Cannot remove more columns");
                }else{
                    for(int i{}; i<m_rows; i++){
                        m_matrix[i].pop_back();
                    }
                }
                updateDimensions();
            }
            
            /**
             * det() returns determinant of matrix. Can be used only on matrices with equal dimensions.
             * Uses rather inefficint algorithm (uses recursion) with very high time complexity. Do not
             * use on larger matrices unless you have a lot of time. 
             */
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

            Matrix& transpose(void){ ///< simple transpose function. Does not return a copy!
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
            
            /**
             * Most basic operators functionality implemented below: addition, subraction,
             * multipication, division (as well as compund assigment versions),
             *  comparison (== and !=), [] operator and << operator. Division only works when 
             * dividing matrix by a number. Multiplication works with both matrices and numbers.
             */
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
                if(other == 0){
                    throw std::invalid_argument("Cannot divide by 0");
                }
                Matrix temp_matrix(m_rows,m_columns);
                for(int i {}; i<m_rows; i++){
                        for(int j {}; j<m_columns; j++){
                            temp_matrix[i][j] = m_matrix[i][j]/other;
                        } 
                    }
                return temp_matrix;
            }

            Matrix operator/=(const T& other){
                if(other == 0){
                    throw std::invalid_argument("Cannot divide by 0");
                }
                for(int i {}; i<m_rows; i++){
                        for(int j {}; j<m_columns; j++){
                            m_matrix[i][j]/=other;
                        } 
                    }
                return *this;
            }

            Matrix& operator=(const Matrix& other){
                    m_matrix = other.m_matrix;
                    updateDimensions();
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
            const std::vector<T>& operator[](const int& index)const{  ///< makes using [] operator on "other" possible
                if(index <0 || index >= m_rows){
                    throw std::invalid_argument("Index out of bounds");
                }
                return m_matrix[index];
            }
            template <typename U>
            friend Matrix<U> operator*(const U& scalar, const Matrix<U>& matrix);
    };
    /**
     * Matrix<T> operator*() function below allows to do "number times matrix" (in that order).
     * Without that, it would only be possible to do "matrix times number".
     */
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
    /**
     * Function below used to display row of matrix in case of using [] on object.
     */
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec){
        for(int i {}; i<vec.size(); i++){
                    
                os<<vec[i]<<" ";
            }
            os<<std::endl;
                
        return os;
    }
    /**
     * SquareMatrix has all the functionality of Matrix, but must have equal dimensions.
     * All functions modifying dimensions are private. In case of multiplication (*=), works only
     * when result is square matrix - number of columns in both matrices is the same
     */
    template <typename T>
    class SquareMatrix : public Matrix<T>{
        private:
            using Matrix<T>::addColumn;
            using Matrix<T>::addRow;
            using Matrix<T>::remColumn;
            using Matrix<T>::remRow;
        public:
            SquareMatrix(const int& size) : Matrix<T>(size,size){}
            SquareMatrix(const int& size,const int& value) : Matrix<T>(size,size,value){}
            SquareMatrix(const std::vector<std::vector<T>>& matrix): Matrix<T>(matrix){
                if(matrix.size()!=matrix[0].size()){
                    throw std::invalid_argument("Matrix dimensions don't match");
                }
            }
            SquareMatrix& operator*=(const Matrix<T>& other){ ///< *= overriden, added check if result is still square matrix
                SquareMatrix result(this->getRows());
                if(this->getRows()!=other.getRows()){
                    throw std::invalid_argument("Cannot multiply matrices: number of columns must be equal to number of rows.");
                }else if(other.getColumns() != this->getColumns()){
                    throw std::invalid_argument("Result must be square matrix");
                }else{           
                    for(int i{}; i<this->getRows();i++){
                        for(int j{};j<this->getColumns();j++){
                            for(int k{};k<this->getColumns();k++){
                                result[i][j] += this->getMatrix()[i][k]*other[k][j];
                            }
                        }
                   }
                   *this = result;
                   return *this; 
                }
            }
    };
    /**
     * IdentityMatrix once created cannot be changed. All operations modifying size
     * or values are private
     */
    template <typename T>
    class IdentityMatrix : public SquareMatrix<T>{
        private:
            using Matrix<T>::setVal;
            using Matrix<T>::transpose;
            using Matrix<T>::operator*=;
            using Matrix<T>::operator*;
            using Matrix<T>::operator+;
            using Matrix<T>::operator+=;
            using Matrix<T>::operator-;
            using Matrix<T>::operator-=;
            using Matrix<T>::operator/;
            using Matrix<T>::operator/=;
        public:
            IdentityMatrix(const int& size) : SquareMatrix<T>(size){ ///< setting "1" on matrix diagonal
                for(int i{}; i<size; i++){
                    setVal(i,i,1);
                }
            }
            /**
             * Operator [] overriden and now returns constant reference,
             * so that value cannot be changed, only read
             */
            const std::vector<T>& operator[](const int& index)const{
                if(index <0 || index >= this->getRows()){  ///< "->" used bcs something something templates
                    throw std::invalid_argument("Index out of bounds");
                }
                return this->getMatrix()[index];
            }
            
    };
 
}

