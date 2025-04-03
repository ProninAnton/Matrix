#ifndef MATRIX_H
#define MATRIX_H

#include <QObject>
#include <memory>

class Matrix : public QObject
{
    Q_OBJECT
public:
    Matrix(int row, int col, std::shared_ptr<int*[]>matrix);
    void operator+(const Matrix &matrixB);
    void operator*(const Matrix &matrixB);

signals:
    void printMatrix(std::shared_ptr<int*[]> matrix);

private:
    int _row;
    int _column;
    std::shared_ptr<int*[]> _matrix;
};

#endif // MATRIX_H
