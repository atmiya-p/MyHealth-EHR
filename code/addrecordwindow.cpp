/**
 * @file addrecordwindow.cpp
 * @brief Window that doctor has access to add records
 *
 *
 * This file is the window that is called when the doctor clicks on the add record button. This has a list of text fields for where the doctor can enter the visit info (visit date, notes, prescriptions) of the patient they searched for
 *
 * @date November 16, 2024
 */

#include "addrecordwindow.h"
#include "ui_addrecordwindow.h"
#include "searchpatientwindow.h"
#include "recordmanager.h"
#include <QMessageBox>
#include "Doctor.h"

AddRecordWindow::AddRecordWindow(QWidget *parent, const std::string& patientID)
    : QDialog(parent)
    , ui(new Ui::AddRecordWindow)
{
    ui->setupUi(this);
    this->username = patientID;
}

AddRecordWindow::~AddRecordWindow()
{
    delete ui;
}

void AddRecordWindow::on_backButton_clicked()
{
    SearchPatientWindow *searchpatientwindow = new SearchPatientWindow(this);
    this->hide();
    searchpatientwindow->show();
}

void AddRecordWindow::on_addButton_clicked()
{
    QString date = ui->visitdateTextEdit->toPlainText();
    QString appointmentnotes = ui->appointmentnotesTextEdit->toPlainText();
    QString prescriptions = ui->prescriptionsTextEdit->toPlainText();

    qDebug() << "Date:" << date;
    qDebug() << "Appointment Notes:" << appointmentnotes;
    qDebug() << "Prescriptions:" << prescriptions;

    Doctor& doctor = Doctor::getInstance();

    RecordManager rm("ehr_database.db");

    QString visitDate = ui->visitdateTextEdit->toPlainText().trimmed();

    if (visitDate.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "Visit date cannot be empty. Try again.");
        return;
    }

    QString notes = ui->appointmentnotesTextEdit->toPlainText().trimmed();

    if (notes.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "Appointment notes cannot be empty. Try again.");
        return;
    }

    Record record = record.createRecord(username, doctor.getUsername(), date.toStdString(), appointmentnotes.toStdString(), prescriptions.toStdString());
    bool success = rm.addRecord(record);

    if (success) {
        QMessageBox::information(this, "Success", "Record added sucessfully");
    } else {
        QMessageBox::warning(this, "Failed", "Could not add record");
    }
}
