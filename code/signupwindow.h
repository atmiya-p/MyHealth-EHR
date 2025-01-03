#ifndef SIGNUPWINDOW_H
#define SIGNUPWINDOW_H

#include <QDialog>
#include "SignUp.h"

namespace Ui {
class SignUpWindow;
}

class SignUpWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SignUpWindow(QWidget *parent = nullptr);
    ~SignUpWindow();

private slots:
    void handleSignupButtonClick();
    void on_backButton_clicked();

private:
    Ui::SignUpWindow *ui;
    SignUp signUp;  // Instance of SignUp to handle registration logic
};

#endif // SIGNUPWINDOW_H
