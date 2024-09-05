#ifndef ARTCHIVEDB_H
#define ARTCHIVEDB_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <string>
#include <vector>
#include "database.h"

class ArtchiveDB : public Database {

public:
    ArtchiveDB();
    ~ArtchiveDB() override;

    bool connect(const std::string& connection_string) override;

    void disconnect() override;

    bool execute_query(const std::string& query) override;

    std::vector<std::vector<std::string>> execute_select_query(const std::string& query) override;

    void begin_transaction() override;

    void commit_transaction() override;

    void rollback_transaction() override;

    bool is_connected() const override;

    std::string get_last_error() const override;

private:
    QSqlDatabase db;
};

#endif // ARTCHIVEDB_H






















// class SQLiteDatabase : public Database {
// public:
//     SQLiteDatabase() : db(nullptr) {}
//
//     ~SQLiteDatabase() {
//         if (db) {
//             sqlite3_close(db);
//         }
//     }
//
//     bool connect(const std::string& connectionString) override {
//         int rc = sqlite3_open(connectionString.c_str(), &db);
//         if (rc) {
//             lastError = sqlite3_errmsg(db);
//             return false;
//         }
//         return true;
//     }
//
//     void disconnect() override {
//         if (db) {
//             sqlite3_close(db);
//             db = nullptr;
//         }
//     }
//
//     bool executeQuery(const std::string& query) override {
//         char* errMsg = nullptr;
//         int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errMsg);
//         if (rc != SQLITE_OK) {
//             lastError = errMsg;
//             sqlite3_free(errMsg);
//             return false;
//         }
//         return true;
//     }
//
//     std::vector<std::vector<std::string>> executeSelectQuery(const std::string& query) override {
//         std::vector<std::vector<std::string>> results;
//         // Implementation for executing SELECT queries and populating results
//         // This would involve using sqlite3_prepare_v2, sqlite3_step, sqlite3_column_text, etc.
//         return results;
//     }
//
//     void beginTransaction() override {
//         executeQuery("BEGIN TRANSACTION");
//     }
//
//     void commitTransaction() override {
//         executeQuery("COMMIT TRANSACTION");
//     }
//
//     void rollbackTransaction() override {
//         executeQuery("ROLLBACK TRANSACTION");
//     }
//
//     bool isConnected() const override {
//         return db != nullptr;
//     }
//
//     std::string getLastError() const override {
//         return lastError;
//     }
//
// private:
//     sqlite3* db;
//     std::string lastError;
// };
//
