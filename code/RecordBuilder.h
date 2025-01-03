#ifndef RECORDBUILDER_H
#define RECORDBUILDER_H

#include <string>
#include "Record.h"

class RecordBuilder {
private:
    Record record;
public:
    RecordBuilder& setPatientID(const std::string& pid);
    RecordBuilder& setDoctorID(const std::string& did);
    RecordBuilder& setDate(const std::string& d);
    RecordBuilder& setNotes(const std::string& n);
    RecordBuilder& setPrescription(const std::string& p);
    Record build();
};

#endif // RECORDBUILDER_H
