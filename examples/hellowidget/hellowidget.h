/**********************************************************
** Copyright (c) 2018 QUIt Coding <info@quitcoding.com>
**
** This software is provided 'as-is', without any express or implied
** warranty.  In no event will the authors be held liable for any damages
** arising from the use of this software.
**
** Permission is granted to anyone to use this software for any purpose,
** including commercial applications, and to alter it and redistribute it
** freely, subject to the following restrictions:
**
** 1. The origin of this software must not be misrepresented; you must not
**    claim that you wrote the original software. If you use this software
**    in a product, an acknowledgment in the product documentation would be
**    appreciated but is not required.
** 2. Altered source versions must be plainly marked as such, and must not be
**    misrepresented as being the original software.
** 3. This notice may not be removed or altered from any source distribution.
**
**********************************************************/

#ifndef HELLOWIDGET_H
#define HELLOWIDGET_H

#include "qnanowidget.h"
#include "qnanopainter.h"
#include "painthelper.h"
#include "QTimer"

class HelloWidget : public QNanoWidget
{
    Q_OBJECT
public:
    HelloWidget()
    {
        setFillColor("#ffffff");
        timer = new QTimer();
        connect(timer, &QTimer::timeout, this, &HelloWidget::timeout);
        timer->start(20);
    }

    void paint(QNanoPainter *p)
    {
        // Painting code is shared as it's identical in all hello* examples
//        QPainter painter(this);
        for(int i = 1; i < 2; i++){
//            paintHelloItem(p, width(), height(), t, QNanoFont());
            paintHelloItem(p, width(), height() / i, t, QNanoFont());

//        paintIcon(&painter, width(), height() / i, t, QFont());
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

#endif // HELLOWIDGET_H
