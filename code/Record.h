#ifndef RECORD_H
#define RECORD_H

#include <string>

class RecordBuilder;

class Record {
public:
    static Record createRecord(const std::string& patientID, const std::string& doctorID, const std::string& date, const std::string& notes, const std::string& prescription);

    std::string getPatientID() const;
    std::string getDoctorID() const;
    std::string getDate() const;
    std::string getNotes() const;
    std::string getPrescription() const;

private:
    std::string patientID;
    std::string doctorID;
    std::string date;
    std::string notes;
    std::string prescription;
    friend class RecordBuilder;
};

#endif
