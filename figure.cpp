#include "figure.h"
#include "qdebug.h"

Figure::Figure(int x, int y) : ObjectFigure (x, y)
{
    std::mt19937 generator(static_cast<uint32_t>(time(nullptr)));
    std::uniform_int_distribution<int32_t> randomVector(1, 5);
    vector = static_cast<time_t>(randomVector(generator));
    id = (rand() % 6) + 1;
    switch(id)
    {
    case 1:
        image.load(":/Images/circle.png");
        break;
    case 2:
        image.load(":/Images/hexagon.png");
        break;
    case 3:
        image.load(":/Images/star.png");
        break;
    case 4:
        image.load(":/Images/triangle.png");
        break;
    case 5:
        image.load(":/Images/twelvestar.png");
        break;
    case 6:
        image.load(":/Images/square.png");
        break;
    default:
        break;
    }
}

Figure::Figure(int x, int y, QString image) : ObjectFigure (x, y)
{
    this->image.load(image);
}

void Figure::paintF(QPainter *painter)
{
    paint(x,y,painter,&image);
}

void Figure::paintMap(Figure *cells[8][8], QPainter *painter)
{
    for(int raw = 0; raw < 8; raw++)
        for(int colon = 0; colon < 8; colon++)
            cells[raw][colon]->paintF(painter);
}

void Figure::transformToBonus()
{
    QImage maskAplha = image;
    maskAplha.fill(QColor(0,0,0,255));
    image.setAlphaChannel(maskAplha.alphaChannel());
    id = 7;
    image.load(":/Images/bonus.png");
}

void Figure::setZeroID()
{
    id = 0;
}

void Figure::setAlpha(int alpha)
{
    QImage maskAplha = image;
    maskAplha.fill(QColor(0,0,0,alpha));
    image.setAlphaChannel(maskAplha.alphaChannel());
}

int Figure::getId()
{
    return id;
}
