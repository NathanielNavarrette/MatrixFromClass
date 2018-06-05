#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLayout>
#include <QScrollArea>
#include <QSettings>
#include <QObject>

#include "matrixwindow.h"
#include "matrixview.h"
#include "opermenu.h"

enum SizeConstraint { SetDefaultConstraint, SetFixedSize, SetMinimumSize, SetMaximumSize, SetMinAndMaxSize, SetNoConstraint };

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    std::vector<Matrix> inputtedMatricies;
    std::vector<QWidget*> outputWidgets;
    std::vector<QWidget*> outLabels;

    QWidget *optionsMenu = new QWidget(this);
    QVBoxLayout *m_layout = new QVBoxLayout(this);
    QHBoxLayout *optionsLayout = new QHBoxLayout(optionsMenu);
    QWidget *addMatrix = new QPushButton("Add a Matrix", optionsMenu);
    QWidget *clearScreen = new QPushButton("Clear Screen", optionsMenu);
    QWidget *operationButton = new QPushButton("Operations", optionsMenu);
    QWidget *autoButton = new QPushButton("Auto run the program", optionsMenu);

    QWidget *matrixViewArea = new matrixWindow(this);
    QWidget *operationMenu = new OperMenu(this);

public slots:
    void addMatrixSlot(bool pressed);
    void finishedAddingMatrix(Matrix add_this);
    void addedMatrixSlot(Matrix viewThis);
    void viesResultingMatrix(Matrix lhs, Matrix rhs, Matrix result, QString operation);
    void tempSlotDebug(bool pressed);
    void operationButtonSending(bool pressed);
    void clearScreenSlot(bool pressed);
    void operMenuClosed(std::vector<Matrix> recieved_list);
    void autRunSlot(bool clicked);

signals:
    void addingMatrix(bool);
    void autoRunSig(bool);
    void operationButtonSent(std::vector<Matrix>);
    void doOperations(std::vector<Matrix>);
};

#endif // MAINWINDOW_H
