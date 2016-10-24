#include "napilcddisplay.h"
#include "ui_napilcddisplay.h"

#include "keywords.h"
#include "tcpserver.h"
#include "tcpclient.h"
#include "androidsender.h"

#include <QFileInfo>
#include <QTime>
#include <QToolButton>

NapiLCDDisplay::NapiLCDDisplay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NapiLCDDisplay)
{
    ui->setupUi(this);

    TCPClient *client = new TCPClient();

    timerClient = new QTimer();
    connect(timerClient, SIGNAL(timeout()), client, SLOT(tryConnect()));
    timerClient->start(3000);

    onUpdateTime();

    timerTime = new QTimer();
    connect(timerTime, SIGNAL(timeout()), this, SLOT(onUpdateTime()));
    timerTime->start(60000);

    _networkValidator = new NetworkThread();

    timerNetwork = new QTimer();
    connect(timerNetwork, SIGNAL(timeout()), _networkValidator, SLOT(checkServices()));
    timerNetwork->start(10000);

    _networkValidator->start();

    buttonGroup = new QButtonGroup();

    _splash = new SplashScreen(this);
    _splash->show();
    _splash->activateWindow();

    connect(buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(onButtonClicked(int)));

    buttonGroup->setExclusive(true);

    connect(&Server::Instance(), SIGNAL(requestSetupUI(QString, QString, QString, QString)),
            this, SLOT(setupUI(QString, QString, QString, QString)));

    connect(&Server::Instance(), SIGNAL(dataChanged(QString)), &Android::Instance(), SLOT(onDataChanged(QString)));

    Qt::WindowFlags flags = 0;
    flags = Qt::Window;
    flags |= Qt::FramelessWindowHint;
    flags |= Qt::X11BypassWindowManagerHint;
    setWindowFlags(flags);
}

NapiLCDDisplay::~NapiLCDDisplay()
{
    delete ui;
}

void NapiLCDDisplay::closeEvent(QCloseEvent *event)
{
    event->ignore();
}

void NapiLCDDisplay::setupUI(QString chipID, QString widgetID, QString key, QString value)
{
    Q_UNUSED(chipID);

    if (_splash) {
        _splash->close();
        _splash = NULL;
    }

    //Setup button if it not exist
    if (!widgets.contains(widgetID)) {
        QFont font;
        font.setPointSize(20);
        QToolButton *button = new QToolButton();
        button->setText(tr("Banche %1").arg(widgetID));
        button->setMinimumSize(35, 50);
        button->setFont(font);
        button->setCheckable(true);
        button->setAutoRaise(true);

        buttonGroup->addButton(button, widgetID.toInt());
        ui->layoutButton->addWidget(button);

        NapiWidget *widget = new NapiWidget(this);

        widgets.insert(widgetID, widget);
    }

    //Set data
    NapiWidget *widget = widgets[widgetID];

    if (key == H_DISTANCE) {
        widget->getDistance()->setHorizotalDistance(value);
    } else if (key == V_DISTANCE) {
        widget->getDistance()->setVerticalDistance(value);
    } else if (key == H_ALIGNMENT) {
        widget->getAlignment()->setHorizotalAlignment(value);
    } else if (key == V_ALIGNMENT) {
        widget->getAlignment()->setVerticalAlignment(value);
    } else if (key == PRESSURE) {
        widget->getPressure()->setPressure(value);
    }

    buttonGroup->button(widgetID.toInt())->setChecked(true);

    buttonGroup->button(widgetID.toInt())->click();
}

void NapiLCDDisplay::onButtonClicked(int id)
{
    removeLayout(ui->layoutDistance);
    removeLayout(ui->layoutAlignment);
    removeLayout(ui->layoutPressure);
    removeLayout(ui->layoutChart);

    ui->layoutDistance->addWidget(widgets[QString::number(id)]->getDistance());
    ui->layoutAlignment->addWidget(widgets[QString::number(id)]->getAlignment());
    ui->layoutPressure->addWidget(widgets[QString::number(id)]->getPressure());
    ui->layoutChart->addWidget(widgets[QString::number(id)]->getChart());

    widgets[QString::number(id)]->getDistance()->show();
    widgets[QString::number(id)]->getAlignment()->show();
    widgets[QString::number(id)]->getPressure()->show();
    widgets[QString::number(id)]->getChart()->show();

    ui->frmWidget->update();
}

void NapiLCDDisplay::onUpdateTime()
{
    QString time = QTime::currentTime().toString("HH:mm");

    ui->lblTime->setText(time);
}

void NapiLCDDisplay::removeLayout(QLayout *layout)
{
    if (layout != 0) {
        QLayoutItem *item;

        while ((item = layout->takeAt(0)) != 0) {
            item->widget()->hide();
            layout->removeItem(item);
        }
    }
}

void NapiLCDDisplay::on_btnClose_clicked()
{
#ifdef Q_OS_WIN
    system("shutdown -r");
#else
    system("sudo reboot");
#endif
}
