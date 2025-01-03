/**
 * @file searchpatientwindow.cpp
 * @brief Window that doctor has access to search their patients
 *
 *
 * This file is the window that is called when the doctor clicks on the search patient button. This has a text field for where the doctor can enter the healthcard of the patient they would like to search
 *
 * @date November 16, 2024
 */

#include "searchpatientwindow.h"
#include "ui_searchpatientwindow.h"
#include "doctordashboardwindow.h"
#include "Doctor.h"
#include "DBManager.h"
#include "DBPatient.h"
#include "addrecordwindow.h"
#include "recordmanager.h"
#include <QDebug>
#include <QMessageBox>

SearchPatientWindow::SearchPatientWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SearchPatientWindow)
{
    ui->setupUi(this);
    hideAllTheButtons();
    ui->recordsTextEdit->hide();
    ui->closeRecordButton->hide();
    ui->deleteButton->hide();

    Doctor& doctor = Doctor::getInstance();
    qDebug() << "Accessing SearchPatientWindow as Doctor: " << QString::fromStdString(doctor.getUsername());
}

SearchPatientWindow::~SearchPatientWindow()
{
    delete ui;
}

void SearchPatientWindow::on_backButton_clicked()
{
    DoctorDashboardWindow *doctordashboardwindow = new DoctorDashboardWindow(this);
    this->hide();
    doctordashboardwindow->show();
}

void SearchPatientWindow::on_searchButton_clicked()
{
    healthcard = ui->healthcardTextEdit->toPlainText();
    DBPatient dbp("ehr_database.db");
    Doctor& doctor = Doctor::getInstance();

    if (healthcard.isEmpty()) {
        ui->recordsTextEdit->setPlainText("Please enter a health card number.");
        return;
    }

    if (dbp.usernameAndCodeExistInPatient(healthcard.toStdString(), doctor.getUsername())) {
        qDebug() << "Patient exists for health card: " << healthcard;
        showAllTheButtons();
        ui->recordsTextEdit->clear();
    } else {
        QMessageBox::warning(this,"Warning", "The patient with the entered health card does not exist.");
        qDebug() << "Patient does not exist for health card: " << healthcard;
        hideAllTheButtons();
    }
}

void SearchPatientWindow::on_addrecordButton_clicked()
{
    AddRecordWindow *addrecordwindow = new AddRecordWindow(this, healthcard.toStdString());
    this->hide();
    addrecordwindow->show();
}

void SearchPatientWindow::on_deleteButton_clicked()
{
    QMessageBox::information(this, "Information", "We are still figuring this out. By our final deliverable, this will be done");
}

void SearchPatientWindow::on_viewvisithistoryButton_clicked()
{
    if (healthcard.isEmpty()) {
        ui->recordsTextEdit->setPlainText("Please enter a valid health card number.");
        return;
    }

    RecordManager rm("ehr_database.db");
    QString formattedRecords = QString::fromStdString(rm.getFormattedRecordsString(healthcard.toStdString()));

    if (formattedRecords.isEmpty() || formattedRecords == "No records found for the specified patient.") {
        ui->recordsTextEdit->setPlainText("No visit history found for the specified patient.");
    } else {
        ui->recordsTextEdit->setPlainText(formattedRecords);
    }
    ui->recordsTextEdit->show();
    ui->closeRecordButton->show();
}


void SearchPatientWindow::showAllTheButtons() {
    ui->patientfoundlabel->show();
    ui->addrecordButton->show();
    ui->viewvisithistoryButton->show();
}

void SearchPatientWindow::hideAllTheButtons() {
    ui->patientfoundlabel->hide();
    ui->addrecordButton->hide();
    ui->viewvisithistoryButton->hide();
}

void SearchPatientWindow::on_closeRecordButton_clicked()
{
    ui->closeRecordButton->hide();
    ui->recordsTextEdit->hide();
}

