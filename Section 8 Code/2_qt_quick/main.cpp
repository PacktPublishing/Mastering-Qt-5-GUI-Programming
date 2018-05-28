#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "photomodel.h"
#include "colorpicker.h"



int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    // NOTE: we use `QGuiApplication` instead of `QApplication` as
    // we're not using widgets
    QGuiApplication app(argc, argv);

    // this registration code to be covered in video 5.3
    qmlRegisterType<ColorPicker>("ColorPickers", 1, 0, "ColorPicker");

    QQmlApplicationEngine engine;

    PhotoModel photo_model;

    QQmlContext *root_context = engine.rootContext();
    root_context->setContextProperty("photo_model", &photo_model);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    // TODO: Connect QML signal to C++ slot here
    QObject *root_object = engine.rootObjects().value(0);
    QObject::connect(root_object, SIGNAL(request_new_colors(QString)), &photo_model, SLOT(randomize_color_values()));

    return app.exec();
}
