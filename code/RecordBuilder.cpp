/**
 * @file RecordBuilder.cpp
 * @brief Implementation of the RecordBuilder class.
 *
 * This class uses the Builder pattern to construct Record objects
 *
 * @date November 16, 2024
 */

#include "RecordBuilder.h"

RecordBuilder& RecordBuilder::setPatientID(const std::string& pid) {
    record.patientID = pid;
    return *this;
}

RecordBuilder& RecordBuilder::setDoctorID(const std::string& did) {
    record.doctorID = did;
    return *this;
}

RecordBuilder& RecordBuilder::setDate(const std::string& d) {
    record.date = d;
    return *this;
}

RecordBuilder& RecordBuilder::setNotes(const std::string& n) {
    record.notes = n;
    return *this;
}

RecordBuilder& RecordBuilder::setPrescription(const std::string& p) {
    record.prescription = p;
    return *this;
}

Record RecordBuilder::build() {
    return record;
}
