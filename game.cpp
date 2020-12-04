#include "game.h"
#include "QWidget"
#include "stateinmainmenu.h"
#include "stdio.h"
#include "qmessagebox.h"

extern int SIZE;

enum
{
    StateInMainMenu = 0,
    StateInGame = 1,

    alphabetSpaceX = 17,
    alphabetSpaceY = 20,

    alphabetCellSize = 236,

    indentX = 44,
    indentY = 23,
};

Game::Game(QLabel *timeLabel, QLabel *scoreLabel, QLineEdit *lineEdit, QPushButton *button)
    : timeLabel(timeLabel), scoreLabel(scoreLabel), lineEdit(lineEdit), button(button)
{
    alphabet.load(":/Images/alphabet.png");
    state = new class StateInMainMenu();
    recordTable = new RecordTable();
    records = recordTable->getRecordTable();
    LP = new LabelesPainter(timeLabel, scoreLabel);

}

void Game::setState(StateGame *s)
{
    this->state = s;
}

void Game::mouseMoveEvent(QMouseEvent *e)
{
    switch (state->getIdState())
    {
    case StateInMainMenu:
        break;
    case StateInGame:
        map->mouseMoveEvent(e);
        break;
    }
}

void Game::pressButton()
{
    switch (state->getIdState())
    {
    case StateInMainMenu:
        inGame();
        break;
    case StateInGame:
        if(map->getTime() > 0)inMainMenu();
        break;
    }
}

void Game::paint(QPainter *painter)
{
    switch (state->getIdState())
    {
    case StateInMainMenu:
        paintRecordTable(painter);
        break;
    case StateInGame:
        map->paint(painter);
        LP->patntLabels(map->getTime(), map->getScore());
        break;
    }
}

QImage Game::getImageSymbol(char ch)
{
    switch (ch)
    {
    case 'A':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*0, (alphabetSpaceY + alphabetCellSize)*0,
                              alphabetCellSize, alphabetCellSize);
    case 'B':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*1, (alphabetSpaceY + alphabetCellSize)*0,
                              alphabetCellSize, alphabetCellSize);
    case 'C':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*2, (alphabetSpaceY + alphabetCellSize)*0,
                              alphabetCellSize, alphabetCellSize);
    case 'D':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*3, (alphabetSpaceY + alphabetCellSize)*0,
                              alphabetCellSize, alphabetCellSize);
    case 'E':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*4, (alphabetSpaceY + alphabetCellSize)*0,
                              alphabetCellSize, alphabetCellSize);
    case 'F':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*5, (alphabetSpaceY + alphabetCellSize)*0,
                              alphabetCellSize, alphabetCellSize);
    case 'G':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*0, (alphabetSpaceY + alphabetCellSize)*1,
                              alphabetCellSize, alphabetCellSize);
    case 'H':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*1, (alphabetSpaceY + alphabetCellSize)*1,
                              alphabetCellSize, alphabetCellSize);
    case 'I':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*2, (alphabetSpaceY + alphabetCellSize)*1,
                              alphabetCellSize, alphabetCellSize);
    case 'J':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*3, (alphabetSpaceY + alphabetCellSize)*1,
                              alphabetCellSize, alphabetCellSize);
    case 'K':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*4, (alphabetSpaceY + alphabetCellSize)*1,
                              alphabetCellSize, alphabetCellSize);
    case 'L':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*5, (alphabetSpaceY + alphabetCellSize)*1,
                              alphabetCellSize, alphabetCellSize);
    case 'M':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*0, (alphabetSpaceY + alphabetCellSize)*2,
                              alphabetCellSize, alphabetCellSize);
    case 'N':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*1, (alphabetSpaceY + alphabetCellSize)*2,
                              alphabetCellSize, alphabetCellSize);
    case 'O':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*2, (alphabetSpaceY + alphabetCellSize)*2,
                              alphabetCellSize, alphabetCellSize);
    case 'P':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*3, (alphabetSpaceY + alphabetCellSize)*2,
                              alphabetCellSize, alphabetCellSize);
    case 'Q':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*4, (alphabetSpaceY + alphabetCellSize)*2,
                              alphabetCellSize, alphabetCellSize);
    case 'R':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*5, (alphabetSpaceY + alphabetCellSize)*2,
                              alphabetCellSize, alphabetCellSize);
    case 'S':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*0, (alphabetSpaceY + alphabetCellSize)*3,
                              alphabetCellSize, alphabetCellSize);
    case 'T':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*1, (alphabetSpaceY + alphabetCellSize)*3,
                              alphabetCellSize, alphabetCellSize);
    case 'U':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*2, (alphabetSpaceY + alphabetCellSize)*3,
                              alphabetCellSize, alphabetCellSize);
    case 'V':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*3, (alphabetSpaceY + alphabetCellSize)*3,
                              alphabetCellSize, alphabetCellSize);
    case 'W':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*4, (alphabetSpaceY + alphabetCellSize)*3,
                              alphabetCellSize, alphabetCellSize);
    case 'X':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*5, (alphabetSpaceY + alphabetCellSize)*3,
                              alphabetCellSize, alphabetCellSize);
    case 'Y':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*0, (alphabetSpaceY + alphabetCellSize)*4,
                              alphabetCellSize, alphabetCellSize);
    case 'Z':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*1, (alphabetSpaceY + alphabetCellSize)*4,
                              alphabetCellSize, alphabetCellSize);
    case '0':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*2, (alphabetSpaceY + alphabetCellSize)*4,
                              alphabetCellSize, alphabetCellSize);
    case '1':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*3, (alphabetSpaceY + alphabetCellSize)*4,
                              alphabetCellSize, alphabetCellSize);
    case '2':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*4, (alphabetSpaceY + alphabetCellSize)*4,
                              alphabetCellSize, alphabetCellSize);
    case '3':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*5, (alphabetSpaceY + alphabetCellSize)*4,
                              alphabetCellSize, alphabetCellSize);
    case '4':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*0, (alphabetSpaceY + alphabetCellSize)*5,
                              alphabetCellSize, alphabetCellSize);
    case '5':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*1, (alphabetSpaceY + alphabetCellSize)*5,
                              alphabetCellSize, alphabetCellSize);
    case '6':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*2, (alphabetSpaceY + alphabetCellSize)*5,
                              alphabetCellSize, alphabetCellSize);
    case '7':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*3, (alphabetSpaceY + alphabetCellSize)*5,
                              alphabetCellSize, alphabetCellSize);
    case '8':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*4, (alphabetSpaceY + alphabetCellSize)*5,
                              alphabetCellSize, alphabetCellSize);
    case '9':
        return alphabet.copy((alphabetSpaceX + alphabetCellSize)*5, (alphabetSpaceY + alphabetCellSize)*5,
                              alphabetCellSize, alphabetCellSize);
    }
    return QImage();
}

void Game::paintRecordTable(QPainter *painter)
{
    int y = 0;
    for(std::multimap<int, std::string>::reverse_iterator iterator = records->rbegin(); iterator != records->rend(); iterator++)
    {
        if(y == 8) break;
        for(unsigned int i = 0; i < (*iterator).second.length(); i++)
        {
            QRect r(indentX + static_cast<int>(i)*SIZE, indentY + SIZE*y, SIZE, SIZE);
            painter->drawImage(r, getImageSymbol((*iterator).second[i]));
        }
        for(unsigned int i = 0; i <= std::to_string((*iterator).first).length(); i++)
        {
            QRect r(indentX + static_cast<int>(8-i)*SIZE, indentY + SIZE*y, SIZE, SIZE);
            painter->drawImage(r, getImageSymbol(std::to_string((*iterator).first)[std::to_string((*iterator).first).length()-i]));
        }
        y++;
    }
}

void Game::checkTimeUp()
{
    if(map->getTime() <= 0)
    {
        int totalScore = map->getScore();
        QMessageBox *msgBox1 = new QMessageBox;
        std::string s = lineEdit->text().toLocal8Bit().data();
        msgBox1->setWindowTitle("Time is UP!");
        msgBox1->setIcon(QMessageBox::Information);
        std::string text = "Your total scrore: " + std::to_string(totalScore);
        msgBox1->setText(text.c_str());
        msgBox1->setWindowModality(Qt::NonModal);
        msgBox1->show();
        msgBox1->exec();
        recordTable->writing(totalScore, s);
        inMainMenu();
    }
}

void Game::frame()
{
    switch (state->getIdState())
    {
    case StateInMainMenu:
        break;
    case StateInGame:
        map->frame();
        checkTimeUp();
        break;
    }
}

void Game::inGame()
{
    button->setText("STOP");
    map = new GameMap(timeLabel, scoreLabel);
    state->inGame(this);
}

void Game::inMainMenu()
{
    button->setText("START");
    records = recordTable->getRecordTable();
    state->inMainMenu(this);
    delete map;
}

Game::~Game()
{
    delete LP;
    delete recordTable;
    if(state->getIdState() == StateInGame) delete map;
    delete state;
}
