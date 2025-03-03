#include "aigamewindow.h"


AiGameWindow::AiGameWindow(int diff, QWidget *parent) :
    QMainWindow(parent)
{
    diffuculty = diff;
    buttonMatrix = {
        {TL, TM, TR},
        {ML, MM, MR},
        {BL, BM, BR}
    };
    gameMatrix = {
        {CellState::Empty,CellState::Empty,CellState::Empty},
        {CellState::Empty,CellState::Empty,CellState::Empty},
        {CellState::Empty,CellState::Empty,CellState::Empty}
    };
    turn = 0;
    mcount = 0;

    int startX = 0;  // Starting X position
    int startY = 0;  // Starting Y position
    int spacing = 100;  // Space between buttons
    for(int i =0; i < 3; i++)
    {
        for(int j = 0; j <3; j++)
        {
            buttonMatrix[i][j] = new QPushButton();
            buttonMatrix[i][j]->move(startX + j * spacing, startY + i * spacing);
            buttonMatrix[i][j]->setFixedSize(40, 40);
            buttonMatrix[i][j]->setParent(this);
        }
    }

}

AiGameWindow::~AiGameWindow()
{

}
