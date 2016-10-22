#ifndef DISTANCEWIDGET_H
#define DISTANCEWIDGET_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class DistanceWidget;
}

class DistanceWidget : public QDialog
{
    Q_OBJECT
public:
    explicit DistanceWidget(QWidget *parent = 0);
    ~DistanceWidget();

public slots:
    void setHorizotalDistance(QString value);

    void setVerticalDistance(QString value);

private:
    Ui::DistanceWidget *ui;
};

#endif // DISTANCEWIDGET_H
