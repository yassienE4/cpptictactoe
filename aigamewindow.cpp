#include "aigamewindow.h"
#include "ui_aigamewindow.h"

AiGameWindow::AiGameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AiGameWindow)
{
    ui->setupUi(this);

}

AiGameWindow::~AiGameWindow()
{
    delete ui;
}
