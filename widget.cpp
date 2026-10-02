#include "widget.h"
#include "ui_widget.h"

#include <QCoreApplication>
#include <QDebug>

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
    QJniObject context = QNativeInterface::QAndroidApplication::context();
    QJniObject vibrateServiceName = QJniObject::getStaticField<jstring>("android/content/Context", "VIBRATOR_MANAGER_SERVICE");

    QJniObject vibratorMgr = context.callMethod<jobject>("getSystemService", vibrateServiceName.object<jstring>());

    QJniObject vibratorEffect = QJniObject::callStaticObjectMethod("android/os/VibrationEffect",
                                                                   "createOneShot",
                                                                   "(JI)Landroid/os/VibrationEffect;",
                                                                   ui->vibrationDurationDial->value(),
                                                                   ui->vibrationAmpDial->value());

    QJniObject vibrator = vibratorMgr.callMethod<jobject>("getDefaultVibrator",
                                                          "()Landroid/os/Vibrator;");

    if (vibrator.isValid() && vibratorEffect.isValid()) {
        vibrator.callMethod<void>("vibrate",
                                  "(Landroid/os/VibrationEffect;)V",
                                  vibratorEffect.object());
    } else {
        qDebug() << "Couldn't vibrate, objects aren't valid!";
    }
}

void Widget::startToast()
{
    jint duration = ui->toastDurationDial->value();
    QString msg = ui->toastTextLineEdit->text();

    QNativeInterface::QAndroidApplication::runOnAndroidMainThread([duration, msg] {
        QJniObject context = QNativeInterface::QAndroidApplication::context();

        QJniObject message = QJniObject::fromString(msg);

        QJniObject toast = QJniObject::callStaticObjectMethod("android/widget/Toast",
                                                              "makeText",
                                                              "(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;",
                                                              context.object(),
                                                              message.object(),
                                                              duration);
        if (toast.isValid())
            toast.callMethod<void>("show");
        return QVariant();
    });
}
