#include "recordmanager.h"
#include <iostream>
#include <sstream>

/**
 * @brief Constructs a RecordManager object
 *
 * Initializes the RecordManager and connects to the SQLite database.
 *
 * @param dbPath The path to the SQLite database file.
 */
RecordManager::RecordManager(const std::string& dbPath) : DBManager(dbPath) {}

/**
 * @brief Creates the Records table in the database if it does not exist.
 *
 * @return true if the table is created successfully, false otherwise.
 */
bool RecordManager::createRecordsTable() {
    const std::string sql =
        "CREATE TABLE IF NOT EXISTS Records ("
        "PatientID TEXT NOT NULL, "
        "DoctorID TEXT NOT NULL, "
        "Date TEXT NOT NULL, "
        "Notes TEXT NOT NULL, "
        "Prescription TEXT );";

    char* error_message = nullptr;
    int exit_code = sqlite3_exec(getDatabase(), sql.c_str(), nullptr, nullptr, &error_message);

    if (exit_code != SQLITE_OK) {
        std::cerr << "Error creating Records table: " << error_message << std::endl;
        sqlite3_free(error_message);
        return false;
    }

    std::cout << "Records table created successfully!" << std::endl;
    return true;
}

/**
 * @brief Adds a new record for a patient to the database.
 *
 * @param record The Record object containing the record details.
 * @return true if the record was added successfully, false otherwise.
 */
bool RecordManager::addRecord(const Record& record) {
    createRecordsTable();
    sqlite3* db = getDatabase();
    if (!db) {
        std::cerr << "Database connection is null." << std::endl;
        return false;
    }

    const std::string sql = "INSERT INTO Records (PatientID, DoctorID, Date, Notes, Prescription) "
                            "VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    bool success = false;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, record.getPatientID().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 2, record.getDoctorID().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 3, record.getDate().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 4, record.getNotes().c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(stmt, 5, record.getPrescription().c_str(), -1, SQLITE_STATIC);

        if (sqlite3_step(stmt) == SQLITE_DONE) {
            success = true;
        } else {
            std::cerr << "Failed to add record: " << sqlite3_errmsg(db) << std::endl;
        }
    } else {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    return success;
}

/**
 * @brief Retrieves all records associated with a specific patient.
 *
 * @param patientUsername The username of the patient whose records are to be retrieved.
 * @return A vector of Record objects containing the patient's records.
 */
std::vector<Record> RecordManager::getAllRecordsForPatient(const std::string& patientUsername) {
    sqlite3* db = getDatabase();
    const std::string sql =
        "SELECT DoctorID, Date, Notes, Prescription FROM Records WHERE PatientID = ?;";
    sqlite3_stmt* stmt;
    std::vector<Record> records;

    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, patientUsername.c_str(), -1, SQLITE_STATIC);

        while (sqlite3_step(stmt) == SQLITE_ROW) {
            std::string doctorID = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
            std::string date = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            std::string notes = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
            std::string prescription = sqlite3_column_text(stmt, 3) ? reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)) : "None";

            records.push_back(Record::createRecord(patientUsername, doctorID, date, notes, prescription));
        }
    } else {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    return records;
}

/**
 * @brief Formats all records for a specific patient into a string.
 *
 * @param patientUsername The username of the patient whose records are to be formatted.
 * @return A formatted string of patient records, or a message if no records are found.
 */
std::string RecordManager::getFormattedRecordsString(const std::string& patientUsername) {
    auto records = getAllRecordsForPatient(patientUsername);

    if (records.empty()) {
        return "No records found for the specified patient.";
    }

    std::ostringstream oss;
    for (const auto& record : records) {
        oss << "DoctorID: " << record.getDoctorID() << "\n"
            << "Date: " << record.getDate() << "\n"
            << "Notes: " << record.getNotes() << "\n"
            << "Prescription: " << (record.getPrescription().empty() ? "None" : record.getPrescription()) << "\n"
            << "-----------------------------------\n";
    }

    return oss.str();
}
