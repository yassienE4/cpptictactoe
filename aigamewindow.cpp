#include "aigamewindow.h"
#include <QRandomGenerator>
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
    // check the row of the last move
    if (gameMatrix[row][0] == player && gameMatrix[row][1] == player && gameMatrix[row][2] == player)
        return true;

    // check the column of the last move
    if (gameMatrix[0][col] == player && gameMatrix[1][col] == player && gameMatrix[2][col] == player)
        return true;

    // check the diagonal if applicable
    if (row == col && gameMatrix[0][0] == player && gameMatrix[1][1] == player && gameMatrix[2][2] == player)
        return true;

    // check the other diagonal if applicable
    if (row + col == 2 && gameMatrix[0][2] == player && gameMatrix[1][1] == player && gameMatrix[2][0] == player)
        return true;

    return false;
}
bool AiGameWindow::checkwinall(std::vector<std::vector<CellState>> board, CellState player)
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
    }
    // Columns
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;
    }
    // Diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;
    if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
        return true;

    return false;

}
bool AiGameWindow::checkdraw(std::vector<std::vector<CellState>> board)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // If any cell is empty, it's not a draw
            if (board[i][j] == CellState::Empty)
            {
                return false;
            }
        }
    }

    return true;
}

void AiGameWindow::restartPress()
{

}
void AiGameWindow::aiTurn()
{
    bool hasMove = false;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (gameMatrix[i][j] == CellState::Empty)
            {
                hasMove = true;
                break;
            }
        }
        if (hasMove) break;
    }
    if (!hasMove)
    {
        win("Draw");
        return; // No moves available, end turn
    }
    if (diffuculty == 1) // easy = purely random 
    {
        easymove();
    }
    if (diffuculty == 2) // medium = half random half algorithm
    {
        if (mcount % 2 == 0)
        {
            easymove();
        }
        else
        {
            hardmove();
        }
        mcount++;
    }
    if (diffuculty == 3) // hard impossible using minmax
    {
        hardmove();
    }
    turn++;
}
void AiGameWindow::easymove()
{
    
    bool done = false;
    while (!done)
    {
        int a = QRandomGenerator::global()->bounded(3);
        int b = QRandomGenerator::global()->bounded(3);
        if (gameMatrix[a][b] == CellState::Empty)
        {
            gameMatrix[a][b] = CellState::PlayerO;
            buttonMatrix[a][b]->setText("O");
            buttonMatrix[a][b]->setEnabled(false);
            done = true;
            if (checkwin(a, b, CellState::PlayerO))
            {
                win("O");
                return;
            }
        }
    }
}
void AiGameWindow::hardmove()
{
    auto result = minmax(gameMatrix, false);
    auto *move = &result.second;
    if (move == nullptr || !move->first || !move->second)
    {
        // If no valid move is returned, declare a draw and return.
        win("Draw");
        return;
    }
    gameMatrix[move->first][move->second] = CellState::PlayerO;
    buttonMatrix[move->first][move->second]->setText("0");
    buttonMatrix[move->first][move->second]->setEnabled(false);
    if (checkwin(move->first,move->second, CellState::PlayerO))
    {
        win("O");
        return;
    }

}
void AiGameWindow::backpress()
{

}
std::pair<int,std::pair<int,int>> AiGameWindow::minmax(std::vector<std::vector<CellState>> board, bool maximising)
{
    // base cases

    // if x wins
    if (checkwinall(board, CellState::PlayerX)) // player 1 maximiing
    {
        // returns (1,(null,null))
        std::pair<int, std::pair<int, int>> myPair = {1, {-10, -10}};
        return myPair; // eval pos1, coords in pos2
    }

    // if o wins
    if (checkwinall(board, CellState::PlayerO)) // player 2 minimising
    {
        // returns (-1,(null,null))
        std::pair<int, std::pair<int, int>> myPair = {-1, {-10, -10}};
        return myPair;
    }

    // if draw
    if (checkdraw(board))
    {
        // returns (0,(null,null))
        std::pair<int, std::pair<int, int>> myPair = {0, {-10, -10}};
        return myPair;
    }

    // alogorithm here
    if (maximising)
    {
        int maxEval = -100;
        std::pair<int,int> *bestmove = nullptr; // will contain coords of best move
        std::vector<std::pair<int,int>> emptySquares = getEmptySquares(board); // array of empty coords

        for (auto pair : emptySquares) //for each set of coords that are empty
        {
            std::vector<std::vector<CellState>> boardCopy = cloneBoard(board);
            boardCopy[pair.first][pair.second] = CellState::PlayerX;
            int eval = minmax(boardCopy, false).first;
            if (eval > maxEval)
            {
                maxEval = eval;
                bestmove = &pair;
            }
        }
        std::pair<int, std::pair<int, int>> returnvalue = {maxEval, {bestmove->first,bestmove->second}};
        return returnvalue;
    }
    else
    {
        int minEval = 100;
        std::pair<int,int> *bestmove = nullptr;
        std::vector<std::pair<int,int>> emptySquares = getEmptySquares(board);

        for (auto pair : emptySquares)
        {

            std::vector<std::vector<CellState>> boardCopy = cloneBoard(board);
            boardCopy[pair.first][pair.second] = CellState::PlayerO;
            int eval = minmax(boardCopy, true).first;
            if (eval < minEval)
            {
                minEval = eval;
                bestmove = &pair;
            }
        }

        std::pair<int, std::pair<int, int>> returnvalue = {minEval, {bestmove->first,bestmove->second}};
        return returnvalue;
    }
}
std::vector<std::pair<int,int>> AiGameWindow::getEmptySquares(std::vector<std::vector<CellState>> board)
{
    std::vector<std::pair<int,int>> emptySquares;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == CellState::Empty)
            {
                emptySquares.push_back(std::make_pair(i,j));
            }
        }
    }
    return emptySquares;

}
std::vector<std::vector<AiGameWindow::CellState>> AiGameWindow::cloneBoard(std::vector<std::vector<CellState>> original)
{
    std::vector<std::vector<CellState>> clone;
    for(auto row : original)
    {
        clone.push_back(row);
    }
    return clone;

}
