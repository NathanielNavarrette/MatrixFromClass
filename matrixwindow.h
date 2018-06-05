#ifndef MATRIXWINDOW_H
#define MATRIXWINDOW_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QDebug>
#include <QTime>
#include <vector>

#include "matrix.h"
#include "matrixview.h"

class matrixWindow : public QWidget
{
    Q_OBJECT
public:
    explicit matrixWindow(QWidget *parent = nullptr);

private:
    void addMatrixDialog();
    void createMatrixAuto();

    //initialize the rows and cols to 1 (smallest actual matrix that can exist)
    int rows = 1;
    int collums = 1;

signals:
    void matrixWindowSignal();
    void sendMatrix(Matrix add_this);
    void addedMatrixSignal(Matrix viewThis);
    void resultingMatrixSignal(Matrix lhs, Matrix rhs, Matrix result, QString operation);

public slots:
    void addingMatrix(bool clicked);
    void addMatrixAccept();
    void doOpers(std::vector<Matrix> recieved_list);
    void autoRun(bool clicked);

};

#endif // MATRIXWINDOW_H
