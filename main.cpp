#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "designfiles.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Create an instance of DesignFjles
    DesignFiles designFiles;

    // Register the MyModel instance with the QML engine
    engine.rootContext()->setContextProperty("designFiles", &designFiles);

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
