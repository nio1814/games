#ifndef CAMERA_H
#define CAMERA_H

#include <QMainWindow>

namespace Ui {
class Camera;
}

class Camera : public QMainWindow
{
    Q_OBJECT

public:
    explicit Camera(QWidget *parent = 0);
    ~Camera();

private:
    Ui::Camera *ui;
};

#endif // CAMERA_H
