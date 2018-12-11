#ifndef MYTRACER_H
#define MYTRACER_H

#include <QObject>
#include "qcustomplot.h"

///
/// \brief The XxwTracer class:在图表中显示鼠标所在位置的x,y值的追踪显示器
///
class XxwTracer : public QObject
{
	Q_OBJECT

public:
	enum TracerType
	{
        XAxisTracer,//依附在x轴上显示x值
        YAxisTracer,//依附在y轴上显示y值
        DataTracer//在图中显示x,y值
	};
    explicit XxwTracer(QCustomPlot *_plot, TracerType _type, QObject *parent = Q_NULLPTR);
    ~XxwTracer();
	void setPen(const QPen &pen);
	void setBrush(const QBrush &brush);
	void setText(const QString &text);
	void setLabelPen(const QPen &pen);
	void updatePosition(double xValue, double yValue);
    void setVisible(bool m_visible);

protected:
    bool m_visible;//是否可见
    TracerType m_type;//类型
    QCustomPlot *m_plot;//图表
    QCPItemTracer *m_tracer;//跟踪的点
    QCPItemText *m_label;//显示的数值
    QCPItemLine *m_arrow;//箭头
};


///
/// \brief The XxwCrossLine class:用于显示鼠标移动过程中的鼠标位置的直线
///
class XxwTraceLine : public QObject
{
public:
    enum LineType
    {
        VerticalLine,//垂直线
        HorizonLine, //水平线
        Both//同时显示水平和垂直线
    };
    explicit XxwTraceLine(QCustomPlot *_plot, LineType _type = VerticalLine, QObject *parent = Q_NULLPTR);
    ~XxwTraceLine();
    void initLine();
    void updatePosition(double xValue, double yValue);

    void setVisible(bool vis)
    {
        if(m_lineV)
            m_lineV->setVisible(vis);
        if(m_lineH)
            m_lineH->setVisible(vis);
    }

protected:
    bool m_visible;//是否可见
    LineType m_type;//类型
    QCustomPlot *m_plot;//图表
    QCPItemStraightLine *m_lineV; //垂直线
    QCPItemStraightLine *m_lineH; //水平线
};

#endif // MYTRACER_H
