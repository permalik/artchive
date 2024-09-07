#ifndef DESIGNDIRECTORY_H
#define DESIGNDIRECTORY_H

#include <QObject>
#include <QString>
#include "artchivedb.h"

class DesignDirectory : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString dir_path READ dir_path WRITE set_dir_path NOTIFY dir_changed)

public:
    explicit DesignDirectory(QObject *parent = nullptr);
    QString dir_path() const;

public slots:
    void set_dir_path(const QString &dir_path);
    QString get_dir_path();

signals:
    void dir_changed(const QString & dir_path);

private:
    bool initialize_database();
    bool update_database(const QString &dir_path);

    QString d_path;
    ArtchiveDB db;
};

#endif // DESIGNDIRECTORY_H
