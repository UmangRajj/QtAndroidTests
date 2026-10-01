#include "widget.h"
#include "ui_widget.h"

#include <QCoreApplication>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->vibrateBtn, &QPushButton::clicked, this, &Widget::startVibration);
    connect(ui->toastBtn, &QPushButton::clicked, this, &Widget::startToast);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::startVibration()
{

}

void Widget::startToast()
{
    QNativeInterface::QAndroidApplication *app = QCoreApplication::instance()->nativeInterface<QNativeInterface::QAndroidApplication>();


}
