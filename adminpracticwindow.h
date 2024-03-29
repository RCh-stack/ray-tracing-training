#ifndef ADMINPRACTICWINDOW_H
#define ADMINPRACTICWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>

namespace Ui {
class AdminPracticWindow;
}

class AdminPracticWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminPracticWindow(QWidget *parent = 0);
    ~AdminPracticWindow();

    void set_window_options();

    void set_id_work(int id) { id_work = id; }
    int get_id_work() { return id_work; }

private slots:
    void on_button_add_work_clicked();

    void on_button_edit_work_clicked();

    void on_button_check_work_clicked();

    void on_button_statistics_clicked();

    void on_button_help_clicked();

    void on_action_help_triggered();

    void on_action_manual_triggered();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
    Ui::AdminPracticWindow *ui;
    int id_work;
};

#endif // ADMINPRACTICWINDOW_H
