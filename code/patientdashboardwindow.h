#ifndef PATIENTDASHBOARDWINDOW_H
#define PATIENTDASHBOARDWINDOW_H

#include <QDialog>

namespace Ui {
class PatientDashboardWindow;
}

class PatientDashboardWindow : public QDialog
{
    Q_OBJECT

public:
    explicit PatientDashboardWindow(QWidget *parent = nullptr);
    ~PatientDashboardWindow();

private slots:
    void on_viewvisitButton_clicked();

    void on_closeRecordButton_clicked();

private:
    Ui::PatientDashboardWindow *ui;
};

#endif // PATIENTDASHBOARDWINDOW_H
