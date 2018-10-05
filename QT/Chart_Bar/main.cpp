#include "mainwindow.h"
#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QBarSet *set0 = new QBarSet("Alex");
    QBarSet *set1 = new QBarSet("Bob");
    QBarSet *set2 = new QBarSet("MArs");
    QBarSet *set3 = new QBarSet("Bob");
    QBarSet *set4 = new QBarSet("Trout");

    *set0<<200<<150<<200<<200<<200<<200;
    *set1<<116<<300<<222<<213<<346<<335;
    *set2<<283<<341<<313<<338<<346<<335;
    *set3<<283<<341<<313<<338<<346<<335;
    *set4<<283<<341<<313<<338<<346<<335;

    QBarSeries *series= new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    //series->append(set3);
    //series->append(set4);

    QChart *chart =new QChart();
    chart->addSeries(series);
    chart->setTitle("Year");

    //No AnimationOptions
    chart->setAnimationOptions(QChart::AllAnimations);
    QStringList categories;
    categories << "2013" <<"2014" <<"2015"<<"2016"<<"2016"<< "2017"<<"2018" ;

    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis, series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    QChartView  *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    QPalette pal= qApp->palette();
    pal.setColor(QPalette::Window, QRgb(0xffffff));
    pal.setColor(QPalette::WindowText, QRgb(0x404040));
    qApp->setPalette(pal);


    QMainWindow window;


    window.setCentralWidget(chartView);
    window.resize(420, 300);
    window.show();
    return a.exec();
}
