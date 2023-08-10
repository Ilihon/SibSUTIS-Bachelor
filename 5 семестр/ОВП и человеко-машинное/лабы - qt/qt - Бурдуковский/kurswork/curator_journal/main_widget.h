#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include <QMainWindow>
#include <QWidget>
#include <QDebug>
#include <QString>
#include <QCloseEvent>
#include <QTextEdit>
#include <QFileDialog>
#include <QTextStream>
#include <QColorDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <QTSql>
#include <QStandardItem>
#include "ui_main_widget.h"

namespace Ui {
class Main_Widget;
}

class Main_Widget : public QWidget
{
    Q_OBJECT

public slots:
    void on_SignInButton_clicked();
    void on_SignOutButton_clicked();
    void on_SwtchWidgetButton_clicked();
    void on_EditGroupButton_clicked();

    void on_AddStudAllButton_clicked();
    void on_DeleteStudAllButton_clicked();
    void on_SaveTableAllButton_clicked();
    void on_ReturnTableAllButton_clicked();

    void on_AddGroupButton_clicked();
    void on_DeleteGroupButton_clicked();
    void on_SaveTableGroupButton_clicked();
    void on_ReturnTableGroupButton_clicked();

    void on_AddSubjButton_clicked();
    void on_DeleteSubjButton_clicked();
    void on_SaveTableSubjButton_clicked();
    void on_ReturnTableSubjButton_clicked();

    void on_BirthdayText_change();
    void on_PhoneText_change();
    void on_EmailText_change();
    void on_ExtraInfoText_change();
    void on_LoadImageButton_clicked();

    void on_AddGroupSubjButton_clicked();
    void on_DeleteGroupSubjButton_clicked();
    void on_SaveTableGroupSubjButton_clicked();
    void on_ReturnTableGroupSubjButton_clicked();

    void on_AddClassButton_clicked();
    void on_DeleteClassButton_clicked();
    void on_SaveTableClassButton_clicked();
    void on_ReturnTableClassButton_clicked();

    void UpdateStudentInfo();
    void UpdateAllGroupsInfo();

    void FillGroupSubjTable();

    void closeEvent(QCloseEvent *event);

public:
    explicit Main_Widget(QWidget *parent = 0);
    ~Main_Widget();
    void FillAllStudTable();
    void FillAllGroupTable();
    void FillSubjTable();
    void FillClassTable(QString table_name);

    void FillGroupComboBox();

private slots:
    void on_comboBox_group_currentIndexChanged(int index);

    void on_comboBox_subject_currentIndexChanged(const QString &arg1);

private:
    Ui::Main_Widget *ui;
    QSqlDatabase db;
    QSqlTableModel *model_all_stud;
    QSqlTableModel *model_all_groups;
    QSqlTableModel *model_subj;
    QSqlTableModel *model_group_subj;
    QSqlTableModel *model_current_group_subj;

    //int AllGroupsCount;
    int added_row_index = 0;
    int added_group_row_index = 0;
    int added_group_subj_row_index = 0;

    int selected_row_index = 0;
    int selected_group_row_index = 0;
    QString current_class_table_name;
    QIcon favicon = QIcon("D:\\labs\\qt\\kurswork\\curator_journal\\Base\\favicon.png");
};

#endif // MAIN_WIDGET_H
