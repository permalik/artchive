#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>

class Database {

public:
    virtual ~Database() = default;

    virtual bool connect(const std::string& connection_string) = 0;

    virtual void disconnect() = 0;

    virtual bool execute_query(const std::string& query) = 0;

    virtual std::vector<std::vector<std::string>> execute_select_query(const std::string& query) = 0;

    virtual void begin_transaction() = 0;

    virtual void commit_transaction() = 0;

    virtual void rollback_transaction() = 0;

    virtual bool is_connected() const = 0;

    virtual std::string get_last_error() const = 0;
};

#endif // DATABASE_H
