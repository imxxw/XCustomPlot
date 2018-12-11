#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "XxwCustomPlot.h"

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

protected:
    XxwCustomPlot *m_customPlot;
};

#endif // DIALOG_H
