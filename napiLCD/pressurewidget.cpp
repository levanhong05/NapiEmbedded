#include "pressurewidget.h"
#include "ui_pressurewidget.h"

#include <QTime>

PressureWidget::PressureWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PressureWidget)
{
    ui->setupUi(this);
    _time = 0;
    _currentValue = 0;

    _timer = new QTimer();
    connect(_timer, SIGNAL(timeout()), this, SLOT(onTimerTick()));
    _timer->start(2000);
}

PressureWidget::~PressureWidget()
{
    delete ui;
}

void PressureWidget::setPressure(QString value)
{
    ui->lcdNumber->display(value);

    _currentValue = value.toDouble();

    emit pressureChanged(_time, _currentValue);

    _time++;

}

void PressureWidget::onTimerTick()
{
    _time += (_timer->interval() / 1000);
}
