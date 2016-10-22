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
    _timer->start(1000);
}

PressureWidget::~PressureWidget()
{
    delete ui;
}

void PressureWidget::setPressure(QString value)
{
    _currentValue = value.toDouble() / 1000;
}

void PressureWidget::onTimerTick()
{
    ui->lcdNumber->display(_currentValue);

    emit pressureChanged(_time, _currentValue);

    _time += (_timer->interval() / 1000);
}
