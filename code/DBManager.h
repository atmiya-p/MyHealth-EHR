#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <sqlite3.h>
#include <string>

class DBManager {
public:
    explicit DBManager(const std::string& dbPath);
    virtual ~DBManager();

    bool verifyLogin(const std::string& username, const std::string& password, const std::string& role);

protected:
    sqlite3* getDatabase();

private:
    sqlite3* db;
};

#endif
