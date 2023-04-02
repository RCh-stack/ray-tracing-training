#include "changepracticwindow.h"
#include "ui_changepracticwindow.h"
#include "editingtoolswindow.h"

ChangePracticWindow::ChangePracticWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePracticWindow)
{
    ui->setupUi(this);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Program Files (x86)/Qt Project/RayTracing/EducationSystem.sqlite");

    if (!db.open())
        QMessageBox::critical(this, "Ошибка", db.lastError().text());

    set_window_options();
    set_default_options();
}

ChangePracticWindow::~ChangePracticWindow()
{
    delete ui;
}

// 1.6
void ChangePracticWindow::set_window_options()
{
    QPixmap generation(":/icons/images/generation-attributes-button.png");
    QPixmap edit(":/icons/images/edit-work-button.png");
    QPixmap close(":/icons/images/exit-button.png");
    QPixmap help(":/icons/images/help-button.png");
    QPixmap options(":/icons/images/edit-lab-button.png");

    QIcon ButtonGeneration(generation);
    QIcon ButtonEdit(edit);
    QIcon ButtonClose(close);
    QIcon ButtonInformation(help);
    QIcon ButtonOptions(options);

    ui->button_generation->setIcon(ButtonGeneration);
    ui->button_edit->setIcon(ButtonEdit);
    ui->button_exit->setIcon(ButtonClose);
    ui->button_help->setIcon(ButtonInformation);
    ui->button_options->setIcon(ButtonOptions);

    QPixmap bkgnd(":/icons/images/mainwindow_background.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio);
    QPalette p = palette();
    p.setBrush(QPalette::Background, bkgnd);
    setPalette(p);
}

// 1.6
void ChangePracticWindow::set_default_options()
{
    ui->text_number->setEnabled(0);
    ui->text_path->setEnabled(0);

    QFont font("Times New Roman", 12);
    ui->text_work->setFont(font);
    ui->html_work->setFont(font);
}

// 1.6
void ChangePracticWindow::get_data_from_db()
{
    QSqlQuery query;
    query.prepare("");
    query.bindValue(":id_theme",    get_id_work());

    query.exec();

    if(query.next())
    {
        set_name_theme(query.value("Name").toString());
        //set_name_file...
        set_path_file(query.value("Path").toString());
    }

    output_data();
}

// 1.6
void ChangePracticWindow::output_data()
{
    ui->text_name_file->setText(""); // !!!
    ui->text_name_work->setText(get_name_theme());
    ui->text_number->setText(QString::number(get_id_work()));
    ui->text_path->setText(get_path_file());
}

// 1.6
void ChangePracticWindow::on_text_work_textChanged()
{
    QString current_text = ui->text_work->toPlainText();
    ui->html_work->setText(current_text);
}

// 1.6
void ChangePracticWindow::edit_file_in_database()
{
    QSqlQuery query;
    query.prepare(update_theme_work());
    query.bindValue(":id_theme",        ui->text_number->text().simplified());
    query.bindValue(":name_theme",  ui->text_name_work->text().simplified());
    query.bindValue(":path",               ui->text_path->text().simplified());

    query.exec();

    QMessageBox::information(this, "Уведомление", "Лабораторная работа изменена.");
}

// 1.6
void ChangePracticWindow::on_button_generation_clicked()
{
    QString id_num_page = QString::number(get_id_work());
    ui->text_number->setText(id_num_page);
    ui->text_path->setText("/files/lab/");

    if(ui->text_name_file->text().simplified().length() == 0)
        ui->text_name_file->setText("filename");

    if(ui->text_name_work->text().simplified().length() == 0)
        ui->text_name_work->setText("Лабораторная работа №" + id_num_page);
}

// 1.6
void ChangePracticWindow::on_button_edit_clicked()
{
    if(ui->text_name_file->text().length() == 0)
        QMessageBox::critical(this, "Уведомление", "Не заполнено поле с наименованием файла!");
    else if(ui->text_name_work->text().length() == 0)
        QMessageBox::critical(this, "Уведомление", "Не заполнено поле с наименованием работы!");
    else if(ui->text_number->text().length() == 0)
        QMessageBox::critical(this, "Уведомление", "Не заполнено поле с номером страницы!");
    else
        edit_file_in_database();
}

void ChangePracticWindow::on_button_options_clicked()
{
    EditingToolsWindow *etw = new EditingToolsWindow;
    etw->setWindowFlags(Qt::MSWindowsFixedSizeDialogHint);
    etw->exec();

    //set_name_font(etw->get_name_font());
    //set_id_font_color(etw->get_id_font_color());
    //set_size_font(etw->get_size_font());

    etw->deleteLater();

    //set_font_options();
}

void ChangePracticWindow::on_button_help_clicked()
{

}

// 1.6
void ChangePracticWindow::on_button_exit_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Уведомление", "Вы уверены, что хотите закрыть окно?\nНесохраненные данные будут потеряны.",
                                  QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes)
        this->close();
}