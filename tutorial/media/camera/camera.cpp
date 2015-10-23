#include "camera.h"
#include "ui_camera.h"

//#include <QCam

Camera::Camera(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Camera)
{
    ui->setupUi(this);

    QActionGroup *videoDevicesGroup = new QActionGroup(this);
    videoDevicesGroup->setExclusive(true);
//    foreach(const qcam)
}

Camera::~Camera()
{
    delete ui;
}
