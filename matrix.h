#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <sstream>

//templated variable-dimension matrix implementation
template <class T, std::size_t rows, std::size_t columns> class Matrix{
protected:
    T** matrix = new T*[rows];
public:

    const size_t ncols = columns;
    const size_t nrows = rows;

    Matrix(std::array<T,rows*columns> elements){
        matrix = new T*[rows];
        for(int i = 0; i < rows; i++){
            matrix[i] = new T[columns];
        }
        for(size_t i = 0; i < rows; i++){
            for(size_t j = 0; j < columns; j++){
                matrix[i][j] = elements[i*columns + j];
            }
        }
    }

    friend std::ostream& operator<<(std::ostream &os, const Matrix &matrix) {
        std::ostringstream output;
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                os << matrix[i][j] << " ";
            }
            os << std::endl;
        }
        return os;
    }

    T* operator[](size_t row) const{
        return matrix[row];
    }

    template<unsigned int N>
    friend Matrix<T, rows, N> operator * (Matrix<T, rows, columns> &lhs, Matrix<T, columns, N> &rhs){
        if(lhs.ncols != rhs.nrows){
            std::cout << "error, rows != cols, multiplication impossible" << std::endl;
        }
        std::array<T, rows * N> products = {};
        for(int i = 0; i < lhs.nrows; i++){
            for(int j = 0; j < rhs.ncols; j++){
                for(int k = 0; k < lhs.ncols; k++){
                    products[i*N + j] += lhs[i][k] * rhs[k][j];
                }
            }
        }
        Matrix<T, rows, N> product(products);
        return product;
    }

    const Matrix<T, columns, rows> transpose(){
    	
    }

    const friend Matrix<T, rows, columns> operator +(const Matrix<T, rows, columns> &lhs, const Matrix<T, rows, columns> &rhs){
        std::array<T, rows * columns> result;
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                T val = lhs.matrix[i][j] + rhs.matrix[i][j];
                result[i*columns + j] = val;
            }
        }
        Matrix<T, rows, columns> sum(result);
        return sum;
    }

    Matrix<T, rows, columns> operator+=(const Matrix<T, rows, columns>& rhs){

        *this = *this + rhs;
        return *this;

    }

    const friend Matrix<T, rows, columns> operator -(const Matrix<T, rows, columns> &lhs, const Matrix<T, rows, columns> &rhs){
        std::array<T, rows * columns> result;
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                T val = lhs.matrix[i][j] - rhs.matrix[i][j];
                result[i*columns + j] = val;
            }
        }
        Matrix<T, rows, columns> diff(result);
        return diff;
    }

    Matrix<T, rows, columns> operator-=(const Matrix<T, rows, columns>& rhs){

        *this = *this - rhs;
        return *this;
    }
};





