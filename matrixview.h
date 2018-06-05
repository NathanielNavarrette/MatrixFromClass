#ifndef MATRIXVIEW_H
#define MATRIXVIEW_H

#include <QWidget>
#include <QLayout>
#include <QLabel>

#include "matrix.h"

class MatrixView : public QWidget
{
    Q_OBJECT
public:
    explicit MatrixView(QWidget *parent = nullptr);
    MatrixView(Matrix &displayThis, QWidget *parent = nullptr);
    MatrixView(Matrix &lhs, Matrix &rhs, Matrix &result, QString operation, QWidget *parent = nullptr);

    QString get_string();
    QWidget *get_label();


private:
    Matrix m_data;
    QString showData;

    QWidget *displayMatrix = new QLabel(this);

    QString get_matrix_string(Matrix &displayThis);

    QWidget *displayWindow = new QWidget(this);
    QHBoxLayout *m_layout = new QHBoxLayout(displayWindow);


signals:

public slots:

};

#endif // MATRIXVIEW_H
