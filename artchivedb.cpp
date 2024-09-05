#include "artchivedb.h"
#include <QVariant>

ArtchiveDB::ArtchiveDB() {
    db = QSqlDatabase::addDatabase("QSQLITE");
}

ArtchiveDB::~ArtchiveDB() {
    if (db.isOpen()) {
        db.close();
    }
}

bool ArtchiveDB::connect(const std::string& connection_string) {
    db.setDatabaseName(QString::fromStdString(connection_string));
    if (!db.open()) {
        qWarning() << "Failed to open database: " << db.lastError().text();
        return false;
    }
    return true;
}

void ArtchiveDB::disconnect() {
    if (db.isOpen()) {
        db.close();
    }
}

bool ArtchiveDB::execute_query(const std::string& query) {
    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query))) {
        qWarning() << "Failed to execute query: " << q.lastError().text();
        return false;
    }
    return true;
}

int row_count() {
    QSqlQuery q;
    int row_count = 0;
    q.exec("SELECT COUNT(*) FROM config");
    if (q.first()) {
        row_count = q.value(0).toInt();
    }
    return row_count;
}

std::vector<std::vector<std::string>> ArtchiveDB::execute_select_query(const std::string& query) {
    std::vector<std::vector<std::string>> result;
    QSqlQuery q;
    if (!q.exec(QString::fromStdString(query))) {
        qWarning() << "Failed to execute query: " << q.lastError();
        return result;
    }
    while (q.next()) {
        std::vector<std::string> row;
        for (int i = 0; i < row_count(); i++) {
            row.push_back(q.value(i).toString().toStdString());
        }
        result.push_back(row);
    }
    return result;
}

void ArtchiveDB::begin_transaction() {
    QSqlQuery q;
    if (!q.exec("BEGIN TRANSACTION")) {
        qWarning() << "Failed to begin transaction: " << q.lastError().text();
    }
}

void ArtchiveDB::commit_transaction() {
    QSqlQuery q;
    if (!q.exec("COMMIT TRANSACTION")) {
        qWarning() << "Failed to commit transaction: " << q.lastError().text();
    }
}

void ArtchiveDB::rollback_transaction() {
    QSqlQuery q;
    if (!q.exec("ROLLBACK TRANSACTION")) {
        qWarning() << "Failed to rollback transaction: " << q.lastError().text();
    }
}

bool ArtchiveDB::is_connected() const {
    return db.isOpen();
}

std::string ArtchiveDB::get_last_error() const {
    return db.lastError().text().toStdString();
}
