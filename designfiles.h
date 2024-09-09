#ifndef DESIGNFILES_H
#define DESIGNFILES_H

#include <QColor>
#include <QObject>
#include <QVector>

// TODO: Refactor to snake_case
class DesignFiles : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString dir_path READ dir_path WRITE set_dir_path NOTIFY dir_path_changed)
    Q_PROPERTY(QStringList items READ items NOTIFY items_changed)
    Q_PROPERTY(QVector<QColor> colors READ colors NOTIFY items_changed)

public:
    explicit DesignFiles(QObject *parent = nullptr);

    QString dir_path() const;

    QStringList items();

    QVector<QColor> colors() const;

public slots:
    void set_dir_path(const QString &dir_path);

signals:
    void dir_path_changed();
    void items_changed();

private:
    QString m_dir_path;
    QStringList d_files;
    QVector<QColor> file_colors;
};

#endif // DESIGNFILES_H
