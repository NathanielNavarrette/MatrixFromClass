#include "opermenu.h"

OperMenu::OperMenu(QWidget *parent) : QWidget(parent)
{
    connect(parent, SIGNAL(operationButtonSent(std::vector<Matrix>)), this, SLOT(operationsMenuSlot(std::vector<Matrix>)));
    connect(this, SIGNAL(menuClosed(std::vector<Matrix>)), parent, SLOT(operMenuClosed(std::vector<Matrix>)));
}

void OperMenu::operationsMenuSlot(std::vector<Matrix> matrix_list)
{
    qDebug() << "Opening Operation Menu";

    QDialog dialog(this);
    dialog.setMinimumHeight(225);
    dialog.setMinimumWidth(225);

    // Use a layout allowing to have a label next to each field
    QFormLayout form(&dialog);

    // Add some text above the fields
    form.addRow(new QLabel("Choose Matrix To do Operations on:\n"));

    // Add the lineEdits with their respective labels
    QList<QLineEdit *> fields;
    //QString label[collums];
    QCheckBox *m_rbuttons[matrix_list.size()];
    QWidget *matrix_display_tmp = NULL;
    QLineEdit *lineEdit = NULL;

    for(int i=0; i < matrix_list.size(); i++)
    {
        qDebug() << "adding to dialog, loop: " << i;
        m_rbuttons[i] = new QCheckBox(QString("Matrix:" "%1").arg(i+1), this);
        //lineEdit = new QLineEdit(QString::number(j+i), &dialog);
        qDebug() << "add to dialog debug 1";
        matrix_display_tmp = new QLabel(MatrixView(matrix_list.at(i), this).get_string()); // this is the line that throws it
        qDebug() << "add to dialog debug 2";
        form.addRow((m_rbuttons[i]), matrix_display_tmp);
        qDebug() << "add to dialog debug 3";
        fields << lineEdit;
        qDebug() << "add to dialog debug 4";
    }

    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    // Show the dialog as modal
    if (dialog.exec() == QDialog::Accepted)
    {
        int count=0;
        std::vector<Matrix> send_list;
        // If the user didn't dismiss the dialog, do something with the fields
        for(int i=0;i<matrix_list.size();i++)
        {
            if(m_rbuttons[i]->isChecked() && count < 2)
            {
                qDebug() << "The matrix " << (i+1) << " in the list was checked";
                send_list.push_back(matrix_list.at(i));
                count++;
            }

            if(count >= 2)
            {
                qDebug() << "sent list";
                emit menuClosed(send_list);
            }
        }

    }
}
