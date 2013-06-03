#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "sub3dtoolgui.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->layout()->setSizeConstraint(QLayout::SetFixedSize);

    connect(this->centralWidget(), SIGNAL(closeProgram()), this, SLOT(close()));
    connect(this->centralWidget(), SIGNAL(newStatus(QString)), ui->statusBar, SLOT(showMessage(QString)));

    sub3dtoolgui *g = (sub3dtoolgui*) this->centralWidget();
    g->init();
}

MainWindow::~MainWindow()
{
    delete ui;
}
