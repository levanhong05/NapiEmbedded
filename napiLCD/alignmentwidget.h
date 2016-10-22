#ifndef ALIGNMENTWIDGET_H
#define ALIGNMENTWIDGET_H

#include <QWidget>
#include <QDialog>

namespace Ui {
class AlignmentWidget;
}

class AlignmentWidget : public QDialog
{
    Q_OBJECT
public:
    explicit AlignmentWidget(QWidget *parent = 0);
    ~AlignmentWidget();

public slots:
    void setHorizotalAlignment(QString value);

    void setVerticalAlignment(QString value);

private:
    Ui::AlignmentWidget *ui;
};

#endif // ALIGNMENTWIDGET_H
