#pragma once
#include <ostream>
namespace ms{
    
        template <typename T>
        class ComplexNumber{
            private:
                T m_real;
                T m_imag;
            public:
                
                ComplexNumber(T r = T(), T i = T()) : m_real(r), m_imag(i) {}
                
                ComplexNumber operator+(const ComplexNumber& other)const{
                    return ComplexNumber(m_real + other.m_real, m_imag + other.m_imag);
                }
                ComplexNumber& operator+=(const ComplexNumber& other){
                    m_real += other.m_real;
                    m_imag += other.m_imag;
                    return *this;
                }
               
                ComplexNumber& operator-=(const ComplexNumber& other){
                    m_real -= other.m_real;
                    m_imag -= other.m_imag;
                    return *this;
                }
                ComplexNumber operator- (const ComplexNumber& other)const{
                    return ComplexNumber(m_real - other.m_real, m_imag - other.m_imag);
                }
                bool operator==(const ComplexNumber& other)const{
                    return m_real == other.m_real && m_imag == other.m_imag;
                }
                bool operator!=(const ComplexNumber& other)const{
                    return !(other==*this);
                }
                ComplexNumber operator*(const ComplexNumber& other)const{
                    return ComplexNumber(m_real*other.m_real-m_imag*other.m_imag, m_real*other.m_imag+m_imag*other.m_real);
                }
                ComplexNumber& operator*=(const ComplexNumber& other){
                    T real = m_real*other.m_real-m_imag*other.m_imag;
                    T imag = m_real*other.m_imag+m_imag*other.m_real;
                    m_real = real;
                    m_imag = imag;
                    return *this;
                }
                ComplexNumber operator/(const ComplexNumber& other)const{
                    T real = (m_real*other.m_real+m_imag*other.m_imag)/(other.m_real*other.m_real+other.m_imag*other.m_imag);
                    T imag = (m_imag*other.m_real-m_real*other.m_imag)/(other.m_real*other.m_real+other.m_imag*other.m_imag);
                    return ComplexNumber(real,imag);
                }
                ComplexNumber& operator/=(const ComplexNumber& other){
                    T real = (m_real*other.m_real+m_imag*other.m_imag)/(other.m_real*other.m_real+other.m_imag*other.m_imag);
                    T imag = (m_imag*other.m_real-m_real*other.m_imag)/(other.m_real*other.m_real+other.m_imag*other.m_imag);
                    m_real = real;
                    m_imag = imag;
                    return *this;
                }
                
                template <typename U>
                friend ComplexNumber<U> operator*(const U&, const ComplexNumber<U>& complexNumber);

                friend std::ostream& operator<<(std::ostream& os, const ComplexNumber& c){
                    os << c.m_real << (c.m_imag >= 0 ? "+" : "-")<<std::abs(c.m_imag)<<"i";
                    return os;
                }
                ComplexNumber operator+(const T& other)const{
                    return ComplexNumber(m_real+other,m_imag);
                }
                ComplexNumber& operator+=(const T& other){
                    m_real += other;
                    return *this;
                }
                ComplexNumber operator-(const T& other)const{
                    return ComplexNumber(m_real-other,m_imag);
                }
                ComplexNumber& operator-=(const T& other){
                    m_real -= other;
                    return *this;
                }
                ComplexNumber& operator=(const ComplexNumber& other){
                    m_real = other.m_real;
                    m_imag = other.m_imag;
                    return *this;
                }

                T getReal()const{
                    return m_real;
                }
                T getImag()const{
                    return m_imag;
                }
                void setReal(T r){
                    m_real =  r;
                }
                void setImag(T i){
                    m_imag = i;
                }

        };

        template <typename T>
        ComplexNumber<T> operator*(const T& scalar, const ComplexNumber<T>& complexNumber){
            return ComplexNumber<T>(complexNumber.getReal()*scalar,complexNumber.getImag()*scalar);
        }
}
