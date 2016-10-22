#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QWidget>
#include <QDialog>

#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
#include <qwt_point_data.h>
#include <qwt_curve_fitter.h>
#include <qwt_spline.h>

#include <qwt_scale_engine.h>
#include <qwt_scale_div.h>

#include <qwt_plot_layout.h>
#include <qwt_plot_zoomer.h>

#include <qwt_plot_canvas.h>
#include <qwt_plot_magnifier.h>
#include <qwt_picker_machine.h>
#include <qwt_plot_zoomer.h>

namespace Ui {
class ChartWidget;
}

class ChartWidget : public QDialog
{
    Q_OBJECT
public:
    explicit ChartWidget(QWidget *parent = 0);
    ~ChartWidget();

protected:
    typedef struct {
        std::vector<double> x;
        double max;
        double min;
        void setDefaultValues()
        {
            x.clear();
        }

        void setDefaultMaxMin()
        {
            max = 1e-15;
            min = 1e+15;
        }
        void insertValues(double _x)
        {
            x.push_back(_x);

            //min
            if (_x < min) {
                min = _x;
            }

            //max
            if (_x > max) {
                max = _x;
            }
        }
        void updateValues(double _x)
        {
            x.pop_back();
            x.push_back(_x);

            //min
            if (_x < min) {
                min = _x;
            }

            //max
            if (_x > max) {
                max = _x;
            }
        }
    } sValues;

    typedef struct {
        int countValues;
        double sumValues;
        void setDefault()
        {
            countValues = 0;
            sumValues = 0.0;
        }
    } avgInfo;

public slots:
    void onPressureChanged(double time, double value);

private:
    void setupPressure();
    void drawPressure();

private:
    Ui::ChartWidget *ui;

    QwtPlotGrid *grid;

    QwtPlot *plot;

    QwtPlotZoomer *m_zoomer;

    QwtPlotCanvas *canvas;
    QPalette palette;

    QwtPlotCurve *curvePressure;

    sValues sPressure;
    avgInfo avgPressure;

    std::vector<double> iTime;

    double _maxTime;
    double _maxValue;
    double _minValue;
};

#endif // CHARTWIDGET_H
