#ifndef ADDRECORDWINDOW_H
#define ADDRECORDWINDOW_H

#include <QDialog>
#include <string>

namespace Ui {
class AddRecordWindow;
}

class AddRecordWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddRecordWindow(QWidget *parent = nullptr, const std::string& patientID = "");
    ~AddRecordWindow();

private slots:
    void on_backButton_clicked();
    void on_addButton_clicked();

private:
    Ui::AddRecordWindow *ui;
    std::string username;
};

#endif // ADDRECORDWINDOW_H
