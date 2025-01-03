/**
 * @file SignUp.cpp
 * @brief Implements the SignUp class for user registration
 *
 * Provides implementation of the SignUp class, which handles registration of doctors and patients in the system. It handles verification codes, checks username existence (for patients), and updates or inserts user credentials into the database. Also, it includes password validation to make sure it is 8 characters.
 *
 * @date November 16, 2024
 */


#include "SignUp.h"
#include "DBManager.h"
#include "Doctor.h"
#include <iostream>

SignUp::SignUp() {
}

/**
 * @brief Registers a new user (doctor or patient) in the system
 *
 * This method checks if the user is registering as a doctor or a patient based on the provided signup code.
 * For doctors, it makes sure that the username does not already exist and then inserts the doctor into the database.
 * For patients, it verifies the signup code and checks if a password is already set before updating the patient's password.
 *
 * @param username - username of the user to register.
 * @param password - password of the user to register.
 * @param signUpCode - signup code to determine if the user is a doctor or patient.
 * @return true if the user was successfully registered, false otherwise.
 */
bool SignUp::registerUser(const std::string& username, const std::string& password, const std::string& signUpCode) {
    DBDoctor dbd("ehr_database.db");
    DBPatient dbp("ehr_database.db");

    if (signUpCode == "DOCTOR") {
        if (!dbd.usernameExistsInDoctor(username)) {
            Doctor& doctor = Doctor::getInstance();
            doctor.setUsername(username);
            doctor.setPassword(password);
            return dbd.insertDoctor(doctor);
        }
        else {
            std::cerr << "Doctor username already exists." << std::endl;
            return false;
        }
    }
    else {
        if (dbp.usernameAndCodeExistInPatient(username, signUpCode) && dbp.isPasswordNullInPatient(username)) {
            return dbp.updatePatientPassword(username, password);
        }
        else {
            std::cerr << "Invalid patient signup code or password already set." << std::endl;
            return false;
        }
    }
}

/**
 * @brief Makes sure pass >= 8 characters
 *
 * Ensures that the password meets the requirement of being at least 8 characters long.
 *
 * @param password - password to validate.
 * @return true if the password is valid, false otherwise.
 */
bool SignUp::passwordValid(const std::string& password) const {
    if(password.length()>=8){
        return true;
    }
    else{
        return false;
    }
}
