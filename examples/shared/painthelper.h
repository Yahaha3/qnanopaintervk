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

#ifndef PAINTHELPER_H
#define PAINTHELPER_H

#include <algorithm>
#include <QCoreApplication>
#include "qnanopainter.h"
#include "QPainter"
#include "QFont"

#define M_PI 3.141592657

static void paintHelloItem(QNanoPainter *m_painter, float w, float h,float t, QNanoFont m_testFont)
{

    QNanoImage::ImageFlags imageFlags = {};
    QString path = QCoreApplication::applicationDirPath() + "/image.png";
    QNanoImage circleImage = QNanoImage(path, imageFlags);
    m_painter->drawImage(circleImage, QRectF(0, 0, w, h));

//    m_painter->setTextAlign(QNanoPainter::ALIGN_CENTER);
//    m_painter->setTextBaseline(QNanoPainter::BASELINE_MIDDLE);
//    // Note: Adjust font size to match QPainter sizing
//    float fontSize = (10.0f + w*0.01f) * 1.32f;
//    m_testFont.setPixelSize(fontSize);
//    m_painter->setFont(m_testFont);
//    m_painter->setStrokeStyle("#000000");
//    m_painter->setFillStyle("#0000EE");
//    m_painter->beginPath();
//    m_painter->setLineWidth(3.0f);
//    m_painter->moveTo(QPointF(100, 100));
//    m_painter->arc(QPointF(100, 100), 100, 0, 1.57);
//    m_painter->lineTo(QPointF(100, 100));
//    m_painter->stroke();
}

static void paintIcon(QPainter *m_painter, float w, float h,float t, QFont m_testFont){

//    auto x = 0.0;
//    float y = h * 0.02f;
//    h = h * 0.05f;
//    float posX = x + w*0.05f;
//    double space = w*0.03f + sinf(t)*w*0.02f;
//    float fontSize = 10.0f + w*0.01f;
//    m_testFont.setPixelSize(fontSize);
//    m_painter->setFont(m_testFont);
//    m_painter->setPen("#000000");
//    m_painter->setBrush(Qt::NoBrush);

//    QPainterPath myPath;

//    auto radius = 50;
//    auto outline = 10;
//    QPoint center(100, 100);
//    myPath.addEllipse(center, radius + outline, radius + outline);
//    myPath.addEllipse(center, radius, radius);
//    myPath.addEllipse(center, radius - outline, radius - outline);
//    m_painter->drawPath(myPath);
//    int i = 0;
//    QVector<QPointF> pointPairs;
//    while (posX < w) {
//        pointPairs.append(QPointF(posX, y));
//        float height = h*0.2f;
//        float ts = w*0.05f;
//        QRectF textRect(posX-ts, y+h-ts, ts*2, ts*2);
//        if (i%10==0) {
//            height = h*0.5f;
//            m_painter->drawText(textRect, Qt::AlignHCenter|Qt::AlignCenter, QString::number(i));
//        } else if (i%5==0) {
//            height = h*0.3f;
//            if (space > w*0.02f) m_painter->drawText(textRect, Qt::AlignHCenter|Qt::AlignCenter, QString::number(i));
//        }
//        pointPairs.append(QPointF(posX, y+height));
//        posX += space;
//        i++;
//    }
//    QPen pen(QColor("#E0E0E0"), 1);
//    m_painter->setPen(pen);
//    m_painter->drawLines(pointPairs);
}

static void drawGraphLine(QNanoPainter *m_painter, float x, float y, float w, float h, int items, float t)
{
    auto m_colorWhite = QNanoColor(255,255,255,255);
    auto m_colorGray = QNanoColor(180,180,180,255);
    auto m_colorBlack = QNanoColor(0,0,0,255);
    auto m_color1 = QNanoColor(180,190,40,20);
    auto m_color2 = QNanoColor(255,255,255,150);
    auto m_color3 = QNanoColor(255,255,255,80);

    QVarLengthArray<float, 1024> samples(items);
    QVarLengthArray<float, 1024> sx(items); QVarLengthArray<float, 1024> sy(items);
    float dx = w/(items-1);
    float dotSize = 4.0f + w*0.005;
    int i;

    // Generate positions
    for (i = 0; i<items; i++) {
        samples[i] = 0.5 + sinf((i+1) * t * 0.2) * 0.1;
    }
    for (i = 0; i < items; i++) {
        sx[i] = x+i*dx;
        sy[i] = y+h*samples[i]*0.8f;
    }

    // Draw graph background area
    QNanoLinearGradient bg(x,y,x,y+h, m_color1, m_color2);
    m_painter->beginPath();
    m_painter->moveTo(sx[0], sy[0]);
    for (i = 1; i < items; i++)
        m_painter->bezierTo(sx[i-1]+dx*0.5f,sy[i-1], sx[i]-dx*0.5f,sy[i], sx[i],sy[i]);
    m_painter->lineTo(x+w, y);
    m_painter->lineTo(x, y);
    m_painter->setFillStyle(bg);
    m_painter->fill();

    // Draw graph line
    m_painter->beginPath();
    m_painter->moveTo(sx[0], sy[0]);
    for (i = 1; i < items; i++)
        m_painter->bezierTo(sx[i-1]+dx*0.5f,sy[i-1], sx[i]-dx*0.5f,sy[i], sx[i],sy[i]);
    m_painter->setStrokeStyle(m_colorGray);
    m_painter->setLineWidth(1.0f+dotSize*0.2f);
    m_painter->stroke();

    // Draw dots
    m_painter->beginPath();
    for (i = 0; i < items; i++)
        m_painter->circle(sx[i], sy[i], dotSize*0.8);
    m_painter->setLineWidth(dotSize*0.2);
    m_painter->setStrokeStyle(m_colorBlack);
    m_painter->setFillStyle(m_colorWhite);
    m_painter->fill();
    m_painter->stroke();
}

static void drawGraphBars(QNanoPainter *m_painter, float x, float y, float w, float h, int items, float t) {

    auto m_colorWhite = QNanoColor(255,255,255,255);
    auto m_colorGray = QNanoColor(180,180,180,255);
    auto m_colorBlack = QNanoColor(0,0,0,255);
    auto m_color1 = QNanoColor(180,190,40,20);
    auto m_color2 = QNanoColor(255,255,255,150);
    auto m_color3 = QNanoColor(255,255,255,80);

    QVarLengthArray<float, 1024> samples(items);
    QVarLengthArray<float, 1024> sx(items); QVarLengthArray<float, 1024> sy(items);
    float dx = w/items;
    float barWidth = dx * 0.8f;
    float margin = dx - barWidth;
    int i;

    // Generate positions
    for (i = 0; i<items; i++) {
        samples[i] = 0.5f + sinf(i*0.1f+t)*0.5f;
    }
    for (i = 0; i < items; i++) {
        sx[i] = x+i*dx + margin/2;
        sy[i] = h*samples[i];
    }

    // Draw graph bars
    m_painter->beginPath();
    for (i = 0; i < items; i++) {
        m_painter->rect((int)sx[i]+0.5f, (int)y+1.5f, (int)barWidth, (int)sy[i]);
    }
    int lineWidth = 1.0f;
    m_painter->setLineWidth(lineWidth);
    m_painter->setLineJoin(QNanoPainter::JOIN_MITER);
    m_painter->setFillStyle(m_color3);
    m_painter->setStrokeStyle(m_colorBlack);
    m_painter->fill();
    m_painter->stroke();
}

static void drawGraphCircles(QNanoPainter *m_painter, float x, float y, float w, float h, int items, float t)
{
    float barWidth = 0.3f * w/items;
    float lineMargin = 0.2f * barWidth;
    float showAnimationProgress = 0.1f + 0.4f*sinf(t*0.8f)+0.5f;
    float lineWidth = barWidth*showAnimationProgress;

    float cx = x+w/2;
    float cy = y+h/2;
    float radius1 = w/2 - lineWidth;
    int i;

    // Setup values
    float a1 = -(float)M_PI/2;
    QVarLengthArray<float, 1024> a0(items);
    for (i=0; i<items; i++) {
        a0[i] = -M_PI/2 + 2*M_PI*(((float)items-i)/items)*showAnimationProgress;
    }

    m_painter->setLineWidth(lineWidth);
    m_painter->setLineJoin(QNanoPainter::JOIN_ROUND);
    m_painter->setLineCap(QNanoPainter::CAP_SQUARE);

    // Draw cicle backgrounds
    float r = radius1;
    QNanoColor c_background(215,215,215,50);
    m_painter->setStrokeStyle(c_background);
    for (int i=0 ; i<items ; i++) {
        m_painter->beginPath();
        m_painter->circle(cx, cy, r);
        m_painter->stroke();
        r -= (lineWidth + lineMargin);
    }

    // Draw circle bars
    r = radius1;
    for (int i=0 ; i<items ; i++) {
        m_painter->beginPath();
        m_painter->arc(cx, cy, r, a0[i], a1, QNanoPainter::WINDING_CCW);
        float s = (float)i/items;
        QNanoColor c(200-150*s, 200-50*s, 100+50*s, 255*showAnimationProgress);
        m_painter->setStrokeStyle(c);
        m_painter->stroke();
        r -= (lineWidth + lineMargin);
    }
}

static void drawIcons(QNanoPainter *m_painter, float x, float y, float w, float h, int items, float t)
{
    QNanoImage::ImageFlags imageFlags = {};
    QString path = ":/qml/images/circle.png";
    auto m_circleImage = QNanoImage(path, imageFlags);

    auto m_testFont = QNanoFont(":/qml/fonts/Roboto-Regular.ttf");

    float s = std::min(w, h);
    float size = 16.0f + s*0.5f;
    // Note: Adjust font size to match QPainter sizing
    float fontSize = size * 2.5f * 1.32f;
    m_testFont.setPixelSize(fontSize);
    m_painter->setFont(m_testFont);
    m_painter->setFillStyle("#FFFFFF");
    m_painter->setTextAlign(QNanoPainter::ALIGN_CENTER);
    m_painter->setTextBaseline(QNanoPainter::BASELINE_MIDDLE);
    for (int i=0 ; i<items ; i++) {
        float xp = x + (w-size)/items*i;
        float yp = y + h*0.5f + h * sinf((i+1) * t * 0.1) * 0.5f;
        m_painter->transform(QTransform().rotate(0.785));
        m_painter->drawImage(m_circleImage, QRectF(xp, yp, size * 1.8f, size));
//        m_painter->fillText(QString::number(i+1), QRectF(xp, yp+size/2, size, size));
    }
}

static void drawRuler(QNanoPainter *m_painter, float x, float y, float w, float h, float t)
{
    auto m_testFont = QNanoFont(":/qml/fonts/Roboto-Regular.ttf");
    float posX = x + w*0.05f;
    double space = w*0.03f + sinf(t)*w*0.02f;
    m_painter->setTextAlign(QNanoPainter::ALIGN_CENTER);
    m_painter->setTextBaseline(QNanoPainter::BASELINE_MIDDLE);
    // Note: Adjust font size to match QPainter sizing
    float fontSize = (10.0f + w*0.01f) * 1.32f;
    m_testFont.setPixelSize(fontSize);
    m_painter->setFont(m_testFont);
    m_painter->setStrokeStyle("#E0E0E0");
    m_painter->setFillStyle("#00EE00");
    m_painter->beginPath();
    int i = 0;
    while (posX < w) {
        m_painter->moveTo(posX, y);
        float height = h*0.2;
        QPointF textPoint(posX, y+h);
        if (i%10==0) {
            height = h*0.5;
            m_painter->fillText(QString::number(i), textPoint);
        } else if (i%5==0) {
            height = h*0.3;
            if (space > w*0.02) m_painter->fillText(QString::number(i), textPoint);
        }
        m_painter->lineTo(posX, y+height);
        posX += space;
        i++;
    }
    m_painter->setLineWidth(1.0f);
    m_painter->stroke();
}

static float _flowerPos(int i) {
    const int items = 12;
    return (2*M_PI) * (1 - (float)i/items) - M_PI/2;
}

static void drawFlower(QNanoPainter *m_painter, float x, float y, float w, float h, float t)
{
    const float cx = x + w/2;
    const float cy = y + h/2;
    const float leafSize = w/2;
    m_painter->save(); // Required to prevent rotation multiply

    m_painter->translate(cx, cy);
    m_painter->rotate(sinf(t)*20 * M_PI/180);
    m_painter->translate(-cx, -cy);

    m_painter->setStrokeStyle("#40000000");
    m_painter->setLineWidth(4);
    QNanoRadialGradient gradient1(cx, cy, leafSize);
    QNanoColor startColor((0.5 + sinf(t*2)*0.5)*255, 0, (0.5 + sinf(t+M_PI)*0.5)*255);
    gradient1.setStartColor(startColor);
    gradient1.setEndColor("#ffffff");
    m_painter->setFillStyle(gradient1);

    m_painter->beginPath();
    m_painter->moveTo(cx, cy);
    const int items = 12;
    for (int i=0; i<items; i+=2) {
        m_painter->quadTo(cx + cosf(_flowerPos(i))*leafSize, cy + sinf(_flowerPos(i))*leafSize, cx + cosf(_flowerPos(i+1))*leafSize, cy + sinf(_flowerPos(i+1))*leafSize);
        m_painter->quadTo(cx + cosf(_flowerPos(i+2))*leafSize, cy + sinf(_flowerPos(i+2))*leafSize, cx, cy);
    }
    m_painter->fill();
    m_painter->stroke();

    m_painter->setFillStyle("#ffffff");
    m_painter->beginPath();
    m_painter->circle(cx, cy, 0.1*w);
    m_painter->fill();
    m_painter->restore();
}

#endif // PAINTHELPER_H
