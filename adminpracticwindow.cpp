#include "adminpracticwindow.h"
#include "ui_adminpracticwindow.h"
#include "checkpracticworkwindow.h"
#include "createpracticwindow.h"
#include "changepracticwindow.h"
#include "openpracticfile.h"

AdminPracticWindow::AdminPracticWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminPracticWindow)
{
    ui->setupUi(this);

    set_window_options();
}

AdminPracticWindow::~AdminPracticWindow()
{
    delete ui;
}

// 1.6
void AdminPracticWindow::set_window_options()
{
    QPixmap add(":/icons/images/add-work-button.png");
    QPixmap edit(":/icons/images/edit-work-button.png");
    QPixmap stats(":/icons/images/stats-users-button.png");
    QPixmap check(":/icons/images/check-work-button.png");
    QPixmap help(":/icons/images/help-button.png");

    QIcon ButtonAdd(add);
    QIcon ButtonEdit(edit);
    QIcon ButtonStats(stats);
    QIcon ButtonCheck(check);
    QIcon ButtonInformation(help);

    ui->button_add_work->setIcon(ButtonAdd);
    ui->button_edit_work->setIcon(ButtonEdit);
    ui->button_check_work->setIcon(ButtonCheck);
    ui->button_statistics->setIcon(ButtonStats);
    ui->button_help->setIcon(ButtonInformation);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

// 1.6
void AdminPracticWindow::on_button_add_work_clicked()
{
    CreatePracticWindow *cpw = new CreatePracticWindow;
    cpw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    cpw->exec();
    cpw->deleteLater();
}

// 1.6
void AdminPracticWindow::on_button_edit_work_clicked()
{
    OpenPracticFile *opf = new OpenPracticFile;
    opf->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    opf->output_data();
    opf->exec();

    set_id_work(opf->get_id_work());
    opf->deleteLater();

    ChangePracticWindow *cpw = new ChangePracticWindow;
    cpw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    //cpw->set_id_work(get_id_work());
    //cpw->output_data_in_file...
    cpw->exec();

    cpw->deleteLater();
}

// 1.6
void AdminPracticWindow::on_button_check_work_clicked()
{
    CheckPracticWorkWindow *cpww = new CheckPracticWorkWindow;
    cpww->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    cpww->output_data_to_form();

    cpww->exec();
    cpww->deleteLater();
}

void AdminPracticWindow::on_button_statistics_clicked()
{

}

void AdminPracticWindow::on_button_help_clicked()
{

}

void AdminPracticWindow::on_action_current_statuses_triggered()
{

}

void AdminPracticWindow::on_action_help_triggered()
{

}

void AdminPracticWindow::on_action_manual_triggered()
{

}

// 1.6
void AdminPracticWindow::on_action_list_works_triggered()
{
    OpenPracticFile *opf = new OpenPracticFile;
    opf->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    opf->exec();

    // dont selected ...

    opf->deleteLater();

}
