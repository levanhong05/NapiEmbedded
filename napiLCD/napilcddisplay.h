#ifndef NAPILCDDISPLAY_H
#define NAPILCDDISPLAY_H

#include <QHash>
#include <QTimer>
#include <QThread>
#include <QMainWindow>

#include "distancewidget.h"
#include "alignmentwidget.h"
#include "pressurewidget.h"
#include "chartwidget.h"

#include "udplistener.h"
#include "splashscreen.h"

#include "tcpserver.h"
#include "tcpclient.h"
#include "androidsender.h"

#include <QButtonGroup>
#include <QCloseEvent>

namespace Ui {
class NapiLCDDisplay;
}

class NapiWidget : public QObject {
    Q_OBJECT
public :
    NapiWidget(QWidget *parent = 0) {
        _distanceWidget = new DistanceWidget(parent);
        _alignmentWidget = new AlignmentWidget(parent);
        _pressureWidget = new PressureWidget(parent);
        _chartWidget = new ChartWidget(parent);

        connect(_pressureWidget, SIGNAL(pressureChanged(double,double)), _chartWidget, SLOT(onPressureChanged(double,double)));
    }

    DistanceWidget *getDistance() {
        return _distanceWidget;
    }

    AlignmentWidget *getAlignment() {
        return _alignmentWidget;
    }

    PressureWidget *getPressure() {
        return _pressureWidget;
    }

    ChartWidget *getChart() {
        return _chartWidget;
    }

private:
    DistanceWidget      *_distanceWidget;
    AlignmentWidget     *_alignmentWidget;
    PressureWidget      *_pressureWidget;
    ChartWidget         *_chartWidget;
};

class NapiLCDDisplay : public QMainWindow
{
    Q_OBJECT
public:
    explicit NapiLCDDisplay(QWidget *parent = 0);
    ~NapiLCDDisplay();

public slots:
    void setupUI(QString chipID, QString widgetID, QString key, QString value);

    void onButtonClicked(int id);

public slots:
    void onUpdateTime();

private slots:
    void on_btnClose_clicked();

private:
    void removeLayout(QLayout *layout);

    void closeEvent(QCloseEvent *event);

private:
    Ui::NapiLCDDisplay *ui;

    QHash<QString, NapiWidget *> widgets;

    QButtonGroup* buttonGroup;

    SplashScreen *_splash;

    QTimer *timerTime;

};

#endif // NAPILCDDISPLAY_H
