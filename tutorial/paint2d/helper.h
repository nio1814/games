#ifndef HELPER_H
#define HELPER_H

#include "qpainter.h"
#include "QPaintEvent"

class Helper
{
public:
    Helper();
    void paint(QPainter *painter, QPaintEvent *event, int elapsed);

signals:

public slots:
};

#endif // HELPER_H
