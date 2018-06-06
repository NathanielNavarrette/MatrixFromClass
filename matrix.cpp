#include "matrix.h"

Matrix::Matrix()
{

}

Matrix::Matrix(m_Matrix complete_set)
{
    m_data = complete_set;
    m_rows = complete_set.size();
    m_cols = complete_set.at(0).size();
}

Matrix::Matrix(std::vector<int> in_values, int rows, int cols)
{
    m_rows = rows;
    m_cols = cols;
    std::vector<int> these_rows;
    std::vector<int> empty_vector;
    int thisSize = (rows*cols);

    for(int i=0;i<thisSize;i)
    {
        if(i != thisSize) //this had (thiSize -1) which fixxed some stuff and broke others
        {
            qDebug() << "Matrix Created successfully";
            int secondLoopMax = i+cols;
            for(int j=i; j < secondLoopMax; j++)
            {
                these_rows.push_back(in_values.at(j));
                i=0;
                i+=(j+1);
            }
            m_data.push_back(these_rows);
            these_rows = empty_vector;
        }else{
            i++;
        }
    }
}

m_Matrix Matrix::get_matrix() const
{
    return m_data;
}

int Matrix::get_rows() const
{
    return m_rows;
}

int Matrix::get_cols() const
{
    return m_cols;
}

int Matrix::get_value_at(int this_row, int this_col)
{
    //qDebug() << "outside size: " << m_data.size() << " Inside side: " << m_data.at(this_row).size();
    return m_data.at(this_row).at(this_col);
}

void Matrix::m_debug_this(QString s_name)
{
    qDebug() << s_name;
    qDebug() << "\nRows: " << m_rows;
    qDebug() << "Cols: " << m_cols;

    qDebug() << "\nValues in Matrix:";
    qDebug() << "m_data size: " << m_data.size();

    for(int i = 0; i < m_data.size(); i++)
    {
        qDebug() << "Size at " << i << " : " << m_data.at(i).size();
        for(int j = 0; j < m_data.at(i).size(); j++)
        {
            qDebug() << m_data.at(i).at(j);
        }
    }
}

bool check_if_possible(const Matrix &lhs, const Matrix &rhs, int operation_case)
{
    /*Function that takes in two matricies and determines if compulation is possible between them
     * operation cases are the different operations that are occuring on the matricies
     */
    switch(operation_case){
    case 1:
        //addition case:
        if((lhs.get_cols() != rhs.get_cols()) || (lhs.get_rows() != rhs.get_rows()))
            return false;
        else
            return true;
        break;
    case 2:

        //subtraction case:
        if((lhs.get_cols() != rhs.get_cols()) || (lhs.get_rows() != rhs.get_rows()))
            return false;
        else
            return true;
        break;

    case 3:
        //multiplication
        if(lhs.get_cols() != rhs.get_rows())
            return false;
        else
            return true;
        break;
    }
    //if all else false:
    return false;
}

Matrix operator+(const Matrix &lhs, const Matrix &rhs)
{
    m_Matrix result;
    Matrix empty_result;

    if(check_if_possible(lhs, rhs, 1))
    {
        //only create and use this memory if its possible
        std::vector<int> values_tmp;
        std::vector<int> empty_vec;
        m_Matrix m_lhs = lhs.get_matrix();
        m_Matrix m_rhs = rhs.get_matrix();

        for(int i = 0; i < m_lhs.size(); i++)
        {
            for(int j = 0; j < m_lhs.at(i).size(); j++)
            {
                values_tmp.push_back( (m_lhs.at(i).at(j)) + (m_rhs.at(i).at(j)) );
            }
            result.push_back(values_tmp);
            values_tmp = empty_vec;
        }
        Matrix return_this(result);
        return return_this;
    }else{
        return empty_result;
    }
}

Matrix operator-(const Matrix &lhs, const Matrix &rhs)
{
    m_Matrix result;
    Matrix empty_result;

    if(check_if_possible(lhs, rhs, 2))
    {
        //only create and use this memory if its possible
        std::vector<int> values_tmp;
        std::vector<int> empty_vec;
        m_Matrix m_lhs = lhs.get_matrix();
        m_Matrix m_rhs = rhs.get_matrix();

        for(int i = 0; i < m_lhs.size(); i++)
        {
            for(int j = 0; j < m_lhs.at(i).size(); j++)
            {
                values_tmp.push_back( (m_lhs.at(i).at(j)) - (m_rhs.at(i).at(j)) );
            }
            result.push_back(values_tmp);
            values_tmp = empty_vec;
        }
        Matrix return_this(result);
        return return_this;
    }else{
        return empty_result;
    }
}

Matrix operator*(const Matrix &lhs, const Matrix &rhs)
{
    /*Operator overload for Matrix class
     * Have to check the different options before being able to do
     * any sort of computation on the matricies
     */

    Matrix empty_result; //empty matrix to send if everything fails.

    if(check_if_possible(lhs, rhs, 3))
    {
        std::vector<int> result_tmp;
        std::vector<int> add_row_tmp;
        std::vector<int> row_tmp;
        std::vector<int> empty_vec;
        m_Matrix m_value;
        m_Matrix m_lhs = lhs.get_matrix();
        m_Matrix m_rhs = rhs.get_matrix();

        for(int i=0; i < lhs.get_rows(); i++)
        {
            for(int j=0; j < rhs.get_cols(); j++)
            {
                for(int k = 0; k < lhs.get_cols(); k++)
                {
                    result_tmp.push_back( (m_lhs.at(i).at(k) * m_rhs.at(k).at(j) ) );
                }
            }
        }

        //take the values that are in result_tmp and rearrange them into the proper matrix
        for(int i=0;i<result_tmp.size();i)
        {
            if(i != result_tmp.size()-1)
            {
                int add_tmp = 0;
                int secondLoopMax = i+lhs.get_cols();
                for(int j=i; j < secondLoopMax; j++)
                {
                    add_tmp += result_tmp.at(j);
                    i=(j+1);
                }
                add_row_tmp.push_back(add_tmp);
            }
        }

        for(int i=0;i<add_row_tmp.size();i)
        {
            if(i != (lhs.get_rows()*rhs.get_cols()) -1)
            {
                int secondLoopMax = i+rhs.get_cols();
                for(int j=i; j < secondLoopMax; j++)
                {
                    row_tmp.push_back(add_row_tmp.at(j));
                    i=0;
                    i+=(j+1);
                }
                m_value.push_back(row_tmp);
                row_tmp = empty_vec;
            }else{
                i++;
            }
        }
        //end the rearranging
        Matrix return_this(m_value);
        return return_this;

    }else if(rhs.get_cols() == 1 && rhs.get_rows() == 1 ){
        //rhs is the scalar
        m_Matrix result_tmp = lhs.get_matrix();
        m_Matrix m_rhs = rhs.get_matrix();

        for(int i=0; i < lhs.get_rows(); i++)
        {
            for(int j=0; j < lhs.get_cols(); j++)
            {
                result_tmp.at(i).at(j) *= m_rhs.at(0).at(0);
            }
        }
        Matrix return_this(result_tmp);
        return return_this;

    }else if(lhs.get_cols() == 1 && lhs.get_rows() == 1){
        //lhs is the scalar
        m_Matrix result_tmp = rhs.get_matrix();
        m_Matrix m_lhs = lhs.get_matrix();

        for(int i=0; i < rhs.get_rows(); i++)
        {
            for(int j=0; j < rhs.get_cols(); j++)
            {
                result_tmp.at(i).at(j) *= m_lhs.at(0).at(0);
            }
        }
        Matrix return_this(result_tmp);
        return return_this;
    }else{
        //if all else fails, return empty result
        return empty_result;
    }
    return empty_result;
}
