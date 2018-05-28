#include <QGuiApplication>
#include <Qt3DQuickExtras/Qt3DQuickWindow>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    // window.setSource(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
