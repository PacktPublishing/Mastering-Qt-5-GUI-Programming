#include <QGuiApplication>
#include <Qt3DQuickExtras/Qt3DQuickWindow>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    Qt3DExtras::Quick::Qt3DQuickWindow window;
    window.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    window.show();

    return app.exec();
}
