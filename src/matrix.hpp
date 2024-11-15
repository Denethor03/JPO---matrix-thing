#pragma once
#include <vector>
#include "../lib/complex.hpp"
namespace ms{
    class Matrix{
        private:
            int m_rows {}, m_columns {};
            std::vector<std::vector<double>> m_matrix;
        public:
            Matrix(int r, int c) : m_rows(r), m_columns(c){}
            Matrix(std::vector<std::vector<double>> matrix) : m_matrix(matrix){}

    };
}