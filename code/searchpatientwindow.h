#ifndef SEARCHPATIENTWINDOW_H
#define SEARCHPATIENTWINDOW_H

#include <QDialog>

namespace Ui {
class SearchPatientWindow;
}

class SearchPatientWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SearchPatientWindow(QWidget *parent = nullptr);
    ~SearchPatientWindow();

private slots:
    void on_backButton_clicked();

    void on_addrecordButton_clicked();

    void on_deleteButton_clicked();

    void on_viewvisithistoryButton_clicked();

    void on_searchButton_clicked();

    void on_closeRecordButton_clicked();

private:
    Ui::SearchPatientWindow *ui;
    void showAllTheButtons();
    void hideAllTheButtons();
    QString healthcard;
};

#endif // SEARCHPATIENTWINDOW_H
