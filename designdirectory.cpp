#include "designdirectory.h"
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

// Create a dedicated class for the db

DesignDirectory::DesignDirectory(QObject *parent) : QObject{parent} {
  if (!initializeDatabase()) {
    qWarning() << "Failed to initialize database.";
  }
}

QString DesignDirectory::dir_path() const { return d_path; }

void DesignDirectory::set_dir_path(const QString &dir_path) {
  if (dir_path == d_path)
    return;

  d_path = dir_path;

  if (updateDatabase(d_path)) {
    emit dir_changed(d_path);
  } else {
    qWarning() << "Failed to persist new directory path";
  }
}

bool DesignDirectory::initializeDatabase() {
  db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName("/Users/au4/git/artchive/artchive.db");

  if (!db.open()) {
    qWarning() << "Failed to open database: " << db.lastError().text();
    return false;
  }

  QSqlQuery query;
  if (!query.exec("CREATE TABLE IF NOT EXISTS config (id INTEGER PRIMARY KEY, "
                  "dir_path TEXT)")) {
    qWarning() << "Failed to create table:" << query.lastError().text();
    return false;
  }
  return true;
}

bool DesignDirectory::updateDatabase(const QString &dir_path) {
  QSqlQuery query;
  query.prepare("REPLACE INTO config (id, dir_path) VALUES (1, :dir_path)");
  query.bindValue(":dir_path", dir_path);

  if (!query.exec()) {
    qWarning() << "Failed to update directory path: "
               << query.lastError().text();
    return false;
  }
  return true;
}
