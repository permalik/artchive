#ifndef DESIGNFILES_H
#define DESIGNFILES_H

#include <QColor>
#include <QObject>
#include <QVector>
#include "designdirectory.h"

// TODO: Refactor to snake_case
class DesignFiles : public QObject {
    Q_OBJECT
    Q_PROPERTY(QStringList items READ items NOTIFY itemsChanged)
    Q_PROPERTY(QVector<QColor> colors READ colors NOTIFY itemsChanged)

public:
    explicit DesignFiles(DesignDirectory *designDirectory, QObject *parent = nullptr);
    QStringList items() const;
    QVector<QColor> colors() const;

signals:
    void itemsChanged();

private:
    DesignDirectory *designDirectory;
    QStringList d_files;
    QVector<QColor> file_colors;
};

#endif // DESIGNFILES_H
