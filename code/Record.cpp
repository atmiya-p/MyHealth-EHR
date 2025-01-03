/**
 * @file Record.cpp
 * @brief Stores the records to be stored in the table
 *
 *
 * This file is used to store the Record as an object when want to add to the records table
 *
 * @date November 16, 2024
 */


#include "Record.h"
#include "RecordBuilder.h"

/**
 * @brief Creates a new Record object using the Builder class with the attributes
 *
 * This method initializes a Record object with the provided patientID,doctorID, date, notes, prescription.
 *
 * @param patientID - healthcard of the patient
 * @param doctorID - username of the doctor
 * @param date - visit date
 * @param notes - patient's visit notes
 * @param prescription - prescription detail
 * @return Record object that is created with RecordBuilder
 */
Record Record::createRecord(const std::string& patientID,const std::string& doctorID, const std::string& date, const std::string& notes, const std::string& prescription) {
    return RecordBuilder()
    .setPatientID(patientID)
        .setDoctorID(doctorID)
        .setDate(date)
        .setNotes(notes)
        .setPrescription(prescription)
        .build();
}

/**
 * @brief Getter to get patient ID of the record
 *
 * @return The patient ID as a string.
 */
std::string Record::getPatientID() const {
    return patientID;
}

/**
 * @brief Getter to get the doctor ID of the record.
 *
 * @return The doctor ID as a string.
 */
std::string Record::getDoctorID() const {
    return doctorID;
}

/**
 * @brief Getter to get the date associated with the record.
 *
 * @return The date as a string.
 */
std::string Record::getDate() const {
    return date;
}

/**
 * @brief Getter to get the notes for the record.
 *
 * @return The note as a string.
 */
std::string Record::getNotes() const {
    return notes;
}

/**
 * @brief Getterm to get the prescription for the record
 *
 * @return The prescription as a string
 */
std::string Record::getPrescription() const {
    return prescription;
}
