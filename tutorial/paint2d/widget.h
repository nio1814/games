#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "helper.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(Helper *helper, QWidget *parent);
    ~Widget();
public slots:
    void animate();
protected:
    void paintEvent(QPaintEvent *event);
private:
    Helper *helper;
    int elapsed;
};

#endif // WIDGET_H
