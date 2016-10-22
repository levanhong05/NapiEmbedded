#include "splashscreen.h"
#include "ui_splashscreen.h"

#include <QDesktopWidget>

SplashScreen::SplashScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SplashScreen)
{
    ui->setupUi(this);

    //Move the dialog away from the center
    setGeometry(0, 0, this->width(), this->height());

    int i = 0;

    if (qApp->desktop()->screenCount() > 1) {
        i = qApp->desktop()->screenNumber(this) ;
    }

    //Put the dialog in the screen center
    const QRect screen = qApp->desktop()->screenGeometry(i);
    move(screen.center() - rect().center());

    Qt::WindowFlags flags = 0;
    flags = Qt::Tool;
    flags |= Qt::CustomizeWindowHint;
    flags |= Qt::FramelessWindowHint;
    setWindowFlags(flags);

    setFixedSize(this->size());
}

SplashScreen::~SplashScreen()
{
    delete ui;
}

void SplashScreen::closeEvent(QCloseEvent *event)
{
    event->setAccepted(!event->spontaneous());
}
