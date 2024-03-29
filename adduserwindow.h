#ifndef ADDUSERWINDOW_H
#define ADDUSERWINDOW_H

#include <QDialog>
#include <QKeyEvent>
#include <QMessageBox>
#include <QSqlQuery>
#include "sql_requests.h"

namespace Ui {
class AddUserWindow;
}

class AddUserWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddUserWindow(QWidget *parent = 0);
    ~AddUserWindow();

    void set_window_options();
    void list_available_groups(int id_role);
    bool code_is_number(const std::string& s);
    bool input_validation();
    int get_id_group();
    bool check_user();
    void add_new_user();
    void clear_input_fields();

private slots:
    void on_comboBox_roles_currentIndexChanged(int index);

    void on_button_add_clicked();

    void on_button_exit_clicked();

    void on_button_help_clicked();

    void on_AddUserWindow_finished(int result);

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::AddUserWindow *ui;
};

#endif // ADDUSERWINDOW_H
