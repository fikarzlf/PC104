#include "mainwindow.h"
#include <QApplication>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>


QT_CHARTS_USE_NAMESPACE

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

          QLineSeries *Line1 = new QLineSeries();

          for (int i = 0; i < 100; i++)    //
          {
              int x, y;
              x=i;
              y=i*i;
              Line1->append(x,y);
          }

          //Line1->append(0, 0);
          //Line1->append(1, 1);
          //Line1->append(2, 2);
          //Line1->append(7, 4);
          //Line1->append(10, 5);
          //*Line1 << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

          QChart *chart = new QChart();
          chart->legend()->hide();
          chart->addSeries(Line1);
          chart->createDefaultAxes();
          chart->setTitle("Simple line chart example");

          QChartView *chartView = new QChartView(chart);
          chartView->setRenderHint(QPainter::Antialiasing);

          QMainWindow window;
          window.setCentralWidget(chartView);
          window.resize(400, 300);
          window.show();

          return a.exec();

}
