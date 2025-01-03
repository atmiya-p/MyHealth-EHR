#ifndef DOCTORDASHBOARDWINDOW_H
#define DOCTORDASHBOARDWINDOW_H

#include <QDialog>

namespace Ui {
class DoctorDashboardWindow;
}

class DoctorDashboardWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DoctorDashboardWindow(QWidget *parent = nullptr);
    ~DoctorDashboardWindow();

private slots:
    void on_searchpatientButton_clicked();

    void on_addpatientButton_clicked();

    void on_manageappointmentsButton_clicked();

private:
    Ui::DoctorDashboardWindow *ui;
};

#endif // DOCTORDASHBOARDWINDOW_H
