#include "maths.h"
#include <cmath>
using namespace MATHS ;


template <typename T>
Matrix<T>::Matrix(int rows, int cols){
    for (int i = 0 ; i< rows; i++){
        for (int j = 0; j < cols ; j++){
            data[i][j] = 0 ; 
        }
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other) {
    rows = other.rows ;
    cols = other.cols ;
    data.resize(rows) ;
    for (int i = 0 ; i < rows ; i++){
        data[i].resize(cols) ;
        for (int j = 0 ; j < cols ; j++){
            data[i][j] = other.data[i][j] ;
        }
    }
}
template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) { 
    if (this != &other) { 
        rows = other.rows ; 
        cols = other.cols ; 
        data.resize(rows) ; 
        for (int i = 0 ; i < rows ; i++){
            data[i].resize(cols) ; 
            for (int j = 0 ; j < cols ; j++){
                data[i][j] = other.data[i][j] ; 
            } 
        } 
    } 
    return *this ;
}
template <typename T>
Matrix<T>::Matrix(const N3& other) {
    rows = 1 ;
    cols = 1 ;
    data.resize(rows) ;
    data[0].resize(cols) ;
    data[0][0].x = other.x ;
    data[0][0].y = other.y ;
    data[0][0].z = other.z ;
}

template <typename T>
Matrix<T> Matrix<T>::operator+  (T value) const {
    Matrix<T> result(rows, cols) ;
    for (int i = 0 ; i < rows ; i++){
        for (int j = 0 ; j < cols ; j++){
            result.data[i][j] = data[i][j] + value ;
        }
    }
    return result ;
}
template <typename T>
Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other) {
    if (rows == other.rows && cols == other.cols){
        for (int i = 0 ; i < rows ; i++){
            for (int j = 0 ; j < cols ; j++){
                data[i][j] += other.data[i][j] ;
            }
        }
    }
    return *this ;
}
template <typename T>
Matrix<T> Matrix<T>::operator-  (const Matrix<T>& other) const {
    if (rows == other.rows && cols == other.cols){
        Matrix<T> result(rows, cols) ;
        for (int i = 0 ; i < rows ; i++){
            for (int j = 0 ; j < cols ; j++){
                result.data[i][j] = data[i][j] - other.data[i][j] ;
            }
        }
        return result ;
    }
    return *this ;
}
template <typename T>
Matrix<T> Matrix<T>::operator-  (T value) const {
    Matrix<T> result(rows, cols) ;
    for (int i = 0 ; i < rows ; i++){
        for (int j = 0 ; j < cols ; j++){
            result.data[i][j] = data[i][j] - value ;
        }
    }
    return result ;
}
template <typename T>
Matrix<T>& Matrix<T>::operator-=(const Matrix<T>& other) {
    if (rows == other.rows && cols == other.cols){
        for (int i = 0 ; i < rows ; i++){
            for (int j = 0 ; j < cols ; j++){
                data[i][j] -= other.data[i][j] ;
            }
        }
    }
    return *this ;
}
template <typename T>
Matrix<T> Matrix<T>::operator*  (const Matrix<T>& other) const {
    if (cols != other.rows){
        throw std::invalid_argument("Incompatible matrix dimensions") ;
    }

    Matrix<T> result(rows, other.cols) ;

    for (int i = 0; i < rows; ++i) {
        for (int k = 0; k < cols; ++k) {
            T sum(0);
            for(int j = 0; j < other.cols; ++j) {
                sum += data[i][k] * other.data[k][j];
            }
            result.data[i][k] = sum;
        }
    }

    return result;
}
template <typename T>
Matrix<T> Matrix<T>::operator* (T lambda) {
   Matrix<T> result(rows, cols);
   for(int i=0; i<rows; ++i)
      for(int j=0; j<cols; ++j)
         result.data[i][j]=data[i][j]*lambda;
   return result;
}

template <typename T> 
Matrix<int> Matrix<T>::operator* (const N3& vec) const { 
    if (cols != 3){ 
        throw std::invalid_argument("Incompatible matrix dimensions") ; 
    } 
    MATHS::N3 res ;
    for (int i = 0; i < rows; ++i) {

        int sum_x(0); 
        int sum_y(0); 
        int sum_z(0); 

        for(int j = 0; j < cols; ++j) { 
           sum_x += data[i][j] * vec.x; 
           sum_y += data[i][j] * vec.y; 
           sum_z += data[i][j] * vec.z; 
        }

        res.x = sum_x ; 
        res.y = sum_y ; 
        res.z = sum_z ; 
    }
    return res;
}

Matrix<float> rotation_2(float theta) {
    Matrix<float> res (2,2);
    res.data[0][0] = std::cos(theta) ;
    res.data[1][1] = std::cos(theta) ;
    res.data[0][1] = - std::sin(theta) ;
    res.data[1][0] = std::cos(theta) ;
    return res ;
}


void Cube::rotate(Matrix<int>& rotation_matrix) { 
        for (auto& vertex : vertices) { 
            Matrix<int> vertex_matrix(3, 1); 
            vertex_matrix.data[0][0] = vertex.x; 
            vertex_matrix.data[1][0] = vertex.y; 
            vertex_matrix.data[2][0] = vertex.z; 
            Matrix<int> rotated_vertex = rotation_matrix * vertex_matrix; 
            vertex.x = rotated_vertex.data[0][0]; 
            vertex.y = rotated_vertex.data[1][0]; 
            vertex.z = rotated_vertex.data[2][0]; 
        } 
        return;
        }