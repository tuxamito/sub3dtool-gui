#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->layout()->setSizeConstraint(QLayout::SetFixedSize);

    connect(this->centralWidget(), SIGNAL(closeProgram()), this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
