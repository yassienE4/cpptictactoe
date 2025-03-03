#ifndef AIGAMEWINDOW_H
#define AIGAMEWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QPushButton>



class AiGameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AiGameWindow(int diff, QWidget *parent = nullptr);
    ~AiGameWindow();
    enum class CellState { Empty = -1, PlayerX = 1, PlayerO = 0 };

private:


    int turn = 0;
    int diffuculty = 0;
    int mcount = 0;
    std::vector<std::vector<CellState>> gameMatrix;
    std::vector<std::vector<QPushButton*>> buttonMatrix;
    void win(std::string x);
    bool checkwin(int row, int col, CellState player);
    bool checkwinall(std::vector<std::vector<CellState>> board, CellState player);
    bool checkdraw(std::vector<std::vector<CellState>> board);
    void buttonPress();
    void restartPress();
    void aiTurn();
    void easymove();
    void hardmove();
    void backpress();
    std::pair<int,std::pair<int,int>> minmax(std::vector<std::vector<CellState>> board, bool maximising);
    std::vector<std::pair<int,int>> getEmptySquares(std::vector<std::vector<CellState>> board);
    std::vector<std::vector<CellState>> cloneBoard(std::vector<std::vector<CellState>> original);
    QPushButton* TL;
    QPushButton* TM;
    QPushButton* TR;
    QPushButton* ML;
    QPushButton* MM;
    QPushButton* MR;
    QPushButton* BL;
    QPushButton* BM;
    QPushButton* BR;


};

#endif // AIGAMEWINDOW_H
