/**
 * @file Doctor.cpp
 * @brief Implements the Singleton design pattern for the Doctor class
 *
 * @extends User.cpp
 *
 * This file provides the implementation of the Doctor class, which extends the User class. The Doctor class follows the Singleton pattern to ensure only one instance exists when the app is run
 *
 * @date November 16, 2024
 */

#include "Doctor.h"

/**
 * @brief Retrieves the single instance of the Doctor class.
 *
 * This method ensures that only one instance of the Doctor class is created. Singleton Design Pattern
 *
 * @return Reference to the single instance of the Doctor class.
 */
Doctor& Doctor::getInstance() {
    static Doctor instance;
    return instance;
}

/**
 * @brief Constructs a Doctor object
 *
 * The constructor initializes the Doctor object with default username and password
 */
Doctor::Doctor() : User("", "") {}
