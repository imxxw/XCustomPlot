#include "Dialog.h"
#include <QVBoxLayout>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    m_customPlot = new XxwCustomPlot();
    m_customPlot->showTracer(true);

    // add title layout element:
    m_customPlot->plotLayout()->insertRow(0);
    m_customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(m_customPlot, "标题", QFont("黑体", 12, QFont::Bold)));

    m_customPlot->legend->setVisible(true);
    QFont legendFont = font();  // start out with MainWindow's font..
    legendFont.setPointSize(9); // and make a bit smaller for legend
    m_customPlot->legend->setFont(legendFont);
    m_customPlot->legend->setBrush(QBrush(QColor(255,255,255,230)));
    // by default, the legend is in the inset layout of the main axis rect. So this is how we access it to change legend placement:
    m_customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignCenter);

    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(m_customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), m_customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(m_customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), m_customPlot->yAxis2, SLOT(setRange(QCPRange)));

    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    m_customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    // generate some data:
    int nCount = 100;
    QVector<double> x(nCount), y0(nCount), y1(nCount); // initialize with entries 0..100
    for (int i = 0; i < nCount; ++i)
    {
        x[i] = i; // x goes from -1 to 1
        y0[i] = qSin(i * 10.0f / nCount); //sin
        y1[i] = qCos(i * 10.0f / nCount); //cos
    }
    // create graph and assign data to it:
    QPen pen;
    int i = 1;
    QCPGraph *pGraph = m_customPlot->addGraph();
    //        m_customPlot->graph(0)->setData(x, y0);
    pGraph->setName("sin曲线");
    pGraph->setData(x,y0);
    pGraph->setPen(QPen(Qt::blue));

    pGraph = m_customPlot->addGraph();
    //        m_customPlot->graph(0)->setData(x, y0);
    pGraph->setName("cos曲线");
    pGraph->setData(x,y1);
    pGraph->setPen(QPen(Qt::darkYellow));

    // give the axes some labels:
    m_customPlot->xAxis->setLabel("x");
    m_customPlot->yAxis->setLabel("y");

    // set axes ranges, so we see all data:
//    m_customPlot->xAxis->setRange(-1, 1);
//    m_customPlot->yAxis->setRange(0, 1);
    m_customPlot->rescaleAxes(true);

    m_customPlot->replot();

    QVBoxLayout *pLayout = new QVBoxLayout;
    pLayout->addWidget(m_customPlot);
    setLayout(pLayout);
    showMaximized();
}

Dialog::~Dialog()
{

}
