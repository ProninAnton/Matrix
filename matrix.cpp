#include "matrix.h"
#include "iostream"

Matrix::Matrix(int row, int col, std::shared_ptr<int *[]> matrix) : _row(row), _column(col), _matrix(matrix) {

}

void Matrix::operator+(const Matrix &matrixB)
{
    if (_row != matrixB._row || _column != matrixB._column) {
        throw std::exception();
    }
    std::shared_ptr<int*[]> newMtrx {new int*[_row]};
    for (int i = 0; i < _row; ++i) {
        newMtrx[i] = new int[_column];
    }
    for (int i = 0; i < _row; ++i) {
        for (int j = 0; j < _column; ++j) {
            newMtrx[i][j] = _matrix[i][j] + matrixB._matrix[i][j];
        }
    }
    emit printMatrix(newMtrx);
    return;
}

void Matrix::operator*(const Matrix &matrixB)
{
    if (_column != matrixB._row) {
        throw std::exception();
    }
    std::shared_ptr<int*[]> newMtrx {new int*[_row]};
    for (int i = 0; i < matrixB._column; ++i) {
        newMtrx[i] = new int[_column];
    }

    for (int i = 0; i < _row; ++i) {
        for (int j = 0; j < matrixB._column; ++j) {
            newMtrx[i][j] = 0;
            for (int k = 0; k < matrixB._row; ++k) {
               newMtrx[i][j] += _matrix[i][k] + matrixB._matrix[k][j];
            }
        }
    }
    Matrix matrixRes(_row, matrixB._column, newMtrx);
    emit printMatrix(newMtrx);
    return;
}
