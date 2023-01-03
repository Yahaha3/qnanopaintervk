#ifndef VKWIDGET_H
#define VKWIDGET_H

#include "QNanoWidgetVk.h"
#include "qnanopainter.h"
#include "painthelper.h"
#include "QTimer"
#include <QLabel>
#include <QWidget>

class VkWidget : public QNanoWidgetVk
{
    Q_OBJECT
public:
    VkWidget(VulkanWindow* window): QNanoWidgetVk(window)
    {
//        setFillColor("#ffffff");
        timer = new QTimer();
        connect(timer, &QTimer::timeout, this, &VkWidget::timeout);
        timer->start(20);
        QLabel* label = new QLabel("Nano", this);
        label->move(50, 50);
    }

    void paint(QNanoPainter *p)
    {
        // Painting code is shared as it's identical in all hello* examples
//        for(int i = 1; i < 2; i++)
        {
//            paintHelloItem(p, width(), height(), t, QNanoFont());
        }
        for(int i = 0; i < 1; i++){
            drawGraphCircles(p, i, 0, width(), height(), 20, t);
//            drawGraphLine(p,    i, 0, width(), height(), 25, t);
//            drawGraphBars(p,    i, 0, width(), height(), 30, t);
//            drawRuler(p, i, 0, width(), height(), t);
//            drawFlower(p, i, 0, width(), height(), t);
        }
    }

private slots:
    void timeout()
    {
        t += 0.03;
//        update();
    }

private:
    QTimer* timer;
    float t = 0;
};

#endif // VKWIDGET_H
