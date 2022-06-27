#ifndef MATRIX_H
#define MATRIX_H
#include <QPoint>
#include <iostream>
#include <QDataStream>

class Matrix
{
private:
    long double **m_matrix;
    int n;
    int m;
public:
    Matrix();
    Matrix(const QPointF &vector);
    Matrix(long double **matrix, int n, int m);
    Matrix(long double a11, long double a12, long double a13,
           long double a21, long double a22, long double a23,
           long double a31, long double a32, long double a33);
    Matrix(const Matrix &source);


    ~Matrix();

    int getN() const;
    int getM() const;
    QPointF getVectorPoint() const;

    long double *operator[](int i) const;
    Matrix &operator=(const Matrix &source);
    friend Matrix operator*(const Matrix &matrix1, const Matrix &matrix2);

    friend std::ostream &operator <<(std::ostream &out, const Matrix &matrix);
    friend QDataStream &operator <<(QDataStream &out, const Matrix &matrix);

};

#endif // MATRIX_H
