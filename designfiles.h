#ifndef DESIGNFILES_H
#define DESIGNFILES_H
#include <QObject>

class DesignFiles : public QObject {
    Q_OBJECT
    Q_PROPERTY(QStringList items READ items NOTIFY itemsChanged)

public:
    explicit DesignFiles(QObject *parent = nullptr);

    QStringList items() const;

signals:
    void itemsChanged();

private:
    QStringList d_files;
};

#endif // DESIGNFILES_H
