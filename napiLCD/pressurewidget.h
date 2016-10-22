#ifndef PRESSUREWIDGET_H
#define PRESSUREWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QDialog>

namespace Ui {
class PressureWidget;
}

class PressureWidget : public QDialog
{
    Q_OBJECT
public:
    explicit PressureWidget(QWidget *parent = 0);
    ~PressureWidget();

public slots:
    void setPressure(QString value);

    void onTimerTick();

signals:
    void pressureChanged(double _time, double value);

private:
    Ui::PressureWidget *ui;

    double _time;

    double _currentValue;

    QTimer *_timer;
};

#endif // PRESSUREWIDGET_H
