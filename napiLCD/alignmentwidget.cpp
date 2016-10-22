#include "alignmentwidget.h"
#include "ui_alignmentwidget.h"

AlignmentWidget::AlignmentWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AlignmentWidget)
{
    ui->setupUi(this);
}

AlignmentWidget::~AlignmentWidget()
{
    delete ui;
}

void AlignmentWidget::setHorizotalAlignment(QString value)
{
    double dValue = value.toDouble();

    if (qAbs(dValue) <= 0.5) {
        ui->lblHCheck->setPixmap(QPixmap(":/napilcd/images/checked.png"));
    } else {
        ui->lblHCheck->setPixmap(QPixmap(":/napilcd/images/unchecked.png"));
    }

    ui->lcdHNumber->display(value);
}

void AlignmentWidget::setVerticalAlignment(QString value)
{
    double dValue = value.toDouble();

    if (qAbs(dValue) <= 0.5) {
        ui->lblVCheck->setPixmap(QPixmap(":/napilcd/images/checked.png"));
    } else {
        ui->lblVCheck->setPixmap(QPixmap(":/napilcd/images/unchecked.png"));
    }

    ui->lcdVNumber->display(value);
}
