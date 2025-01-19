#ifndef WIDGET_H
#define WIDGET_H
#include <QApplication>
#include <QtWidgets>
#include <QLabel>
#include <QPushButton>
#include <QLineSeries>
#include <QChart>
#include <QChartView>
#include <cmath>
using namespace std;
class Widget : public QWidget
{
 Q_OBJECT
public:
    Widget(QWidget *parent=nullptr);
    ~Widget();
    unordered_map<string, float> getData();
    vector<float> linspace(float start, float end, int count);
    float y(float a, float b, float c, float x);
    vector<float> getSolutionQuadEquation(float a, float b, float c);
private:
    QLabel *labelEquation;
    QLabel *labelA;
    QLineEdit *inputA;
    QLabel *labelB;
    QLineEdit *inputB;
    QLabel *labelC;
    QLineEdit *inputC;
    QLabel *labelLeftBorder;
    QLineEdit *inputLeftBorder;
    QLabel *labelRightBorder;
    QLineEdit *inputRightBorder;
    QPushButton *buttonChart;
    QPushButton *buttonFindSolution;
    QLabel *labelX1;
    QLabel *labelX2;
    QLabel *labelX3;
    QLineSeries* series;
    QChart* chart; 
    QFormLayout *formLayout;
    QChartView* chartView;
private slots:
    void onButtonChartClick();
    void onButtonFindSolutionClick();
};
#endif // WIDGET_H 