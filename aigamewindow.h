#ifndef AIGAMEWINDOW_H
#define AIGAMEWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QPushButton>

namespace Ui {
class AiGameWindow;
}

class AiGameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AiGameWindow(QWidget *parent = nullptr);
    ~AiGameWindow();
    enum class CellState { Empty = -1, PlayerX = 1, PlayerO = 0 };

private:
    Ui::AiGameWindow *ui;

    int turn = 0;
    int diffuculty = 0;
    int mcount = 0;
    std::vector<std::vector<CellState>> gameMatrix;
    std::vector<std::vector<QPushButton>> buttonMatrix;
    void win();
    bool checkwin();
    bool checkwinall();
    bool checkdraw();
    void buttonPress();
    void restartPress();
    void aiTurn();
    void easymove();
    void hardmove();
    void backpress();
    std::pair<int,std::pair<int,int>> minmax();
    std::vector<std::pair<int,int>> getEmptySquares();
    std::vector<std::vector<CellState>> cloneBoard();

};

#endif // AIGAMEWINDOW_H
