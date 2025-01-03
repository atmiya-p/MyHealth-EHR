/**
 * @file User.cpp
 * @brief Implements the User class to manage user attributes
 *
 * This file provides the implementation of the User class, which represents the base class for different types of users in the system, such as doctors and patients.
 *
 * @date November 16, 2024
 */


#include "User.h"

/**
 * @brief Constructs a User object with a username and password
 *
 * This constructor initializes the User object with the given username and password.
 *
 * @param username - username of the user.
 * @param password - password of the user.
 */
User::User(const std::string& username, const std::string& password)
    : username(username), password(password) {}

/**
 * @brief Getter to get the username of the user.
 *
 * @return The username as a string
 */
std::string User::getUsername() const {
    return username;
}

/**
 * @brief Getter to get the password of the user.
 *
 * @return The password as a string
 */
std::string User::getPassword() const {
    return password;
}

/**
 * @brief Setter to set the username of the user
 *
 * @param username - new username to set
 */
void User::setUsername(const std::string& username) {
    this->username = username;
}

/**
 * @brief Updates the password of the user
 *
 * @param password - new password to set.
 */
void User::setPassword(const std::string& password) {
    this->password = password;
}
