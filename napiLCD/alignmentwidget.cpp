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
    ui->lcdHNumber->display(value);
}

void AlignmentWidget::setVerticalAlignment(QString value)
{
    ui->lcdVNumber->display(value);
}
