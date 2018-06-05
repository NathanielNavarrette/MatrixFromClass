#include "matrixview.h"
#include <iomanip>

MatrixView::MatrixView(QWidget *parent) : QWidget(parent)
{

}

MatrixView::MatrixView(Matrix &displayThis, QWidget *parent) : QWidget(parent)
{
    m_data = displayThis;
    QString final_string;

    final_string = get_matrix_string(m_data);
    showData = final_string;
}
MatrixView::MatrixView(Matrix &lhs, Matrix &rhs, Matrix &result, QString operation, QWidget *parent) : QWidget(parent)
{
    qDebug() << "Debug 2";
    Matrix lhs_data = lhs;
    Matrix rhs_data = rhs;
    m_data = result;
    QString final_string;

    QWidget *m1 = new QLabel(QString(get_matrix_string(lhs_data)), displayWindow);
    QWidget *opr = new QLabel(operation, displayWindow);
    QWidget *m2 = new QLabel(QString(get_matrix_string(rhs_data)), displayWindow);
    QWidget *eql = new QLabel(QString("="), displayWindow);
    QWidget *m3 = new QLabel(QString(get_matrix_string(m_data)), displayWindow);

    m_layout->addWidget(m1);
    m_layout->addWidget(opr);
    m_layout->addWidget(m2);
    m_layout->addWidget(eql);
    m_layout->addWidget(m3);
}

QString MatrixView::get_matrix_string(Matrix &displayThis)
{
    QString return_string;
    //m_data = displayThis;

    /*
     * this is the function that doesnt work when you have a nX1 matrix for what ever reason
     * has to do with the get rows or something, it goes one over on the rows i guess
     */

    for(int i=0;i<m_data.get_rows();i++)
    {
        for(int j=0;j<m_data.get_cols();j++)
        {
            qDebug() << "break 1: i:" << i << " j: " << j;
            return_string += QString("%1").arg(QString::number(m_data.get_value_at(i, j)), -5);// + " ";
            qDebug() << "adding value to string";
        }
        qDebug() << "adding space to string";
        return_string += "\n"; //adds a new line for the matrix
    }

    qDebug() << "Return statement";
    return return_string;
}

QString MatrixView::get_string()
{
    if(showData != "")
        return showData;
    else
        return QString("Operation Wasn't able to be done\nOn the two chosen Matricies.");
}

QWidget* MatrixView::get_label()
{
    return displayWindow;
}
