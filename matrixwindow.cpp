#include "matrixwindow.h"

matrixWindow::matrixWindow(QWidget *parent) : QWidget(parent)
{
    connect(parent, SIGNAL(addingMatrix(bool)), this, SLOT(addingMatrix(bool)));
    connect(parent, SIGNAL(autoRunSig(bool)), this, SLOT(autoRun(bool)));
    connect(this, SIGNAL(matrixWindowSignal()), this, SLOT(addMatrixAccept()));
}

void matrixWindow::addMatrixAccept()
{
    addMatrixDialog();
}

void matrixWindow::autoRun(bool clicked)
{
    //randomly create the number for rows and collumns for auto run function
    int max_value = 3;
    qsrand(QDateTime::currentMSecsSinceEpoch()%5000);
    int randRows = qrand();
    int randCols = qrand();
    randRows = (randRows % max_value) + 1;
    randCols = (randCols % max_value) + 1;

    //when ever the cols = 1, make rows = 1 so that it's just a scalar
    if(randCols == 1)
        randRows = 1;

    this->rows = randRows;
    this->collums = randCols;

    //call the rest of the functio to pass and create actual Matrix varible
    createMatrixAuto();

    //qDebug() << "Random Rows: " << randRows << " Random Cols: " << randCols;
}

void matrixWindow::createMatrixAuto()
{
    qDebug() << "Rows: " << rows << " Cols: " << collums;

    int max_value = 3;
    qsrand(QDateTime::currentMSecsSinceEpoch()%5000);

    int varibleCount = rows*collums;
    qDebug() << "Varible Count within the matrix: " << varibleCount;
    std::vector<int> vector_tmp;

    for(int i=0;i<varibleCount;i++)
    {
        int randValue = qrand();
        randValue %= 17;
        vector_tmp.push_back(randValue);
    }

    Matrix m_matrix(vector_tmp, rows, collums);
    emit sendMatrix(m_matrix);
}

void matrixWindow::addMatrixDialog()
{
    std::vector<int> c_tmp;

    QDialog dialog(this);
    dialog.setMinimumHeight(225);
    dialog.setMinimumWidth(225);

    // Use a layout allowing to have a label next to each field
    QFormLayout form(&dialog);

    // Add some text above the fields
    form.addRow(new QLabel("Values in Matrix:"));

    // Add the lineEdits with their respective labels
    QList<QLineEdit *> fields;
    QString label[collums];
    QLineEdit *lineEdit = NULL;

    int max_value = 25;
    qsrand(QDateTime::currentMSecsSinceEpoch()%5000);

    for(int i = 0; i < rows; ++i)
    {
        for(int j = 0; j < collums; j++)
        {
            //initialize and get a random varible each time
            int randnumb = qrand();
            randnumb %= max_value;

            label[j] = QString("Row:" "%1").arg(i + 1);
            lineEdit = new QLineEdit(QString::number(randnumb), &dialog);
            form.addRow("Row" + QString::number(i+1) + " ,Column" + QString::number(j+1), lineEdit);
            fields << lineEdit;
        }
    }

    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    //QObject::connect(&buttonBox, SIGNAL(accepted()), parent())        //connect the accpted signal to previous dialog to close both windows at once

    // Show the dialog as modal
    if (dialog.exec() == QDialog::Accepted){
        // If the user didn't dismiss the dialog, do something with the fields
        foreach(QLineEdit * lineEdit, fields)
        {
            c_tmp.push_back(lineEdit->text().toInt());
        }
        Matrix m_matrix(c_tmp, rows, collums);
        emit sendMatrix(m_matrix);
    }else{
        //just close and do nothing
    }
}

void matrixWindow::doOpers(std::vector<Matrix> recieved_list)
{
    //the actual part of the program that does the operations

    Matrix addition = recieved_list.at(0)+recieved_list.at(1);
    //emit addedMatrixSignal(addition);
    emit resultingMatrixSignal(recieved_list.at(0), recieved_list.at(1), addition, QString("+"));
    addition.m_debug_this(QString("Addition"));

    Matrix subtract = recieved_list.at(0)-recieved_list.at(1);
    //emit addedMatrixSignal(subtract);
    emit resultingMatrixSignal(recieved_list.at(0), recieved_list.at(1), subtract, QString("-"));
    subtract.m_debug_this(QString("Subtraction"));

    Matrix multi = recieved_list.at(0)*recieved_list.at(1);
    //emit addedMatrixSignal(multi);
    emit resultingMatrixSignal(recieved_list.at(0), recieved_list.at(1), multi, QString("*"));
    multi.m_debug_this(QString("Multiplication"));
}

void matrixWindow::addingMatrix(bool clicked)
{
    QDialog dialog(this);
    // Use a layout allowing to have a label next to each field
    QFormLayout form(&dialog);

    // Add some text above the fields
    form.addRow(new QLabel("Size of Matrix:"));

    // Add the lineEdits with their respective labels
    QList<QLineEdit *> fields;

    for(int i = 0; i < 2; ++i) {
        QLineEdit *lineEdit = NULL;
        QString label;
        if(i==0)
        {
            label = QString("Rows:" "%1").arg(i + 1);
            lineEdit = new QLineEdit(QString::number(3), &dialog);
        }else if(i == 1){
            label = QString("Collums:" "%1").arg(i + 1);
            lineEdit = new QLineEdit(QString::number(3), &dialog);
        }

        form.addRow(label, lineEdit);

        fields << lineEdit;
    }

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    // Show the dialog as modal
    if (dialog.exec() == QDialog::Accepted)
    {
        qDebug() << "into if dialog::accepted";
        // If the user didn't dismiss the dialog, do something with the fields
        foreach(QLineEdit * lineEdit, fields) {
            if(fields.constFirst()->text().toInt() == 0 || fields.constLast()->text().toInt() == 0 )
            {
                QMessageBox::critical(this, tr("Invalid Data"), tr("You entered invalid data"));
            }else{
                this->rows = fields.constFirst()->text().toInt();
                this->collums = fields.constLast()->text().toInt();
            }
        }
        emit matrixWindowSignal();
    }

}
