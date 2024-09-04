#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "designdirectory.h"
#include "designfiles.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    DesignDirectory designDirectory;
    DesignFiles designFiles;

    engine.rootContext()->setContextProperty("designFiles", &designFiles);
    engine.rootContext()->setContextProperty("designDirectory", &designDirectory);

    const QUrl url(QStringLiteral("qrc:/artchive/main.qml"));

    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
