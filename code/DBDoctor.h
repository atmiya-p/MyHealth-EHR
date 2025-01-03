#ifndef DBDOCTOR_H
#define DBDOCTOR_H

#include "DBManager.h"
#include "Doctor.h"
#include <string>

class DBDoctor : public DBManager {
public:
    explicit DBDoctor(const std::string& dbPath);

    bool createDoctorTable();  // Create the Doctors table
    bool insertDoctor(const Doctor& doctor);  // Insert a new doctor
    bool usernameExistsInDoctor(const std::string& username);  // Check if username exists in Doctors
};

#endif // DBDOCTOR_H
