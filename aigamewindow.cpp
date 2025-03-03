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

}

AiGameWindow::~AiGameWindow()
{

}
