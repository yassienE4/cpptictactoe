#include "aigamewindow.h"
#include <QRandomGenerator>
#include <string>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QDialog>
using namespace std;

int maxDepth = 8; // 8 is the max anyways if there was no depth limiter
int totalevals =0;

AiGameWindow::AiGameWindow(int diff, QWidget *parent) :
    QMainWindow(parent)
{
    this->setFixedSize(300,300);
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
    int startY = 50;  // Starting Y position
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
    Restart = new QPushButton();
    Restart->setText("Restart");
    Restart->move(75,0);
    Restart->setFixedSize(100,40);
    Restart->setParent(this);
    connect(Restart, &QPushButton::clicked, this, &AiGameWindow::restartPress);

    EvalLabel = new QLabel();
    EvalLabel->move(180, 0);
    EvalLabel->setFixedSize(400,40);
    EvalLabel->setParent(this);
    EvalLabel->setText("evals");

}

AiGameWindow::~AiGameWindow()
{

}

void AiGameWindow::buttonPress()
{
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    if(clickedButton == nullptr || clickedButton->isEnabled() == false)
        return;
    string name = clickedButton->objectName().toStdString();
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
bool AiGameWindow::checkwinall( vector< vector<CellState>> board, CellState player)
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
bool AiGameWindow::checkdraw( vector< vector<CellState>> board)
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
    auto result = minmax(gameMatrix, false, 0); // Start with depth 0
    auto move = result.second;
    if (!move.first.has_value() || !move.second.has_value())
    {
        // If no valid move is returned, declare a draw and return.
        win("Draw");
        return;
    }
    gameMatrix[move.first.value()][move.second.value()] = CellState::PlayerO;
    buttonMatrix[move.first.value()][move.second.value()]->setText("O");
    buttonMatrix[move.first.value()][move.second.value()]->setEnabled(false);
    if (checkwin(move.first.value(),move.second.value(), CellState::PlayerO))
    {
        win("O");
        return;
    }

}

pair<int, pair<optional<int>,optional<int>>> AiGameWindow::minmax(vector<vector<CellState>> board, bool maximising, int depth, int evalutations)
{
    // base cases

    // if x wins
    if (checkwinall(board, CellState::PlayerX)) // player 1 maximiing
    {
        // returns (1,(null,null))
        pair<int,  pair<optional<int>, optional<int>>> myPair = {1, {nullopt, nullopt}};
        return myPair; // eval pos1, coords in pos2
    }

    // if o wins
    if (checkwinall(board, CellState::PlayerO)) // player 2 minimising
    {
        // returns (-1,(null,null))
        pair<int,  pair<optional<int>, optional<int>>> myPair = {-1, {nullopt, nullopt}};
        return myPair;
    }

    // if draw
    if (checkdraw(board))
    {
        // returns (0,(null,null))
        pair<int,  pair<optional<int>, optional<int>>> myPair = {0, {nullopt, nullopt}};
        return myPair;
    }
    
    // Optional: Set a maximum depth to limit the search
    if (depth >= maxDepth) {
        // Return a heuristic value when max depth is reached
        pair<int, pair<optional<int>, optional<int>>> myPair = {0, {nullopt, nullopt}};
        return myPair;
    }

    // alogorithm here
    if (maximising)
    {
        int maxEval = -100;
        pair<optional<int>, optional<int> > bestmove; // will contain coords of best move
        vector< pair<int,int>> emptySquares = getEmptySquares(board); // array of empty coords

        for (auto pair : emptySquares) //for each set of coords that are empty
        {
            vector< vector<CellState>> boardCopy = cloneBoard(board);
            boardCopy[pair.first][pair.second] = CellState::PlayerX;
            int eval = minmax(boardCopy, false, depth + 1).first;
            evalutations++;
            totalevals = totalevals + evalutations;
            if (eval > maxEval)
            {
                maxEval = eval;
                bestmove = pair;
            }
        }
        EvalLabel->setText(QString::fromStdString(to_string(totalevals)));
        pair<int,  pair<optional<int>, optional<int> > > returnvalue = {maxEval, {bestmove.first,bestmove.second}};
        return returnvalue;
    }
    else
    {
        int minEval = 100;
        pair<optional<int>, optional<int> > bestmove;
        vector< pair<int,int>> emptySquares = getEmptySquares(board);

        for (auto pair : emptySquares)
        {
            vector< vector<CellState>> boardCopy = cloneBoard(board);
            boardCopy[pair.first][pair.second] = CellState::PlayerO;
            int eval = minmax(boardCopy, true, depth + 1).first;
            evalutations++;
            totalevals = totalevals + evalutations;
            if (eval < minEval)
            {
                minEval = eval;
                bestmove = pair;
            }
        }
        EvalLabel->setText(QString::fromStdString(to_string(totalevals)));
        pair<int,  pair<optional<int>, optional<int> > > returnvalue = {minEval, {bestmove.first,bestmove.second}};
        return returnvalue;
    }
}

 vector< pair<int,int>> AiGameWindow::getEmptySquares( vector< vector<CellState>> board)
{
    vector< pair<int,int>> emptySquares;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == CellState::Empty)
            {
                emptySquares.push_back( make_pair(i,j));
            }
        }
    }
    return emptySquares;

}
 vector< vector<AiGameWindow::CellState>> AiGameWindow::cloneBoard( vector< vector<CellState>> original)
{
    vector< vector<CellState>> clone;
    for(auto row : original)
    {
        clone.push_back(row);
    }
    return clone;

}


void AiGameWindow::backpress()
{

}

void AiGameWindow::restartPress()
{
    turn = 0;
    for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j <3; j++)
        {
            gameMatrix[i][j] = CellState::Empty;
            buttonMatrix[i][j]->setText("");
            buttonMatrix[i][j]->setEnabled(true);
        }
    }

}

void AiGameWindow::win(string x)
{
    showWinnerPopup(x);
}

void AiGameWindow::showWinnerPopup(string x) {

    QString winstring;
    switch (x[0]) {
    case 'X':
        winstring = "X Won!";
        break;
    case 'O':
        winstring = "O Won!";
        break;
    default:
        winstring = "DRAW!";
        break;
    }


    QDialog popup(this);
    popup.setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    popup.setFixedSize(100, 100);

    QVBoxLayout layout(&popup);
    QLabel label(winstring, &popup);
    label.setAlignment(Qt::AlignCenter);

    QPushButton closeButton("Close", &popup);
    connect(&closeButton, &QPushButton::clicked, &popup, &QDialog::accept);

    layout.addWidget(&label);
    layout.addWidget(&closeButton);
    layout.setAlignment(Qt::AlignCenter);

    popup.exec(); // Modal dialog (use popup.show() for non-modal)
}
