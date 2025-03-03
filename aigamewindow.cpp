#include "aigamewindow.h"
#include <string>

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
            connect(buttonMatrix[i][j], &QPushButton::clicked, this, &AiGameWindow::buttonPress);
            buttonMatrix[i][j]->setObjectName(QString::number(i) + QString::number(j));
        }
    }

}

AiGameWindow::~AiGameWindow()
{

}

void AiGameWindow::buttonPress()
{
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    if(clickedButton == nullptr || clickedButton->isEnabled() == false)
        return;
    std::string name = clickedButton->objectName().toStdString();
    int row = name[0] - '0';
    int col = name[1] - '0';

    if(turn %2 == 0)
    {
        clickedButton->setText("X");
        gameMatrix[row][col] = CellState::PlayerX;
        clickedButton->setEnabled(false);
        if(checkwin(row, col, CellState::PlayerX))
        {
            win("X");
            return;
        }
        turn++;
        aiTurn();
    }


}
void AiGameWindow::win(std::string x)
{

}
bool AiGameWindow::checkwin(int row, int col, CellState player)
{

}
bool AiGameWindow::checkwinall(std::vector<std::vector<CellState>> board, CellState player)
{

}
bool AiGameWindow::checkdraw(std::vector<std::vector<CellState>> board)
{

}

void AiGameWindow::restartPress()
{

}
void AiGameWindow::aiTurn()
{

}
void AiGameWindow::easymove()
{

}
void AiGameWindow::hardmove()
{

}
void AiGameWindow::backpress()
{

}
std::pair<int,std::pair<int,int>> AiGameWindow::minmax(std::vector<std::vector<CellState>> board, bool maximising)
{

}
std::vector<std::pair<int,int>> AiGameWindow::getEmptySquares(std::vector<std::vector<CellState>> board)
{

}
std::vector<std::vector<AiGameWindow::CellState>> AiGameWindow::cloneBoard(std::vector<std::vector<CellState>> original)
{

}
