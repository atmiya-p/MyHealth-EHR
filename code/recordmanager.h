#ifndef RECORDMANAGER_H
#define RECORDMANAGER_H

#include "DBManager.h"
#include "Record.h"
#include <vector>
#include <string>


class RecordManager : public DBManager {
public:

    explicit RecordManager(const std::string& dbPath);

    bool createRecordsTable();

    bool addRecord(const Record& record);

    std::vector<Record> getAllRecordsForPatient(const std::string& patientUsername);

    std::string getFormattedRecordsString(const std::string& patientUsername);
};

#endif
