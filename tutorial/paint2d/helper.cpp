#include "helper.h"

Helper::Helper()
{
    QLinearGradient gradient(QPointF(50,-20), QPointF(80,20));
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, QColor(0xa6, 0xce, 0x39));

    background = QBrush(QColor(64,32,64));
    circleBrush = QBrush(gradient);
}

void Helper::paint(QPainter *painter, QPaintEvent *event, int elapsed)
{
    painter->fillRect(event->rect(), background);
    painter->translate(100, 100);
    painter->save();
    painter->setBrush(circleBrush);
    painter->rotate(elapsed*.05);

    qreal r = elapsed/1000.0;
    int n=30;
    for(int i=0; i<n; i++)
    {
        painter->rotate(30);
        qreal factor = (i+r)/n;
        qreal radius = 0 + 120*factor;
        qreal circleRadius  = 1 +factor*20;
        painter->drawEllipse(QRectF(radius, -circleRadius, 2*circleRadius, 2*circleRadius));
    }
    painter->restore();
}

