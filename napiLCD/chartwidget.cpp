#include "chartwidget.h"
#include "ui_chartwidget.h"

ChartWidget::ChartWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChartWidget)
{
    ui->setupUi(this);

    plot = new QwtPlot();
    plot->setTitle(tr("Graphe de pression"));

    // Customize axis label font
    QFont font;
    font.setFamily("Fixedsys");
    font.setPixelSize(20);

    plot->setAutoFillBackground(true);
    palette = plot->palette();
    palette.setColor(QPalette::Background, QColor(255,255,255));
    plot->setPalette(palette);
    canvas = new QwtPlotCanvas();

    canvas->setStyleSheet(
        "border: 1px inset white;"
        "border-radius: 5px;"
        "background: white;"
    );

    plot->setCanvas(canvas);
    plot->plotLayout()->setAlignCanvasToScales(true);

    plot->setAxisScaleEngine(QwtPlot::yLeft, new QwtLinearScaleEngine(100));

    // Customize axis label font
    QFont labelsFont;
    labelsFont.setFamily("Fixedsys");
    labelsFont.setPointSize(15);

    plot->setAxisFont(QwtPlot::xBottom, labelsFont);
    plot->setAxisFont(QwtPlot::yLeft, labelsFont);
    plot->setAxisTitle(QwtPlot::xBottom, tr("Temps"));

    sPressure.setDefaultMaxMin();
    avgPressure.setDefault();

    setupPressure();

    //Gird
    grid = new QwtPlotGrid();
    grid->enableY(true);
    grid->enableYMin(true);
    grid->setMajorPen(Qt::darkGray, 1.0, Qt::DotLine);
    grid->setMinorPen(Qt::gray, 0.5 , Qt::DotLine);
    grid->attach(plot);

    //zoomer
    this->m_zoomer = new QwtPlotZoomer(QwtPlot::xBottom, QwtPlot::xTop, this->plot->canvas());
    this->m_zoomer->setRubberBandPen(QPen(Qt::red, 2, Qt::DotLine));
    this->m_zoomer->setTrackerPen(QPen(Qt::red));
    this->m_zoomer->setMousePattern(QwtEventPattern::MouseSelect2, Qt::NoButton);
    this->m_zoomer->setMousePattern(QwtEventPattern::MouseSelect3, Qt::NoButton);
    this->m_zoomer->zoom(0);
    this->m_zoomer->setEnabled(false);

    plot->setAutoReplot(false);
    ui->verticalLayout->addWidget(this->plot);

    this->plot->show();

    _minValue = 0;
    _maxTime = _maxValue = 10;
}

ChartWidget::~ChartWidget()
{
    delete ui;
}

void ChartWidget::onPressureChanged(double time, double value)
{
    if (time > _maxTime) {
        _maxTime = time + 10;
    }

    if (value > _maxValue) {
        _maxValue = value + 5;
    } else if (value < _minValue) {
        _minValue = value - 5;
    }

    avgPressure.countValues ++;

    if (avgPressure.countValues == 1) {
        sPressure.insertValues(value);
    }

    plot->setAxisScale(QwtPlot::xBottom, 0.0, _maxTime);
    plot->setAxisScale(QwtPlot::yLeft, _minValue, _maxValue);

    iTime.push_back(time);

    drawPressure();

    plot->replot();

    avgPressure.setDefault();
}

void ChartWidget::drawPressure()
{
    if (sPressure.x.size() == 0) {
        return;
    }

    curvePressure->setData(new QwtPointArrayData(&iTime[0], &sPressure.x[0], sPressure.x.size()));
    curvePressure->attach(plot);
}

void ChartWidget::setupPressure()
{
    curvePressure = new QwtPlotCurve();
    curvePressure->setPen(QColor(0, 170, 0), 3.0), curvePressure->setRenderHint(QwtPlotItem::RenderAntialiased, true);
    curvePressure->setCurveAttribute(QwtPlotCurve::Fitted, false);
}
