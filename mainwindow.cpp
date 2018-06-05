#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    optionsLayout->addWidget(addMatrix);
    optionsLayout->stretch(1);
    optionsLayout->addWidget(operationButton);
    optionsLayout->stretch(1);
    optionsLayout->addWidget(clearScreen);
    optionsLayout->stretch(1);
    optionsLayout->addWidget(autoButton);
    optionsLayout->stretch(1);
    optionsMenu->setFixedHeight(50);

    m_layout->addWidget(optionsMenu);
    m_layout->addWidget(matrixViewArea);

    ui->centralWidget->setLayout(m_layout);
    this->setMinimumHeight(600);
    this->setMinimumWidth(800);

    connect(this, SIGNAL(doOperations(std::vector<Matrix>)), matrixViewArea, SLOT(doOpers(std::vector<Matrix>)));
    connect(addMatrix, SIGNAL(clicked(bool)), this, SLOT(addMatrixSlot(bool)));

    connect(clearScreen, SIGNAL(clicked(bool)), this, SLOT(tempSlotDebug(bool)));
    connect(clearScreen, SIGNAL(clicked(bool)), this, SLOT(clearScreenSlot(bool)));
    connect(operationButton, SIGNAL(clicked(bool)), this, SLOT(operationButtonSending(bool)));
    connect(autoButton, SIGNAL(clicked(bool)), this, SLOT(autRunSlot(bool)));

    connect(matrixViewArea, SIGNAL(addedMatrixSignal(Matrix)), this, SLOT(addedMatrixSlot(Matrix)));
    connect(matrixViewArea, SIGNAL(resultingMatrixSignal(Matrix, Matrix, Matrix, QString)) , this, SLOT(viesResultingMatrix(Matrix, Matrix, Matrix, QString)));
    connect(matrixViewArea, SIGNAL(sendMatrix(Matrix)), this, SLOT(finishedAddingMatrix(Matrix)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addMatrixSlot(bool pressed)
{
    emit addingMatrix(pressed);
}

void MainWindow::addedMatrixSlot(Matrix viewThis)
{
    QWidget *add_this = new QLabel(MatrixView(viewThis, this).get_string());
    m_layout->addWidget(add_this);
}
void MainWindow::viesResultingMatrix(Matrix lhs, Matrix rhs, Matrix result, QString operation)
{
    QWidget *matrixView = new matrixWindow(matrixViewArea);
    QHBoxLayout *matrixLayout = new QHBoxLayout(matrixView);
    QWidget *l1 = new QLabel(MatrixView(lhs, this).get_string());
    QWidget *l2 = new QLabel(operation);
    QWidget *l3 = new QLabel(MatrixView(rhs, this).get_string());
    QWidget *l4 = new QLabel(QString("="));
    QWidget *l5 = new QLabel(MatrixView(result, this).get_string());

    matrixLayout->addWidget(l1);
    matrixLayout->addWidget(l2);
    matrixLayout->addWidget(l3);
    matrixLayout->addWidget(l4);
    matrixLayout->addWidget(l5);

    outputWidgets.push_back(l1);
    outputWidgets.push_back(l2);
    outputWidgets.push_back(l3);
    outputWidgets.push_back(l4);
    outputWidgets.push_back(l5);

    outLabels.push_back(matrixView);

    m_layout->addWidget(matrixView);
}

void MainWindow::finishedAddingMatrix(Matrix add_this)
{
    inputtedMatricies.push_back(add_this);
}

void MainWindow::operationButtonSending(bool)
{
    emit operationButtonSent(inputtedMatricies);
}

void MainWindow::operMenuClosed(std::vector<Matrix> recieved_list)
{
    emit doOperations(recieved_list);
}

void MainWindow::autRunSlot(bool clicked)
{
    emit autoRunSig(clicked);
}

void MainWindow::clearScreenSlot(bool)
{
    //attempt to clear the screen by deleting the child objects
    std::vector<QWidget*> emptyWidgets;

    //delete the widgets in memory as well as remove them from the layout
    for(int i=0;i<outputWidgets.size();i++)
    {
        m_layout->removeWidget(outputWidgets.at(i));
        delete outputWidgets.at(i);
    }
    outputWidgets = emptyWidgets;

    //delete the label widgets from memory
    for(int i=0;i<outLabels.size();i++)
    {
        delete outLabels.at(i);
    }
    outLabels = emptyWidgets;
}

void MainWindow::tempSlotDebug(bool pressed)
{
    for(int i=0;i<inputtedMatricies.size();i++)
    {
        qDebug() << "Matrix : " << i+1;
        for(int j=0;j<inputtedMatricies.at(i).get_rows();j++)
        {
            for(int k=0;k<inputtedMatricies.at(i).get_cols();k++)
            {
                qDebug() << inputtedMatricies.at(i).get_value_at(j, k);
            }
        }
    }
}
