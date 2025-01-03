/**
 * @file DBManager.cpp
 * @brief This class is used to connect the database and perform login verification
 *
 * This file contains the logic for managing the SQLite database connection, verifying user logins, and starting the database operations for the EHR
 *
 * @date November 16, 2024
 */

#include "DBManager.h"
#include <iostream>

/**
 * @brief Constructs a DBManager object and initializes the db connection
 *
 * Open a connection to the SQLite database at the path
 *
 * @param dbPath path to the SQLite database file
 */
DBManager::DBManager(const std::string& dbPath) : db(nullptr) {
    int exit_code = sqlite3_open(dbPath.c_str(), &db);
    if (exit_code) {
        std::cerr << "Error opening database: " << sqlite3_errmsg(db) << std::endl;
        db = nullptr;
    } else {
        std::cout << "Database opened successfully!" << std::endl;
    }
}

/**
 * @brief Destroys the DBManager object and closes the db connection
 *
 * Makes sure that the SQLite database connection is properly closed
 */
DBManager::~DBManager() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

/**
 * @brief Getter to get the SQLite database connection object
 *
 * Provides access to the sqlite3* database connection for use in other methods
 *
 * @return Pointer to the SQLite database connection object
 */
sqlite3* DBManager::getDatabase() {
    return db;
}

/**
 * @brief Verifies the login credentials
 *
 * This method checks if the provided username and password match a record in the database for the specified role (Doctor or Patient)
 *
 * @param username the username provided by the user.
 * @param password the password provided by the user.
 * @param role The role of the user ("DOCTOR" or "PATIENT")
 * @return true if the credentials are valid; false otherwise.
 */
bool DBManager::verifyLogin(const std::string& username, const std::string& password, const std::string& role) {
    std::string sql;

    if (role == "DOCTOR") {
        sql = "SELECT 1 FROM Doctors WHERE Username = ? AND Password = ?;";
    } else if (role == "PATIENT") {
        sql = "SELECT 1 FROM Patients WHERE Username = ? AND Password = ?;";

    } else {
        std::cerr << "Invalid role specified: " << role << std::endl;
        return false;
    }

    sqlite3_stmt* stmt;
    int exit_code = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    if (exit_code != SQLITE_OK) {
        std::cerr << "SQL error preparing statement: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, password.c_str(), -1, SQLITE_STATIC);

    bool validLogin = (sqlite3_step(stmt) == SQLITE_ROW);

    sqlite3_finalize(stmt);

    return validLogin;
}
