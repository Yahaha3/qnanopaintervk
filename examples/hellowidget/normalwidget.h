#ifndef NORMALWIDGET_H
#define NORMALWIDGET_H

#include "qnanowidget.h"
#include "qnanopainter.h"
#include "painthelper.h"
#include "QTimer"

class NormalWidget : public QWidget
{
    Q_OBJECT
public:
    NormalWidget()
    {
        timer = new QTimer();
        connect(timer, &QTimer::timeout, this, &NormalWidget::timeout);
        timer->start(20);
    }

    void paintEvent(QPaintEvent *event)
    {
        QPainter painter(this);
        for(int i = 1; i < 300; i++){
//            paintHelloItem(p, width(), height(), t, QNanoFont());
//            paintHelloItem(p, width(), height() / i, t, QNanoFont());

        paintIcon(&painter, width(), height() / i, t, QFont());
        }
    }

private slots:
    void timeout()
    {
        t += 0.03;
        update();
    }

private:
    QTimer* timer;
    float t = 0;
};
#endif // NORMALWIDGET_H
