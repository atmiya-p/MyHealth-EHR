/**
 * @file mainwindow.cpp
 * @brief Log in page of the system
 *
 *
 * This file is the window that is the log in page of the system. Here, the user can log in and must specify if they are signing in as a doctor or patient.
 *
 * @date November 16, 2024
 */


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signupwindow.h"
#include "DBManager.h"
#include "User.h"
#include "Doctor.h"
#include "patientdashboardwindow.h"
#include "doctordashboardwindow.h"
#include <QMessageBox>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setFixedSize(860, 600);
    ui->setupUi(this);
    connect(ui->showPassword, &QCheckBox::toggled, this, &MainWindow::showPassword);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked() {
    QString username = ui->usernametextEdit->toPlainText();
    QString password = ui->passwordlineEdit->text();

    QString role;
    if (ui->doctorRadioButton->isChecked()) {
        role = "DOCTOR";
    } else if (ui->patientRadioButton->isChecked()) {
        role = "PATIENT";
    } else {
        QMessageBox::warning(this, "Selection Required", "Please select whether you are a doctor or patient.");
        return;
    }

    DBManager dbManager("ehr_database.db");
    bool validLogin = dbManager.verifyLogin(username.toStdString(), password.toStdString(), role.toStdString());

    if (validLogin) {
        if (role == "DOCTOR") {
            Doctor& doctor = Doctor::getInstance();
            doctor.setUsername(username.toStdString());
            doctor.setPassword(password.toStdString());

            DoctorDashboardWindow *dashboard = new DoctorDashboardWindow(this);
            this->close();
            dashboard->show();
        } else if (role == "PATIENT") {
            Patient &patient = Patient::getInstance();
            patient.setUsername(username.toStdString());
            patient.setPassword(password.toStdString());

            PatientDashboardWindow *dashboard = new PatientDashboardWindow(this);
            this->close();
            dashboard->show();
        }
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
    }
}


void MainWindow::showPassword(bool checked) {
    if (checked) {
        ui->passwordlineEdit->setEchoMode(QLineEdit::Normal);
    } else {
        ui->passwordlineEdit->setEchoMode(QLineEdit::Password);
    }
}

void MainWindow::on_commandLinkButton_clicked() {
    SignUpWindow *signUpPage = new SignUpWindow(this);
    this->hide();
    signUpPage->show();
}
