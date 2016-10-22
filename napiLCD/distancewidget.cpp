#include "distancewidget.h"
#include "ui_distancewidget.h"

DistanceWidget::DistanceWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DistanceWidget)
{
    ui->setupUi(this);
}

DistanceWidget::~DistanceWidget()
{
    delete ui;
}

void DistanceWidget::setHorizotalDistance(QString value)
{
    ui->lcdHNumber->display(value);
}

void DistanceWidget::setVerticalDistance(QString value)
{
    ui->lcdVNumber->display(value);
}
