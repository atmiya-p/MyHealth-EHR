/**
 * @file DBPatient.cpp
 * @brief This class is used to manage patient-related database operations.
 *
 * This class handles the "Patients" table, which includes creating the table, inserting new patient records, and verifying if a patient's username exists in the table
 *
 * @date November 16, 2024
 */

#include "DBPatient.h"
#include <iostream>

/**
 * @brief Constructs a DBPatient object and initializes the db connection
 *
 * @param dbPath - path to the SQLite file
 */
DBPatient::DBPatient(const std::string& dbPath) : DBManager(dbPath) {}

/**
 * @brief Creates the "Patients" table in the database if it doesn't exist
 *
 * @return true if the table was successfully created or already exists. False otherwise
 */
bool DBPatient::createPatientTable() {
    const std::string sql =
        "CREATE TABLE IF NOT EXISTS Patients ("
        "Username TEXT PRIMARY KEY, "
        "Password TEXT, "
        "VerificationCode TEXT);";

    char* error_message = nullptr;
    int exit_code = sqlite3_exec(getDatabase(), sql.c_str(), nullptr, nullptr, &error_message);

    if (exit_code != SQLITE_OK) {
        std::cerr << "Error creating Patients table: " << error_message << std::endl;
        sqlite3_free(error_message);
        return false;
    }

    std::cout << "Patients table created successfully!" << std::endl;
    return true;
}

/**
 * @brief Inserts a new patient into the "Patients" table.
 *
 * This method inserts a patient with a username and verification code into the database. The password is initially set to NULL.
 *
 * @param username which is the patient's username.
 * @param verificationCode which is patient's verification code (doctor username)
 * @return true if the patient was successfully inserted, false otherwise.
 */
bool DBPatient::insertPatient(const std::string username, const std::string verificationCode) {
    createPatientTable();
    const std::string sql = "INSERT INTO Patients (Username, VerificationCode) VALUES (?,?);";

    sqlite3_stmt* stmt;
    bool success = false;

    if (sqlite3_prepare_v2(getDatabase(), sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, verificationCode.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_DONE) {
            success = true;
        } else {
            std::cerr << "Failed to insert patient: " << sqlite3_errmsg(getDatabase()) << std::endl;
        }
    } else {
        std::cerr << "Failed to prepare patient insert statement: " << sqlite3_errmsg(getDatabase()) << std::endl;
    }

    sqlite3_finalize(stmt);
    return success;
}

/**
 * @brief Checks if a patient's username and verification code exist in the db.
 *
 * This method validates if a patient record exists with the username and verification code.
 *
 * @param username - the patient's username.
 * @param code - patient's verification code.
 * @return true if a matching record exists, false otherwise.
 */
bool DBPatient::usernameAndCodeExistInPatient(const std::string& username, const std::string& code) {
    const std::string sql = "SELECT 1 FROM Patients WHERE Username = ? AND VerificationCode = ?;";

    sqlite3_stmt* stmt;
    bool exists = false;

    if (sqlite3_prepare_v2(getDatabase(), sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, code.c_str(), -1, SQLITE_STATIC);

        exists = (sqlite3_step(stmt) == SQLITE_ROW);
    } else {
        std::cerr << "Failed to prepare username and code check: " << sqlite3_errmsg(getDatabase()) << std::endl;
    }

    sqlite3_finalize(stmt);
    return exists;
}

/**
 * @brief Checks if a patient's password is set NULL in the db
 *
 * This method verifies if a patient's record has no password set - this implies that they haven't signed up on the system yet
 *
 * @param username - patient's username.
 * @return true if the password is NULL, false otherwise.
 */
bool DBPatient::isPasswordNullInPatient(const std::string& username) {
    const std::string sql = "SELECT 1 FROM Patients WHERE Username = ? AND Password IS NULL;";

    sqlite3_stmt* stmt;
    bool isNull = false;

    if (sqlite3_prepare_v2(getDatabase(), sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);

        isNull = (sqlite3_step(stmt) == SQLITE_ROW);
    } else {
        std::cerr << "Failed to prepare password null check: " << sqlite3_errmsg(getDatabase()) << std::endl;
    }

    sqlite3_finalize(stmt);
    return isNull;
}

/**
 * @brief Updates a patient's password in the db.
 *
 * This method sets a new password for a patient identified by username.
 *
 * @param username - patient's username.
 * @param password - new password to set.
 * @return true if the password was successfully updated, false otherwise
 */
bool DBPatient::updatePatientPassword(const std::string& username, const std::string& password) {
    const std::string sql = "UPDATE Patients SET Password = ? WHERE Username = ?;";

    sqlite3_stmt* stmt;
    bool success = false;

    if (sqlite3_prepare_v2(getDatabase(), sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, password.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, username.c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_DONE) {
            success = true;
        } else {
            std::cerr << "Failed to update password: " << sqlite3_errmsg(getDatabase()) << std::endl;
        }
    } else {
        std::cerr << "Failed to prepare password update statement: " << sqlite3_errmsg(getDatabase()) << std::endl;
    }

    sqlite3_finalize(stmt);
    return success;
}
