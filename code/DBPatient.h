#ifndef DBPATIENT_H
#define DBPATIENT_H

#include "DBManager.h"
#include "Patient.h"
#include <string>

class DBPatient : public DBManager {
public:
    explicit DBPatient(const std::string& dbPath);

    bool createPatientTable();
    bool insertPatient(const std::string username, const std::string verificationCode);
    bool usernameAndCodeExistInPatient(const std::string& username, const std::string& code);
    bool isPasswordNullInPatient(const std::string& username);
    bool updatePatientPassword(const std::string& username, const std::string& password);
};

#endif
