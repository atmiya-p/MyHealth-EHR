#ifndef SIGNUP_H
#define SIGNUP_H

#include <string>
#include "DBDoctor.h"
#include "DBPatient.h"

class SignUp {
public:
    SignUp();

    bool registerUser(const std::string& username, const std::string& password, const std::string& signUpCode);
    bool passwordValid(const std::string& password) const;

};

#endif // SIGNUP_H
