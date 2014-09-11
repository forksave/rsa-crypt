#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "cryptmananger.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    CryptMananger* cryptManager=new CryptMananger();
    engine.rootContext()->setContextProperty("cryptManager", cryptManager);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
