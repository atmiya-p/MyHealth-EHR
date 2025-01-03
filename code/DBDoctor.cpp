/**
 * @file DBDoctor.cpp
 * @brief This class is used to manage doctor-related database operations.
 *
 * This class handles the "Doctors" table, which includes creating the table, inserting new doctor records, and verifying if a doctor's username exists in the table
 *
 * @date November 16, 2024
 */

#include "DBDoctor.h"
#include <iostream>

/**
 * @brief Constructs a DBDoctor object and initializes the db connection
 *
 * @param dbPath which is the path to the SQLite database file
 */
DBDoctor::DBDoctor(const std::string& dbPath) : DBManager(dbPath) {}


/**
 * @brief Creates the "Doctors" table in the db if it doesn't exist
 *
 * @return true if the table was successfully created or already exists. Otherwise, returns false
 */
bool DBDoctor::createDoctorTable() {
    const std::string sql =
        "CREATE TABLE IF NOT EXISTS Doctors ("
        "Username TEXT PRIMARY KEY, "
        "Password TEXT NOT NULL);";

    char* error_message = nullptr;
    int exit_code = sqlite3_exec(getDatabase(), sql.c_str(), nullptr, nullptr, &error_message);

    if (exit_code != SQLITE_OK) {
        std::cerr << "Error creating Doctors table: " << error_message << std::endl;
        sqlite3_free(error_message);
        return false;
    }

    std::cout << "Doctors table created successfully!" << std::endl;
    return true;
}

/**
 * @brief Inserts a new doctor into the "Doctors" table
 *
 * This method uses query to insert a doctor record into the database. The doctor username must be unique, and the password cannot be null.
 *
 * @param doctor A `Doctor` object that has the username and password to insert.
 * @return true if the doctor was successfully inserted. Otherwise, returns false
 */
bool DBDoctor::insertDoctor(const Doctor& doctor) {
    createDoctorTable();
    const std::string sql = "INSERT INTO Doctors (Username, Password) VALUES (?, ?);";

    sqlite3_stmt* stmt;
    bool success = false;

    if (sqlite3_prepare_v2(getDatabase(), sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, doctor.getUsername().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, doctor.getPassword().c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_DONE) {
            success = true;
        } else {
            std::cerr << "Failed to insert doctor: " << sqlite3_errmsg(getDatabase()) << std::endl;
        }
    } else {
        std::cerr << "Failed to prepare doctor insert statement: " << sqlite3_errmsg(getDatabase()) << std::endl;
    }

    sqlite3_finalize(stmt);
    return success;
}

/**
 * @brief Checks if the username exists in the "Doctors" table
 *
 * This method determines if a doctor's username already exists
 *
 * @param username The username to check for existence.
 * @return true if the username exists and returns false otherwise.
 */
bool DBDoctor::usernameExistsInDoctor(const std::string& username) {
    const std::string sql = "SELECT 1 FROM Doctors WHERE Username = ?;";

    sqlite3_stmt* stmt;
    bool exists = false;

    if (sqlite3_prepare_v2(getDatabase(), sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

        exists = (sqlite3_step(stmt) == SQLITE_ROW);
    } else {
        std::cerr << "Failed to prepare doctor username check: " << sqlite3_errmsg(getDatabase()) << std::endl;
    }

    sqlite3_finalize(stmt);
    return exists;
}
