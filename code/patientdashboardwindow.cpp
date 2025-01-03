/**
 * @file patientdashboardwindow.cpp
 * @brief Window that patient gets once they log in. Patients main page
 *
 *
 * This file is the window that is called when the patient successfully logs in. This has buttons that the patient can select what they would like to do
 *
 * @date November 16, 2024
 */

#include "patientdashboardwindow.h"
#include "ui_patientdashboardwindow.h"
#include "DBPatient.h"
#include "Patient.h"
#include "recordmanager.h"
#include <QMessageBox>

PatientDashboardWindow::PatientDashboardWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::PatientDashboardWindow)
{
    setFixedSize(860,600);
    ui->setupUi(this);
    ui->RecordsTextEdit->hide();
    ui->manageappointmentsButton->hide();
}

PatientDashboardWindow::~PatientDashboardWindow()
{
    delete ui;
}

void PatientDashboardWindow::on_viewvisitButton_clicked()
{
    Patient &patient = Patient::getInstance();
    std::string username = patient.getUsername();

    RecordManager rm("ehr_database.db");
    QString formattedRecords = QString::fromStdString(rm.getFormattedRecordsString(username));

    if (formattedRecords.isEmpty() || formattedRecords == "No records found for the specified patient.") {
        ui->RecordsTextEdit->setPlainText("No visit history found.");
    } else {
        ui->RecordsTextEdit->setPlainText(formattedRecords);
    }
    ui->RecordsTextEdit->show();
    ui->closeRecordButton->show();
}


void PatientDashboardWindow::on_closeRecordButton_clicked()
{
    ui->RecordsTextEdit->hide();
    ui->closeRecordButton->hide();
}
