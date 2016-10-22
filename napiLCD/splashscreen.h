#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QDialog>
#include <QCloseEvent>

namespace Ui {
class SplashScreen;
}

class SplashScreen : public QDialog
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
