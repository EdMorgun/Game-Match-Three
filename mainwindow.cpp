#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QPushButton"
#include "QLabel"
#include "ctime"
#include "QTimer"
#include "QLineEdit"
#include "QMediaContent"

int SIZE;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(740,480);

    background.load(":/Images/background.png");

    createRandom();
    createMusic();
    createButton();
    createTimeLabel();
    createScoreLabel();
    createLineEdit();

    game = std::unique_ptr<Game>(new Game(timeLabel, scoreLabel, lineEdit, button));

    createTimer();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    SIZE = 54;
    QPainter painter(this);

    painter.drawImage(0,0,background);
    game->paint(&painter);

}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    game->mouseMoveEvent(e);
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    game->mouseMoveEvent(e);
}

void MainWindow::createTimeLabel()
{
    timeLabel = new QLabel("Time: 0:00", ui->centralWidget);
    timeLabel->setGeometry(500,24,220,50);
    timeLabel->setStyleSheet("QLabel { background-color : rgba(119, 238, 0, 175); color : blue; "
                             "border-style: solid; border-width: 2px; border-color: darkGreen; }");
    QFont f;
        f.setBold(true);
        f.setFamily("Comic Sans MS");
        f.setPointSize(26);
    timeLabel->setFont(f);
}

void MainWindow::createButton()
{
    button = new QPushButton("START", ui->centralWidget);
    button->setStyleSheet("QAbstractButton {"
                          "background: rgba(0,255,255,100); }");
    button->setGeometry(530,404,150,50);
    QFont f;
        f.setBold(true);
        f.setFamily("Comic Sans MS");
        f.setPointSize(26);
        button->setFont(f);
}

void MainWindow::createScoreLabel()
{
    scoreLabel = new QLabel("Score: 9999", ui->centralWidget);
    scoreLabel->setGeometry(500,124,220,50);
    scoreLabel->setStyleSheet("QLabel { background-color : rgba(119, 238, 0, 175); color : blue; "
                             "border-style: solid; border-width: 2px; border-color: darkGreen; }");
    QFont f;
        f.setBold(true);
        f.setFamily("Comic Sans MS");
        f.setPointSize(25);
    scoreLabel->setFont(f);
}

void MainWindow::createLineEdit()
{
    lineEdit = new QLineEdit(ui->centralWidget);
    lineEdit->setStyleSheet("QLineEdit { background-color : rgba(236, 255, 71, 175); color : rgba(255, 71, 144, 255); "
                            "border-style: solid; border-width: 2px; border-color: blue; }");
    lineEdit->setGeometry(600,240,120,60);
    QFont f;
        f.setBold(true);
        f.setFamily("Comic Sans MS");
        f.setPointSize(32);
    lineEdit->setFont(f);
    lineEdit->setMaxLength(3);
}

void MainWindow::createMusic()
{
    mediaPlayer = new QMediaPlayer(this);
    playList = new QMediaPlaylist(mediaPlayer);
    playList->addMedia(QUrl("qrc:/Images/song.wav"));
    playList->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    mediaPlayer->setMedia(playList);
    mediaPlayer->setVolume(25);
    mediaPlayer->play();
}

void MainWindow::createTimer()
{
    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(frame()));
    timer->start(17);
    connect(button, SIGNAL (released()), this, SLOT (pressButton()));
}

void MainWindow::createRandom()
{
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    srand(reinterpret_cast<unsigned int>(ltm));
}

void MainWindow::frame()
{
    game->frame();
    update();
}

void MainWindow::pressButton()
{
    game->pressButton();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    delete button;
    delete timeLabel;
    delete scoreLabel;
    delete lineEdit;
    delete playList;
    delete mediaPlayer;
}
