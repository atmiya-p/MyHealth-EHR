#ifndef PATIENT_H
#define PATIENT_H

#include "User.h"
#include <string>

class Patient : public User {
public:
    static Patient& getInstance();

    Patient(const Patient&) = delete;
    Patient& operator=(const Patient&) = delete;

    void setPatient(const std::string& username, const std::string& password, const std::string& verificationCode);

    std::string getVerificationCode() const;

private:
    Patient(const std::string& username = "", const std::string& password = "", const std::string& verificationCode = "");

    std::string verificationCode;
};

#endif
