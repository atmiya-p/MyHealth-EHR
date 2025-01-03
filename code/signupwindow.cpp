/**
 * @file signupwindow.cpp
 * @brief Sign up page of the system
 *
 *
 * This file is the window that is the sign up page of the system. Here, the user can sign up if they are allowed to with the verification code they enter
 *
 * @date November 16, 2024
 */

#include "signupwindow.h"
#include "ui_signupwindow.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QString>

SignUpWindow::SignUpWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SignUpWindow)
{
    ui->setupUi(this);

    // Connecting the sign-up button to handleSignupButtonClick
    connect(ui->signupbutton, &QPushButton::clicked, this, &SignUpWindow::handleSignupButtonClick);
}

SignUpWindow::~SignUpWindow()
{
    delete ui;
}

void SignUpWindow::handleSignupButtonClick()
{

    QString username = ui->usernametextEdit->toPlainText();
    QString password = ui->passwordlineEdit->text();
    QString signUpCode = ui->signupcodelineEdit->text();

    bool eightCharactersLong = signUp.passwordValid(password.toStdString());

    if(username.isEmpty()){
        QMessageBox::warning(this, "Failed", "Username cannot be empty. Try again.");
        return;
    }

    if(!eightCharactersLong){
        QMessageBox::warning(this, "Failed", "Password has to be at least 8 characters in length. Try again.");
        return;
    }

    bool success = signUp.registerUser(username.toStdString(), password.toStdString(), signUpCode.toStdString());

    if (success) {
        QMessageBox::information(this, "Success", "Registration successful!");
    } else {
        QMessageBox::warning(this, "Failed", "Registration failed. Please check your details and try again.");
    }
}

void SignUpWindow::on_backButton_clicked()
{
    MainWindow *mainPage = new MainWindow(this);
    this->hide();
    mainPage->show();
}
