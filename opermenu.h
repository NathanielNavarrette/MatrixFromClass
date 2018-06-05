#ifndef OPERMENU_H
#define OPERMENU_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QRadioButton>
#include <QCheckBox>
#include <QDebug>
#include <vector>

#include "matrixview.h"
#include "matrix.h"

class OperMenu : public QWidget
{
    Q_OBJECT
public:
    explicit OperMenu(QWidget *parent = nullptr);

private:


public slots:
    void operationsMenuSlot(std::vector<Matrix> matrix_list);

signals:
    void menuClosed(std::vector<Matrix> matrix_list);

};

#endif // OPERMENU_H
