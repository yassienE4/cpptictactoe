#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aigamewindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_newGame_clicked()
{
    AiGameWindow *x = new AiGameWindow(1);
    this->hide();
    x->show();
}

