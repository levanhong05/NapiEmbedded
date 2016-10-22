#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QWidget>
#include <QCloseEvent>

namespace Ui {
class SplashScreen;
}

class SplashScreen : public QWidget
{
    Q_OBJECT
public:
    explicit SplashScreen(QWidget *parent = 0);
    ~SplashScreen();

private:
    void closeEvent(QCloseEvent *event);

private:
    Ui::SplashScreen *ui;

};

#endif // SPLASHSCREEN_H
