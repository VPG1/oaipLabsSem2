#include "matrix.h"

int Matrix::getN() const
{
    return n;
}

int Matrix::getM() const
{
    return m;
}

QPointF Matrix::getVectorPoint() const
{
    assert(n == 3 && m == 1);
    return QPointF(m_matrix[0][0], m_matrix[1][0]);
}

long double *Matrix::operator[](int i) const //
{
    return m_matrix[i];
}

Matrix &Matrix::operator=(const Matrix &source)
{
    if(this == &source){
        return *this;
    }


    for(int i = 0; i < n; ++i){
        delete[] m_matrix[i];
    }
    delete[] m_matrix;


    n = source.n;
    m = source.m;

    if(source.m_matrix){
        m_matrix = new long double*[n];
        for(int i = 0; i < n; ++i){
            m_matrix[i] = new long double[m];
            for(int j = 0; j < m; ++j){
                m_matrix[i][j] = source.m_matrix[i][j];
            }
        }
    }
    else{
        m_matrix = nullptr;
    }

    return *this;
}

Matrix::Matrix()
{
    m_matrix = nullptr;
    n = 0;
    m = 0;

}

Matrix::Matrix(const QPointF &vector)
    : n(3), m(1)
{
    m_matrix = new long double*[n];
    for(int i = 0; i < n; ++i){
        m_matrix[i] = new long double[m];
    }
    m_matrix[0][0] = vector.x();
    m_matrix[1][0] = vector.y();
    m_matrix[2][0] = 1;
}

Matrix::Matrix(long double **matrix, int n, int m)
    : n(n), m(m)
{
    m_matrix = matrix;
}

Matrix::Matrix(long double a11, long double a12, long double a13,
               long double a21, long double a22, long double a23,
               long double a31, long double a32, long double a33)
    : n(3), m(3)
{
    m_matrix = new long double*[n];
    for(int i = 0; i < n; ++i){
        m_matrix[i] = new long double[m];
    }
    m_matrix[0][0] = a11, m_matrix[0][1] = a12, m_matrix[0][2] = a13;
    m_matrix[1][0] = a21, m_matrix[1][1] = a22, m_matrix[1][2] = a23;
    m_matrix[2][0] = a31, m_matrix[2][1] = a32, m_matrix[2][2] = a33;
}

Matrix::Matrix(const Matrix &source)
{
    n = source.n;
    m = source.m;

    if(source.m_matrix){
        m_matrix = new long double*[n];
        for(int i = 0; i < n; ++i){
            m_matrix[i] = new long double[m];
            for(int j = 0; j < m; ++j){
                m_matrix[i][j] = source.m_matrix[i][j];
            }
        }
    }
    else{
        m_matrix = nullptr;
    }
}

Matrix::~Matrix()
{
    for(int i = 0; i < n; ++i){
        delete[] m_matrix[i];
    }
    delete[] m_matrix;
}

Matrix operator*(const Matrix &matrix1, const Matrix &matrix2){
    assert(matrix1.getM() == matrix2.getN());
    long double **resMatrix = new long double*[matrix1.getN()];
    for(int i = 0; i < matrix1.getN(); ++i){
        resMatrix[i] = new long double[matrix2.getM()];
        for(int j = 0; j < matrix2.getM(); ++j){
            resMatrix[i][j] = 0;
            for(int k = 0; k < matrix1.getM(); ++k){
                resMatrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    return Matrix(resMatrix, matrix1.getN(), matrix2.getM());
}

std::ostream &operator <<(std::ostream &out, const Matrix &matrix){
    for(int i = 0; i < matrix.getN(); ++i){
        for(int j = 0; j < matrix.getM(); ++j){
            out << matrix[i][j] << " ";
        }
        out << '\n';
    }
    return out;
}

QDataStream &operator <<(QDataStream &out, const Matrix &matrix){
    for(int i = 0; i < matrix.getN(); ++i){
        for(int j = 0; j < matrix.getM(); ++j){
            out << (double)matrix[i][j] << " ";
        }
        out << '\n';
    }
    return out;
}

