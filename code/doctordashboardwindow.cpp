/**
 * @file doctordashboardwindow.cpp
 * @brief Window that doctor gets once they log in. Doctors main page
 *
 *
 * This file is the window that is called when the doctor successfully logs in. This has buttons that the doctor can select what they would like to do
 *
 * @date November 16, 2024
 */


#include "doctordashboardwindow.h"
#include "ui_doctordashboardwindow.h"
#include "searchpatientwindow.h"
#include "addpatientwindow.h"
#include <QMessageBox>

DoctorDashboardWindow::DoctorDashboardWindow(QWidget *parent)
    : QDialog(parent), ui(new Ui::DoctorDashboardWindow)
{
    ui->setupUi(this);
    ui->manageappointmentsButton->hide();
}

DoctorDashboardWindow::~DoctorDashboardWindow()
{
    delete ui;
}

void DoctorDashboardWindow::on_searchpatientButton_clicked()
{
    SearchPatientWindow *searchpatientwindow = new SearchPatientWindow(this);
    this->hide();
    searchpatientwindow->show();
}

void DoctorDashboardWindow::on_addpatientButton_clicked()
{
    AddPatientWindow *addpatientwindow = new AddPatientWindow(this);
    this->hide();
    addpatientwindow->show();
}

void DoctorDashboardWindow::on_manageappointmentsButton_clicked()
{
    QMessageBox::information(this, "Information", "We are still figuring this out. By our final deliverable, this will be done");
}

