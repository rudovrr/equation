#include "widget.hpp"
Widget::Widget(QWidget *parent)
 : QWidget(parent) 
{
    labelEquation = new QLabel("x^3 + A*x^2 + B*x + C = 0");
    labelA = new QLabel("A:");
    inputA = new QLineEdit;
    labelB = new QLabel("B:");
    inputB = new QLineEdit;
    labelC = new QLabel("C:");
    inputC = new QLineEdit;
    labelLeftBorder = new QLabel("X от:");
    inputLeftBorder = new QLineEdit;
    labelRightBorder = new QLabel("до:");
    inputRightBorder = new QLineEdit;
    buttonChart = new QPushButton("Построить график");
    buttonFindSolution = new QPushButton("Найти решение");
    labelX1 = new QLabel("");
    labelX2 = new QLabel("");
    labelX3 = new QLabel("");
    series = new QLineSeries;
    chart = new QChart;
    chart->legend()->hide();
    chart->createDefaultAxes();
    formLayout = new QFormLayout();
    formLayout->addRow(labelEquation);
    formLayout->addRow(labelA, inputA);
    formLayout->addRow(labelB, inputB);
    formLayout->addRow(labelC, inputC);
    formLayout->addRow(labelLeftBorder, inputLeftBorder);
    formLayout->addRow(labelRightBorder, inputRightBorder);
    formLayout->addRow(buttonChart);
    formLayout->addRow(buttonFindSolution);
    formLayout->addRow(labelX1);
    formLayout->addRow(labelX2);
    formLayout->addRow(labelX1);
    formLayout->addRow(labelX2);
    formLayout->setLabelAlignment(Qt::AlignRight);
    chartView = new QChartView(chart);

    formLayout->addWidget(chartView);
    formLayout->setVerticalSpacing(7);
    setLayout(formLayout);
    setFixedWidth(600);
    setFixedHeight(800);

    connect(buttonChart, &QPushButton::clicked, this,  &Widget::onButtonChartClick);
    connect(buttonFindSolution, &QPushButton::clicked, this, &Widget::onButtonFindSolutionClick);
}
void Widget::onButtonChartClick()
{
    unordered_map<string, float> umap = getData();
    vector<float> x = linspace(umap["leftBorder"], umap["rightBorder"], 1000);

    QLineSeries *series = new QLineSeries();

    for (float x_item : x) {
        float y_item = y(umap["a"], umap["b"], umap["c"], x_item);
        series->append(x_item, y_item);
    }

    chart = new QChart;
    chart->addSeries(series);
    chart->legend()->hide();
    chart->createDefaultAxes();
    chartView->setChart(chart);
    
}

void Widget::onButtonFindSolutionClick()
{
    unordered_map<string, float> umap = getData();

    float a = umap["a"];
    float b = umap["b"];
    float c = umap["c"];
    float leftBorder = umap["leftBorder"];
    float rightBorder = umap["rightBorder"];

    float localLeft = leftBorder;
    float localRight = rightBorder;
    float x1;
    while(true) 
    {
        float x = (localLeft + localRight) / 2.;
        float y_item = y(a, b, c, x);
        if(( y(a, b, c, x) > -0.000001) && ( y(a, b, c, x) < 0.000001))
        {
            x1 = x;
            break;
        } 
        else if ((y(a, b, c, x) > 0) && (y(a, b, c, localLeft) > 0.))
        {
            localLeft = x;
        } 
        else if ((y(a, b, c, x) > 0.) && (y(a, b, c, localRight) > 0.))
        {
            localRight = x;
        }
        else if ((y(a, b, c, x) < 0.) && (y(a, b, c, localLeft) < 0.))
        {
            localLeft = x;
        }
        else if ((y(a, b, c, x) < 0.) && (y(a, b, c, localRight) < 0.))
        {
            localRight = x;
        }
    }

    labelX1->setText(QString::fromStdString("X1=" + to_string(x1)));

    vector<float> r = getSolutionQuadEquation(1., a+x1, (b+(a+x1)*x1));

    if (1 <= r.size())
    {
        labelX2->setText(QString::fromStdString("X2=" + to_string(r[0])));
    }

    if (2 == r.size())
    {
        labelX2->setText(QString::fromStdString("X3=" + to_string(r[1])));
    }
    
}

vector<float> Widget::getSolutionQuadEquation(float a, float b, float c)
{
    vector<float> r;

    if (!((a > - 0.000000001 )&&(a < 0.000000001)))
    {
        float discreminant = pow(b, 2) - 4*a*c;
        if ((discreminant > - 0.000000001)&&(discreminant < 0.000000001))
        {
            r.push_back(- b / (2*a));
            r.push_back(- b / (2*a));
        } else if (discreminant > 0)
        {
            r.push_back((- b + sqrt(discreminant))/(2*a));
            r.push_back((- b - sqrt(discreminant))/(2*a));
        }

    } else
    {
        r.push_back(-c/b);
    }

    return r;
        
}


unordered_map<string, float> Widget::getData()
{
    unordered_map<string, float> umap;
    umap["a"] = inputA->text().toFloat();
    umap["b"] = inputB->text().toFloat();
    umap["c"] = inputC->text().toFloat();
    umap["leftBorder"] = inputLeftBorder->text().toFloat();
    umap["rightBorder"] = inputRightBorder->text().toFloat();
    return umap;
}
vector<float> Widget::linspace(float start, float end, int count)
{
    vector<float> r;
    r.reserve(count);
    float step = (end - start) / (count-1);
    for (int i = 0; i < count ; i++) {
        r.push_back(start + i * step);
    }
    return r;
}
float Widget::y(float a, float b, float c, float x)
{
    return pow(x, 3) + a*pow(x, 2) + b*x + c;
}
Widget::~Widget()
{
} 