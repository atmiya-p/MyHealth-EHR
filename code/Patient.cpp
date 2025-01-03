/**
 * @file Patient.cpp
 * @brief Implements the Singleton design pattern for the Patient class
 *
 * @extends User.cpp
 *
 * This file provides the implementation of the Patient class, which extends the User class. The Patient class follows the Singleton pattern to ensure only one instance exists when the app is run
 *
 * @date November 16, 2024
 */

#include "Patient.h"

/**
 * @brief Retrieves the single instance of the Patient class
 *
 * This method ensures that only one instance of the Patient class is created.
 *
 * @return Reference to the single instance of the Patient class.
 */
Patient& Patient::getInstance() {
    static Patient instance;
    return instance;
}

/**
 * @brief Constructs a Patient object with username, password, and verification code.
 *
 * This constructor initializes the Patient object with user-specific details, including the username, password, and verification code.
 *
 * @param username - patient's username.
 * @param password - patient's password.
 * @param verificationCode - patient's verification code.
 */
Patient::Patient(const std::string& username, const std::string& password, const std::string& verificationCode)
    : User(username, password), verificationCode(verificationCode) {}

/**
 * @brief Sets the patient details including username, password, and verification code.
 *
 * This method updates the attributes of the Patient instance
 *
 * @param username - patient's username.
 * @param password - patient's password.
 * @param verificationCode - patient's verification code.
 */
void Patient::setPatient(const std::string& username, const std::string& password, const std::string& verificationCode) {
    this->username = username;
    this->password = password;
    this->verificationCode = verificationCode;
}

/**
 * @brief Retrieves the patient's verification code
 *
 * This method provides access to the patient's verification code
 *
 * @return A string representing the patient's verification code
 */
std::string Patient::getVerificationCode() const {
    return verificationCode;
}
