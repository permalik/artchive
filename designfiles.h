#ifndef DESIGNFILES_H
#define DESIGNFILES_H

#include <QObject>
#include "designdirectory.h"

// TODO: Refactor to snake_case
class DesignFiles : public QObject {
    Q_OBJECT
    Q_PROPERTY(QStringList items READ items NOTIFY itemsChanged)

public:
    explicit DesignFiles(DesignDirectory *designDirectory, QObject *parent = nullptr);
    QStringList items() const;

signals:
    void itemsChanged();

private:
    DesignDirectory *designDirectory;
    QStringList d_files;
};

#endif // DESIGNFILES_H
