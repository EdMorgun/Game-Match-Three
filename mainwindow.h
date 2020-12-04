#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QPushButton"
#include "QLabel"
#include "game.h"
#include "QFont"
#include "QMediaPlayer"
#include "QMediaPlaylist"
#include "memory"

extern int SIZE;

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void createTimeLabel();
    void createButton();
    void createScoreLabel();
    void createLineEdit();
    void createMusic();
    void createTimer();
    void createRandom();

private:
    std::unique_ptr<Game> game;
    QTimer *timer;
    QImage background;
    Ui::MainWindow *ui;
    QPushButton *button;
    QLabel *timeLabel, *scoreLabel;
    QLineEdit *lineEdit;
    QMediaPlayer *mediaPlayer;
    QMediaPlaylist *playList;

private slots:
    void frame();
    void pressButton();
};

#endif // MAINWINDOW_H
