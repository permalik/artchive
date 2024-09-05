#include "designdirectory.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

// Create a dedicated class for the db

DesignDirectory::DesignDirectory(QObject *parent) : QObject{parent} {
  if (!initialize_database()) {
    qWarning() << "Failed to initialize database.";
  }
}

QString DesignDirectory::dir_path() const {
    return d_path;
}

void DesignDirectory::set_dir_path(const QString &dir_path) {
  if (dir_path == d_path)
    return;

  d_path = dir_path;

  if (update_database(d_path)) {
    emit dir_changed(d_path);
  } else {
    qWarning() << "Failed to persist new directory path";
  }
}

bool DesignDirectory::initialize_database() {
    if (!db.connect("/Users/au4/git/artchive/artchive.db")) {
        qWarning() << "Failed to initialize database.";
        return false;
    }
    const std::string create_table_query = "CREATE TABLE IF NOT EXISTS config (id INTEGER PRIMARY KEY, dir_path TEXT)";
    if (!db.execute_query(create_table_query)) {
        qWarning() << "Failed to create table: " << QString::fromStdString(db.get_last_error());
        return false;
    }
    return true;
}

bool DesignDirectory::update_database(const QString &dir_path) {
    std::string query = "REPLACE INTO config (id, dir_path) VALUES (1, '" + dir_path.toStdString() + "')";
    if (!db.execute_query(query)) {
        qWarning() << "Failed to update database: " << QString::fromStdString(db.get_last_error());
        return false;
    }
    return true;
}
