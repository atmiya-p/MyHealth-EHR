#ifndef DOCTOR_H
#define DOCTOR_H

#include "User.h"

class Doctor : public User {
public:
    static Doctor& getInstance();

    Doctor(const Doctor&) = delete;
    Doctor& operator=(const Doctor&) = delete;

private:
    Doctor();
};

#endif // DOCTOR_H
