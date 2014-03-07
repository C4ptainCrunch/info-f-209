#include "matchwidget.h"

MatchWidget::MatchWidget(QWidget * parent):
    QWidget(parent) {

    //-------------------------SIZE SETTINGS---------------------------
    this->setFixedHeight(720);
    this->setFixedWidth(1280);

    //----------------------BACKGROUND SETTINGS---------------------------
    QVBoxLayout * layout = new QVBoxLayout;
    QLabel * image = new QLabel(this);
    image->setPixmap(QPixmap(QCoreApplication::applicationDirPath() + "/images/Quidditch_pitch_hogwarts.jpg"));
    layout->addWidget(image);
    //this->setLayout(layout);


    //---------------------MAIN CONTAINER WIDGET---------------------------
    QWidget * mainWidget = new QWidget(this);
    mainWidget->setFixedHeight(720);
    mainWidget->setFixedWidth(1280);
    QGridLayout * mainLayout = new QGridLayout(mainWidget);

    //------------------------SCORE SETTINGS--------------------------------
    QLabel * title = new QLabel("VOUS : 0", mainWidget);
    title->setFixedSize(200, 75);
    QFont font;
    font.setPointSize(17);
    title->setStyleSheet(" font-weight: bold; font-size: 18pt; color : red;");
    title->setAlignment(Qt::AlignBottom | Qt::AlignJustify);
    title->setWordWrap(true);
    title->setFont(font);
    title->move(100, 50);
    title->show();

    QLabel * title2 = new QLabel("ADVERSAIRE : 0", mainWidget);
    title2->setFixedSize(200, 75);
    title2->setAlignment(Qt::AlignBottom | Qt::AlignJustify);
    title2->setStyleSheet(" font-weight: bold; font-size: 18pt; color : red;");
    title2->setWordWrap(true);
    title2->setFont(font);
    title2->move(1000, 50);
    title2->show();

    //---------------------FIELD CONTAINER WIDGET--------------------------
    fieldWidget  = new QFrame(mainWidget);
    //fieldWidget->setLineWidth(2);
    //fieldWidget->setFrameStyle(QFrame::Box);
    /*
       QPalette* palette = new QPalette();
       palette->setBrush(QPalette::Foreground,QBrush(QImage("images/wood.jpg")));
       palette->setColor(QPalette::Background,Qt::white);
       fieldWidget->setPalette(*palette);
       fieldWidget->setAutoFillBackground( true );
     */

    //---------------------FIELD REPRESENTATION----------------------------

    fieldWidget->setFixedSize(QSize(1100, 450));
    fieldWidget->move(mainWidget->width() / 2 - fieldWidget->width() / 2, mainWidget->height() / 2 - fieldWidget->height() / 2);
    QLabel * label = new QLabel(fieldWidget);
    QPixmap * pixmap = new QPixmap(1100, 450);
    pixmap->fill(Qt::transparent);

    QPainter painter(pixmap);
    painter.setBrush(QBrush(Qt::darkGreen));
    Hexagon hexagon[WIDTH][LENGHT];
    QBrush * grass = new QBrush(QImage("images/grass.jpg"));

    double x = 0;
    double y = 0;
    int delta = 1 / 2;
    bool pair = true;
    for (int i = 0; i < WIDTH; ++i) {
        for (int j = 0; j < LENGHT; ++j) {
            hexagon[i][j].setX(x);
            hexagon[i][j].setY(y);
            hexagon[i][j].setCorners();
            //hexagon[i][j].setStylesheet("background-image : url(images/grass2.jpg)");

            x += 18;

            double diameterFactor = 46.0 / 100.0;

            double result = pow(i - WIDTH / 2.0, 2) / pow(diameterFactor * WIDTH, 2);
            result += pow(j - LENGHT / 2.0, 2) / pow(diameterFactor * LENGHT, 2);
            if (i % 2 != 0) {
                result -= delta;
            }
            if (result < 1) {
                if (i <= LENGHT / 2 and j == LENGHT / 2) {
                    painter.setBrush(QBrush(Qt::white));
                }
                else {
                    painter.setBrush(*grass);
                }
                painter.drawPolygon(hexagon[i][j].hexagon_);
            }
        }
        y += 15;
        if (pair) {
            x = 35;
        }
        else {
            x = 26;
        }
        pair = !pair;
    }

    label->setPixmap(*pixmap);


    //mainLayout->addWidget(fieldWidget,1,1);
    mainWidget->setLayout(mainLayout);
    //fieldWidget->move(200,200);
    mainWidget->show();


}

MatchWidget::~MatchWidget() {}
