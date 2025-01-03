/**
 * @file addpatientwindow.cpp
 * @brief Window that doctor has access to add patients
 *
 *
 * This file is the window that is called when the doctor clicks on the add patient button. This has a text field for where the doctor can enter the healthcard of the patient they would like to add
 *
 * @date November 16, 2024
 */

#include "addpatientwindow.h"
#include "ui_addpatientwindow.h"
#include "doctordashboardwindow.h"
#include "Patient.h"
#include "DBPatient.h"
#include "Doctor.h"
#include <QMessageBox>

AddPatientWindow::AddPatientWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddPatientWindow)
{
    ui->setupUi(this);
    ui->addedLabel->hide();
}

AddPatientWindow::~AddPatientWindow()
{
    delete ui;
}

void AddPatientWindow::on_backButton_clicked()
{
    DoctorDashboardWindow *doctordashboardwindow = new DoctorDashboardWindow(this);
    this->hide();
    doctordashboardwindow->show();
}

void AddPatientWindow::on_addButton_clicked()
{
    QString healthcard = ui->healthcardTextEdit->toPlainText().trimmed();

    if (healthcard.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "Health card number cannot be empty. Try again.");
        return;
    }

    Doctor& doctor = Doctor::getInstance();
    std::string doctorUsername = doctor.getUsername();

    DBPatient dbp("ehr_database.db");
    if(dbp.insertPatient(healthcard.toStdString(), doctorUsername)){
        ui->addedLabel->show();
    }
    else{
        ui->addedLabel->hide();
        QMessageBox::warning(this, "Failed", "The patient could not be added.");
    }


    qDebug() << "Patient added for doctor: " << QString::fromStdString(doctorUsername);
}
