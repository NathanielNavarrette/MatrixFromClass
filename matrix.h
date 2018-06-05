#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

#include <QDebug>

typedef std::vector<std::vector<int>> m_Matrix;

class Matrix
{
public:
    Matrix();
    Matrix(m_Matrix complete_set);
    Matrix(std::vector<int> in_values, int rows, int cols);
    void m_debug_this(QString s_name);
    m_Matrix get_matrix() const;
    int get_rows() const;
    int get_cols() const;
    int get_value_at(int this_row, int this_col);


private:
    m_Matrix m_data;
    int m_rows = 0; //if both rows and cols are still 0, theres nothing
    int m_cols = 0; //in the Matrix and the requested operation cannot be done

};

bool check_if_possible(const Matrix &lhs, const Matrix &rhs, int operation_case);

Matrix operator+(const Matrix &lhs, const Matrix &rhs);
Matrix operator-(const Matrix &lhs, const Matrix &rhs);
Matrix operator*(const Matrix &lhs, const Matrix &rhs);

#endif // MATRIX_H
