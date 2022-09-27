#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <point.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(new Point(this, 0, new Position(10, 10)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

