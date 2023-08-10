#include "main_widget.h"
#include "mydatabase.h"

Main_Widget::Main_Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Main_Widget)
{

    myDataBase *mdb = new myDataBase();
    mdb->Connection();

    ui->setupUi(this);
    this->resize(200,130);
    this->setMinimumSize(200,130);
    this->setMaximumSize(200,130);
    ui->stackedWidget->setCurrentIndex(0);

    db = mdb->mydb;

    connect(ui->pushButton_SignIn, SIGNAL(clicked(bool)), this, SLOT(on_SignInButton_clicked()));
    connect(ui->pushButton_SignOut, SIGNAL(clicked(bool)), this, SLOT(on_SignOutButton_clicked()));
    connect(ui->pushButton_SwitchWidget, SIGNAL(clicked(bool)), this, SLOT(on_SwtchWidgetButton_clicked()));
    connect(ui->pushButton_GroupControl, SIGNAL(clicked(bool)), this, SLOT(on_EditGroupButton_clicked()));

    connect(ui->pushButton_AddStud_All, SIGNAL(clicked(bool)), this, SLOT(on_AddStudAllButton_clicked()));
    connect(ui->pushButton_DeleteStud_All, SIGNAL(clicked(bool)), this, SLOT(on_DeleteStudAllButton_clicked()));
    connect(ui->pushButton_AddGroup, SIGNAL(clicked(bool)), this, SLOT(on_AddGroupButton_clicked()));
    connect(ui->pushButton_DeleteGroup, SIGNAL(clicked(bool)), this, SLOT(on_DeleteGroupButton_clicked()));
    connect(ui->pushButton_AddSubj, SIGNAL(clicked(bool)), this, SLOT(on_AddSubjButton_clicked()));
    connect(ui->pushButton_DeleteSubj, SIGNAL(clicked(bool)), this, SLOT(on_DeleteSubjButton_clicked()));
    connect(ui->pushButton_AddGroupSubj, SIGNAL(clicked(bool)), this, SLOT(on_AddGroupSubjButton_clicked()));
    connect(ui->pushButton_DeleteGroupSubj, SIGNAL(clicked(bool)), this, SLOT(on_DeleteGroupSubjButton_clicked()));
    connect(ui->pushButton_AddClass, SIGNAL(clicked(bool)), this, SLOT(on_AddClassButton_clicked()));
    connect(ui->pushButton_DeleteClass, SIGNAL(clicked(bool)), this, SLOT(on_DeleteClassButton_clicked()));

    connect(ui->pushButton_SaveTable_All, SIGNAL(clicked(bool)), this, SLOT(on_SaveTableAllButton_clicked()));
    connect(ui->pushButton_ReturnTable_All, SIGNAL(clicked(bool)), this, SLOT(on_ReturnTableAllButton_clicked()));
    connect(ui->pushButton_SaveTable_Group, SIGNAL(clicked(bool)), this, SLOT(on_SaveTableGroupButton_clicked()));
    connect(ui->pushButton_ReturnTable_Group, SIGNAL(clicked(bool)), this, SLOT(on_ReturnTableGroupButton_clicked()));
    connect(ui->pushButton_SaveTable_Subj, SIGNAL(clicked(bool)), this, SLOT(on_SaveTableSubjButton_clicked()));
    connect(ui->pushButton_ReturnTable_Subj, SIGNAL(clicked(bool)), this, SLOT(on_ReturnTableSubjButton_clicked()));
    connect(ui->pushButton_SaveTable_GroupSubj, SIGNAL(clicked(bool)), this, SLOT(on_SaveTableGroupSubjButton_clicked()));
    connect(ui->pushButton_ReturnTable_GroupSubj, SIGNAL(clicked(bool)), this, SLOT(on_ReturnTableGroupSubjButton_clicked()));
    connect(ui->pushButton_SaveClass, SIGNAL(clicked(bool)), this, SLOT(on_SaveTableClassButton_clicked()));
    connect(ui->pushButton_ReturnClass, SIGNAL(clicked(bool)), this, SLOT(on_ReturnTableClassButton_clicked()));


    connect(ui->dateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(on_BirthdayText_change()));
    connect(ui->plainTextEdit_phone_number, SIGNAL(textChanged()), this, SLOT(on_PhoneText_change()));
    connect(ui->plainTextEdit_email, SIGNAL(textChanged()), this, SLOT(on_EmailText_change()));
    connect(ui->textEdit_extra_info, SIGNAL(textChanged()), this, SLOT(on_ExtraInfoText_change()));
    connect(ui->pushButton_load_Image, SIGNAL(clicked(bool)), this, SLOT(on_LoadImageButton_clicked()));
}

void Main_Widget::FillGroupSubjTable(){
    qDebug() << "Filling subjects table for group";
    int row_index=0;
    if(ui->tableView_all_group->selectionModel()->hasSelection())
    {
        row_index = ui->tableView_all_group->selectionModel()->currentIndex().row();
    }
    qDebug() << row_index << " - " << ui->tableView_all_group->model()->rowCount() << " - " << ui->lwGroups->count();
    //if(row_index<ui->tableView_all_group->model()->rowCount()){
    if(row_index >= ui->lwGroups->count()){
        return;
    }
    selected_group_row_index = row_index;
    QString group_name = model_all_groups->index(selected_group_row_index,1).data().toString();
    QString table_name = "SubjectsFor_"+ group_name;
    model_group_subj = new QSqlTableModel();
    model_group_subj->setTable(table_name);
    model_group_subj->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_group_subj->setHeaderData(1, Qt::Horizontal, tr("Предметы ")+group_name);
    model_group_subj->select();
    ui->tableView_GroupSubj->setModel(model_group_subj);
    ui->tableView_GroupSubj->setColumnHidden(0,true);
    ui->tableView_GroupSubj->resizeRowsToContents();
    ui->tableView_GroupSubj->resizeColumnsToContents();
    ui->tableView_GroupSubj->setSortingEnabled(true);               // Сортировка таблицы
    ui->tableView_GroupSubj->sortByColumn(0,Qt::AscendingOrder);    // Порядок сортировки по умолчанию
    ui->tableView_GroupSubj->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
}

void Main_Widget::FillGroupComboBox() {
    qDebug() << "filling group combo box";
    model_all_groups->sort(1, Qt::AscendingOrder);
    ui->comboBox_group->clear();
    ui->comboBox_group->addItem("Выбор группы");
    for(int i=0; i<model_all_groups->rowCount(); i++){
        ui->comboBox_group->addItem(model_all_groups->index(i,1).data().toString());
    }
    model_all_groups->sort(0, Qt::AscendingOrder);
}

void Main_Widget::on_comboBox_subject_currentIndexChanged(const QString &arg1)
{
    int cur_index_group = ui->comboBox_group->currentIndex();
    int cur_index_subj = ui->comboBox_subject->currentIndex();
    qDebug() << "switch subject combo box";
    qDebug() << cur_index_group << " - " << cur_index_subj;
    if(cur_index_group<=0){
        ui->tableView->setModel(NULL);
        return;
    }
    if(cur_index_subj<=0){
        ui->tableView->setModel(NULL);
        return;
    }
    QString group_name = ui->comboBox_group->itemText(cur_index_group);
    QString subject_name = arg1;
    QString table_name = "Subj_" + group_name + "_" + subject_name;
    current_class_table_name = table_name;
    qDebug() << table_name;


    this->FillClassTable(table_name);
    qDebug() << "start filling " << group_name << " tableview";

    //удаление из таблицы пары студентов, которых не существует
    int n = model_current_group_subj->rowCount();
    int size = model_all_stud->rowCount();
    for (int i = 0; i < n; i++){
        size = model_all_stud->rowCount();
        bool flag = true;
        for(int j = 0; j < size; j++){
            if(model_all_stud->index(j,2).data().toString() == group_name){
                QString enter_name = model_all_stud->index(j,1).data().toString();
                QString enter_status = model_all_stud->index(j,3).data().toString();
                qDebug() << "enter name = "<< enter_name;
                qDebug() << "enter status = "<< enter_status;
                if((model_current_group_subj->index(i,1).data().toString() == enter_name) &&
                        (model_current_group_subj->index(i,2).data().toString() == enter_status)){
                    flag =false;
                }
            }
        }
        if(flag){
            model_current_group_subj->removeRow(i);
            model_current_group_subj->submitAll();
            i--;
            n--;
        }
    }
    //------------------

    //вставка в таблицу пары соответствующих студентов, если их там нет
    size = model_all_stud->rowCount();
    for (int i = 0; i < size;i++){
        if(model_all_stud->index(i,2).data().toString() == group_name){
            QString enter_name = model_all_stud->index(i,1).data().toString();
            QString enter_status = model_all_stud->index(i,3).data().toString();
            qDebug() << "enter name = "<< enter_name;
            qDebug() << "enter status = "<< enter_status;

            n = model_current_group_subj->rowCount();
            qDebug() << "n = "<< n;
            bool flag = true;
            for(int j = 0; j<n; j++){
                if((model_current_group_subj->index(j,1).data().toString() == enter_name) &&
                        (model_current_group_subj->index(j,2).data().toString() == enter_status)){
                    flag =false;
                }
            }
            if(flag){
                qDebug() << "Add to tableView new row";
                model_current_group_subj->insertRow(n); //добавляем строку, без сохранения она не запишется в бд
                model_current_group_subj->setData(model_current_group_subj->index(n,1), enter_name);
                model_current_group_subj->setData(model_current_group_subj->index(n,2), enter_status);
                model_current_group_subj->submitAll();
            }
        }
    }
    //------------------
}

void Main_Widget::FillClassTable(QString table_name){
    model_current_group_subj = new QSqlTableModel();
    model_current_group_subj->setTable(table_name);
    model_current_group_subj->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_current_group_subj->setHeaderData(1, Qt::Horizontal, tr("ФИО студента"));
    model_current_group_subj->setHeaderData(2, Qt::Horizontal, tr("Статус"));
    if(model_current_group_subj->columnCount()>3){
        int size = model_current_group_subj->columnCount();
        for(int i=3; i < size; i++){
            QString normalize_date = model_current_group_subj->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString();
            normalize_date.remove(0,5);
            normalize_date.replace("_",".");
            qDebug() << normalize_date;
            model_current_group_subj->setHeaderData(i, Qt::Horizontal, normalize_date);
            model_current_group_subj->submitAll();
        }
    }
    model_current_group_subj->select();

    ui->tableView->setModel(model_current_group_subj);
    ui->tableView->setColumnHidden(0,true);
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setSortingEnabled(true);               // Сортировка таблицы
    ui->tableView->sortByColumn(0,Qt::AscendingOrder);    // Порядок сортировки по умолчанию
}

void Main_Widget::on_comboBox_group_currentIndexChanged(int cur_index)
{
    qDebug() << "filling subject combo box";
    qDebug() << cur_index;
    if(cur_index<=0){
        ui->comboBox_subject->setCurrentIndex(0);
        ui->tableView->setModel(NULL);
        return;
    }
    QString group_name = ui->comboBox_group->itemText(cur_index);
    QString table_name = "SubjectsFor_"+ group_name;

    QSqlTableModel *model_buffer;
    model_buffer = new QSqlTableModel();
    model_buffer->setTable(table_name);
    model_buffer->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_buffer->sort(1, Qt::AscendingOrder);
    model_buffer->select();

    ui->comboBox_subject->clear();
    ui->comboBox_subject->addItem("Выбор предмета");
    for(int i = 0; i<model_buffer->rowCount(); i++){
        ui->comboBox_subject->addItem(model_buffer->index(i,1).data().toString());
    }
    model_buffer->sort(0, Qt::AscendingOrder);
}

void Main_Widget::FillAllStudTable() {
    qDebug() << "refreshing all students table";
    model_all_stud = new QSqlTableModel();
    model_all_stud->setTable("AllStudents");
    model_all_stud->setEditStrategy(QSqlTableModel::OnManualSubmit);

    model_all_stud->setHeaderData(1, Qt::Horizontal, tr("ФИО студента"));
    model_all_stud->setHeaderData(2, Qt::Horizontal, tr("Группа"));
    model_all_stud->setHeaderData(3, Qt::Horizontal, tr("Статус"));
    model_all_stud->select();
    ui->tableView_all_stud->setModel(model_all_stud);

    ui->tableView_all_stud->setColumnHidden(0,true);
    for(int i = 4; i<10;i++){
        ui->tableView_all_stud->setColumnHidden(i,true);
    }
    ui->tableView_all_stud->resizeRowsToContents();
    ui->tableView_all_stud->resizeColumnsToContents();
    ui->tableView_all_stud->setSortingEnabled(true);               // Сортировка таблицы
    ui->tableView_all_stud->sortByColumn(0,Qt::AscendingOrder);    // Порядок сортировки по умолчанию
    ui->tableView_all_stud->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    connect(ui->tableView_all_stud->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(UpdateStudentInfo()));
    this->UpdateStudentInfo();
}

void Main_Widget::UpdateStudentInfo()
{
    qDebug() << "updating selected student info";
    int row_index=0;
    if(ui->tableView_all_stud->selectionModel()->hasSelection())
    {
        row_index = ui->tableView_all_stud->selectionModel()->currentIndex().row();
    }
    selected_row_index = row_index;
    //считываем значения выбранной строки
    QString selected_date = model_all_stud->index(selected_row_index,5).data().toString();
    QDate date = QDate::fromString(selected_date,"dd.MM.yyyy");
    QString selected_phone = model_all_stud->index(selected_row_index,6).data().toString();
    QString selected_email = model_all_stud->index(selected_row_index,7).data().toString();
    QString selected_photo = model_all_stud->index(selected_row_index,8).data().toString();
    QImage image(selected_photo);
    QString selected_ExtraInfo = model_all_stud->index(selected_row_index,9).data().toString();
    //обновляем инфу о студентах
    ui->dateEdit->setDate(date);
    ui->plainTextEdit_phone_number->setPlainText(selected_phone);
    ui->plainTextEdit_email->setPlainText(selected_email);
    ui->label_photo->setPixmap(QPixmap::fromImage(image));
    ui->textEdit_extra_info->setText(selected_ExtraInfo);
}

void Main_Widget::FillAllGroupTable() {
    qDebug() << "refreshing all groups table";
    model_all_groups = new QSqlTableModel();
    model_all_groups->setTable("AllGroups");
    model_all_groups->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_all_groups->setHeaderData(1, Qt::Horizontal, tr("Группа"));
    model_all_groups->sort(0, Qt::AscendingOrder);
    model_all_groups->select();

    ui->tableView_all_group->setModel(model_all_groups);
    ui->tableView_all_group->setColumnHidden(0,true);
    ui->tableView_all_group->resizeRowsToContents();
    ui->tableView_all_group->resizeColumnsToContents();
    ui->tableView_all_group->setSortingEnabled(true);               // Сортировка таблицы
    ui->tableView_all_group->sortByColumn(0,Qt::AscendingOrder);    // Порядок сортировки по умолчанию
    ui->tableView_all_group->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    connect(ui->tableView_all_group->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), this, SLOT(FillGroupSubjTable()));
    this->UpdateAllGroupsInfo();
}

void Main_Widget::UpdateAllGroupsInfo(){
    qDebug() << "updating groups list";
    ui->lwGroups->clear();
    for(int i=0; i<model_all_groups->rowCount(); i++){
        bool flag = true;
        for(int j=0; j < ui->lwGroups->count(); j++){
            if(ui->lwGroups->item(j)->text() == model_all_groups->index(i,1).data().toString()){
                flag = false;
            }
        }
        if(flag){
            ui->lwGroups->addItem(model_all_groups->index(i,1).data().toString());
        }
    }
}

void Main_Widget::FillSubjTable() {
    qDebug() << "refreshing all groups table";
    model_subj = new QSqlTableModel();
    model_subj->setTable("AllSubj");
    model_subj->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_subj->setHeaderData(1, Qt::Horizontal, tr("Предмет"));
    model_subj->sort(0, Qt::AscendingOrder);
    model_subj->select();
    ui->tableView_subj->setModel(model_subj);
    ui->tableView_subj->setColumnHidden(0,true);
    ui->tableView_subj->resizeRowsToContents();
    ui->tableView_subj->resizeColumnsToContents();
    ui->tableView_subj->setSortingEnabled(true);               // Сортировка таблицы
    ui->tableView_subj->sortByColumn(0,Qt::AscendingOrder);    // Порядок сортировки по умолчанию
    ui->tableView_subj->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
}

void Main_Widget::on_AddStudAllButton_clicked()
{
    qDebug() << "add student button was clicked";
    model_all_stud->sort(0, Qt::AscendingOrder);
    int size = model_all_stud->rowCount();
    model_all_stud->insertRow(size); //добавляем строку, без сохранения она не запишется в бд
    model_all_stud->setData(model_all_stud->index(size,3),"студент"); //По умолчанию ставим статус студента
    added_row_index = size;
}

void Main_Widget::on_DeleteStudAllButton_clicked()
{
    qDebug() << "delete student button was clicked";
    //Подтверждение удаления выделенного элемента
    QMessageBox ms;
    ms.setWindowTitle("Предупреждение");
    ms.setWindowIcon(favicon);
    if(ui->tableView_all_stud->selectionModel()->hasSelection())
    {
        qDebug() << "All Student table has selection";
        QAbstractButton *yes = ms.addButton("Да",QMessageBox::YesRole);
        ms.addButton("Нет",QMessageBox::NoRole);
        ms.setText("Точно хочешь удалить этого бедолагу?");
        ms.setIcon(QMessageBox::Warning);
        ms.exec();
        if(ms.clickedButton() == yes)
        {
           int row;
           int id;
           QItemSelectionModel *select = ui->tableView_all_stud->selectionModel();
           if(select->hasSelection()){
               row = select->currentIndex().row();
               model_all_stud->removeRow(row);
               model_all_stud->submitAll();
               id = ui->tableView_all_stud->model()->index(row,0).data().toInt();
               QSqlTableModel *mod = new QSqlTableModel();
               mod->setTable("AllStudents");
               int n = mod->rowCount();
               for (int i = 0; i<n; i++){
                   if(mod->index(i,0).data().toInt() == id){
                       mod->removeRow(i);
                       i--;
                       n--;
                   }
               }
               mod->submitAll();
               this->FillAllStudTable();
           }
       }
    } else {
        ms.setText("Вы не выбрали студента или таблица пуста");
        ms.setIcon(QMessageBox::Warning);
        ms.addButton("Окей, босс",QMessageBox::ApplyRole);
        ms.exec();
    }
}

void Main_Widget::on_AddGroupButton_clicked()
{
    qDebug() << "add group button was clicked";
    model_all_groups->sort(0, Qt::AscendingOrder);
    int size = model_all_groups->rowCount();
    model_all_groups->insertRow(size); //добавляем строку, без сохранения она не запишется в бд
    added_group_row_index = size;
}

void Main_Widget::on_DeleteGroupButton_clicked()
{
    qDebug() << "delete group button was clicked";
    //Подтверждение удаления выделенного элемента
    QMessageBox ms;
    ms.setWindowTitle("Предупреждение");
    ms.setWindowIcon(favicon);
    if(ui->tableView_all_group->selectionModel()->hasSelection())
    {
        qDebug() << "Group table has selection";
        QAbstractButton *yes = ms.addButton("Да",QMessageBox::YesRole);
        ms.addButton("Нет",QMessageBox::NoRole);
        ms.setText("Точно хочешь удалить это общество бедолаг?");
        ms.setIcon(QMessageBox::Warning);
        ms.exec();
        if(ms.clickedButton() == yes)
        {
           int row;
           QItemSelectionModel *select = ui->tableView_all_group->selectionModel();
           if(select->hasSelection()){
               row = select->currentIndex().row();

               QString group_name =ui->tableView_all_group->model()->index(row,1).data().toString();
               QString table_name = "SubjectsFor_"+group_name;
               QSqlQuery q(db);
               qDebug() << table_name << " try to delete";
               if(!q.exec("DROP TABLE IF EXISTS " + table_name)){
                   qDebug() << table_name << " table successfully deleted";
               }
               for(int i = 0; i < model_subj->rowCount(); i++){
                   table_name = "Subj_"+group_name + "_" + model_subj->index(i,1).data().toString();
                   if(q.exec("DROP TABLE IF EXISTS " + table_name)){
                       qDebug() << table_name << " table successfully deleted";
                   }
               }
               int n =model_all_stud->rowCount();
               for(int i = 0; i<n; i++) {
                   if(model_all_stud->index(i,2).data().toString()==group_name){
                       model_all_stud->removeRow(i);
                       model_all_stud->submitAll();
                       i--;
                       n--;
                   }
               }

               model_all_groups->removeRow(row);
               model_all_groups->submitAll();
               this->FillAllGroupTable();
               this->FillAllStudTable();
           }
       }
    } else {
        ms.setText("Вы не выбрали группу или таблица пуста");
        ms.setIcon(QMessageBox::Warning);
        ms.addButton("Окей, босс",QMessageBox::ApplyRole);
        ms.exec();
    }
}

void Main_Widget::on_AddSubjButton_clicked()
{
    qDebug() << "add subject button was clicked";
    model_subj->sort(0, Qt::AscendingOrder);
    int size = model_subj->rowCount();
    model_subj->insertRow(size); //добавляем строку, без сохранения она не запишется в бд
}

void Main_Widget::on_DeleteSubjButton_clicked()
{
    qDebug() << "delete subject button was clicked";
    //Подтверждение удаления выделенного элемента
    QMessageBox ms;
    ms.setWindowTitle("Предупреждение");
    ms.setWindowIcon(favicon);
    if(ui->tableView_subj->selectionModel()->hasSelection())
    {
        qDebug() << "Subject table has selection";
        QAbstractButton *yes = ms.addButton("Да",QMessageBox::YesRole);
        ms.addButton("Нет",QMessageBox::NoRole);
        ms.setText("Точно хочешь удалить этот предмет?");
        ms.setIcon(QMessageBox::Warning);
        ms.exec();
        if(ms.clickedButton() == yes)
        {
           int row;
           QItemSelectionModel *select = ui->tableView_subj->selectionModel();
           if(select->hasSelection()){
               row = select->currentIndex().row();

               QString subject_name = ui->tableView_subj->model()->index(row,1).data().toString();
               for(int i = 0; i < ui->lwGroups->count(); i++){
                   QSqlTableModel *model_buffer;
                   QString group_name = ui->lwGroups->item(i)->text();
                   QString table_name = "SubjectsFor_"+ group_name;
                   model_buffer = new QSqlTableModel();
                   model_buffer->setTable(table_name);
                   model_buffer->setEditStrategy(QSqlTableModel::OnManualSubmit);
                   model_buffer->select();

                   QString table_name_sub = "Subj_"+group_name + "_" + subject_name;
                   QSqlQuery q(db);
                   if(q.exec("DROP TABLE IF EXISTS " + table_name_sub)){
                        qDebug() << table_name_sub << " table successfully deleted";
                   }


                   int n = model_buffer->rowCount();
                   for(int j = 0; j < n;j++){
                       if(model_buffer->index(j,1).data().toString()==subject_name){
                           model_buffer->removeRow(j);
                           model_buffer->submitAll();
                           j--;
                           n--;
                       }
                   }
               }

               model_subj->removeRow(row);
               model_subj->submitAll();
               this->FillAllGroupTable();
               this->FillAllStudTable();
           }
       }
    } else {
        ms.setText("Вы не выбрали группу или таблица пуста");
        ms.setIcon(QMessageBox::Warning);
        ms.addButton("Окей, босс",QMessageBox::ApplyRole);
        ms.exec();
    }
}

void Main_Widget::on_AddGroupSubjButton_clicked()
{
    qDebug() << "add group-subject button was clicked";
    model_group_subj->sort(0, Qt::AscendingOrder);
    int size = model_group_subj->rowCount();
    model_group_subj->insertRow(size); //добавляем строку, без сохранения она не запишется в бд
    added_group_subj_row_index = size;
}

void Main_Widget::on_DeleteGroupSubjButton_clicked()
{
    qDebug() << "delete group-subject button was clicked";
    //Подтверждение удаления выделенного элемента
    QMessageBox ms;
    ms.setWindowTitle("Предупреждение");
    ms.setWindowIcon(favicon);
    if(ui->tableView_GroupSubj->selectionModel()->hasSelection())
    {
        qDebug() << "Group-subject table has selection";
        QAbstractButton *yes = ms.addButton("Да",QMessageBox::YesRole);
        ms.addButton("Нет",QMessageBox::NoRole);
        ms.setText("Точно хочешь удалить этот предмет?");
        ms.setIcon(QMessageBox::Warning);
        ms.exec();
        if(ms.clickedButton() == yes)
        {
           int row;
           QItemSelectionModel *select = ui->tableView_GroupSubj->selectionModel();
           if(select->hasSelection()){
               row = select->currentIndex().row();

               QString group_name = ui->tableView_all_group->model()->index(selected_group_row_index,1).data().toString();
               QString subject_name = ui->tableView_GroupSubj->model()->index(row,1).data().toString();
               QString table_name = "Subj_" + group_name + "_" + subject_name;
               QSqlQuery q(db);
               qDebug() << "DROP TABLE IF EXISTS " + table_name;
               if(q.exec("DROP TABLE IF EXISTS " + table_name)){
                    qDebug() << table_name << " table successfully deleted";
               }
               model_group_subj->removeRow(row);
               model_group_subj->submitAll();
               this->FillAllGroupTable();
               this->FillAllStudTable();
           }
       }
    } else {
        ms.setText("Вы не выбрали группу или таблица пуста");
        ms.setIcon(QMessageBox::Warning);
        ms.addButton("Окей, босс",QMessageBox::ApplyRole);
        ms.exec();
    }
}

// добавление нового столбика занятий
void Main_Widget::on_AddClassButton_clicked()
{
    QString selected_date = ui->dateEdit_class->date().toString("dd_MM_yyyy");
    int size = model_current_group_subj->columnCount();
    qDebug() << size << " " << selected_date;
    if(size>3){
        QString prelast_date = model_current_group_subj->headerData(size-1, Qt::Horizontal, Qt::DisplayRole).toString();
        //prelast_date.remove(0,5);
        prelast_date.replace("_",".");
        qDebug() << size << " " << selected_date << prelast_date;
        QDate pre_date = QDate::fromString(prelast_date,"dd.MM.yyyy");
        QDate add_date = ui->dateEdit_class->date();
        if(pre_date>add_date){
            qDebug() << "меньше";
            return;
        }
        qDebug() << "больше";
    }
    QString save_date = "date_" + selected_date;
    qDebug() << selected_date << current_class_table_name;
    QSqlQuery q(db);
    qDebug() << "ALTER TABLE " + current_class_table_name + " ADD " + save_date + " TEXT";
    if(!q.exec("ALTER TABLE " + current_class_table_name + " ADD " + save_date + " TEXT")){
        qDebug() << "column add failure";
        return;
    }
    this->FillClassTable(current_class_table_name);
}

void Main_Widget::on_DeleteClassButton_clicked()
{
    qDebug() << "delete class button was clicked";
    //Подтверждение удаления выделенного элемента
    QMessageBox ms;
    ms.setWindowTitle("Предупреждение");
    ms.setWindowIcon(favicon);
    if(ui->tableView->selectionModel()->hasSelection())
    {
        qDebug() << "Class table has selection";
        QAbstractButton *yes = ms.addButton("Да",QMessageBox::YesRole);
        ms.addButton("Нет",QMessageBox::NoRole);
        ms.setText("Точно хочешь удалить это занятие?");
        ms.setIcon(QMessageBox::Warning);
        ms.exec();
        if(ms.clickedButton() == yes)
        {
           int column;
           QItemSelectionModel *select = ui->tableView->selectionModel();
           if(select->hasSelection()){
               column = select->currentIndex().column();
               //если выделена столбец не занятия
               //то прекращаем процесс удаления
               if(column<3){
                   QMessageBox ms2;
                   ms2.setText("Вы не выбрали отличный от занятия столбец");
                   ms2.setWindowTitle("Предупреждение");
                   ms2.setWindowIcon(favicon);
                   ms2.setIcon(QMessageBox::Warning);
                   ms2.addButton("Окей, босс",QMessageBox::ApplyRole);
                   ms2.exec();
                   return;
               }
               QString allColumns = "id, StudentName, StudentStatus";
               QString allColumns_with_type = "id INTEGER NOT NULL UNIQUE, StudentName TEXT NOT NULL, StudentStatus TEXT NOT NULL, ";
               for(int i = 3; i < model_current_group_subj->columnCount(); i++){
                   if(i != column){
                        QString date = model_current_group_subj->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString();
                        qDebug() << "column name: " << date;
                        date.replace(".","_");
                        allColumns = allColumns + ", date_" + date;
                        allColumns_with_type = allColumns_with_type + "date_" + date + " TEXT, ";
                   }
               }
               allColumns_with_type = allColumns_with_type + "PRIMARY KEY(id AUTOINCREMENT)";
               qDebug() << allColumns;
               qDebug() << allColumns_with_type;
               //return;
               QString request = "CREATE TABLE " + current_class_table_name + "_new(" + allColumns_with_type + ")";
               QSqlQuery q(db);
               if(!q.exec(request)){
                   qDebug() << "Create new table failure";
                   return;
               }
               request = "INSERT INTO " + current_class_table_name + "_new SELECT " + allColumns + " FROM " + current_class_table_name;
               if(!q.exec(request)){
                   qDebug() << "Copy to new table failure";
                   return;
               }
               request = "DROP TABLE IF EXISTS " + current_class_table_name;
               if(!q.exec(request)){
                   qDebug() << "Delete old table failure";
                   return;
               }
               request = "ALTER TABLE " + current_class_table_name + "_new RENAME TO " + current_class_table_name;
               if(!q.exec(request)){
                   qDebug() << "Rename new table failure";
                   return;
               }
               this->FillClassTable(current_class_table_name);

/*
               QString group_name = ui->tableView_all_group->model()->index(selected_group_row_index,1).data().toString();
               QString subject_name = ui->tableView_GroupSubj->model()->index(row,1).data().toString();
               QString table_name = "Subj_" + group_name + "_" + subject_name;
               QSqlQuery q(db);
               qDebug() << "DROP TABLE IF EXISTS " + table_name;
               if(q.exec("DROP TABLE IF EXISTS " + table_name)){
                    qDebug() << table_name << " table successfully deleted";
               }*/
           }
       }
    } else {
        ms.setText("Вы не выбрали занятие или таблица пуста");
        ms.setIcon(QMessageBox::Warning);
        ms.addButton("Окей, босс",QMessageBox::ApplyRole);
        ms.exec();
    }
}


//---изменение инфы о студентах ------begin
void Main_Widget::on_BirthdayText_change()
{
    QString selected_date = ui->dateEdit->date().toString("dd.MM.yyyy");
    qDebug() << "editing birthday: "<< selected_row_index << " " << selected_date;
    model_all_stud->setData(model_all_stud->index(selected_row_index,5),selected_date);
}

void Main_Widget::on_PhoneText_change()
{
    QString selected_phone = ui->plainTextEdit_phone_number->toPlainText();
    qDebug() << "editing phone number: "<< selected_row_index << " " << selected_phone;
    model_all_stud->setData(model_all_stud->index(selected_row_index,6),selected_phone);
}

void Main_Widget::on_EmailText_change()
{
    QString selected_email = ui->plainTextEdit_email->toPlainText();
    qDebug() << "editing phone number: "<< selected_row_index << " " << selected_email;
    model_all_stud->setData(model_all_stud->index(selected_row_index,7),selected_email);
}

void Main_Widget::on_LoadImageButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(0, "Выберите изображение", QDir::currentPath(), "*.png *.jpg *.gif *.jpeg");
    QImage image(filename);
    ui->label_photo->setPixmap(QPixmap::fromImage(image));
    model_all_stud->setData(model_all_stud->index(selected_row_index,8),filename);
}

void Main_Widget::on_ExtraInfoText_change()
{
    QString selected_ExtraInfo = ui->textEdit_extra_info->toPlainText();
    qDebug() << "editing extra info: "<< selected_row_index << " " << selected_ExtraInfo;
    model_all_stud->setData(model_all_stud->index(selected_row_index,9),selected_ExtraInfo);
}
//---изменение инфы о студентах-------end

//сохранение таблицы всех студентов в бд
void Main_Widget::on_SaveTableAllButton_clicked()
{
    //проверяем, существует ли группа, добавляемого студента в таблице групп
    bool flag = false;
    for(int i = 0; i < ui->lwGroups->count(); i++){
        if(model_all_stud->index(added_row_index,2).data().toString() == ui->lwGroups->item(i)->text()){
            flag = true;
        }
    }
    //если существует, то сохраняем
    if(flag){
        model_all_stud->submitAll();
    } else {
        QMessageBox ms;
        ms.setWindowTitle("Предупреждение");
        ms.setWindowIcon(favicon);
        ms.setText("Такой группы не существует");
        ms.setIcon(QMessageBox::Warning);
        ms.addButton("Окей, босс",QMessageBox::ApplyRole);
        ms.exec();
    }
}

//отмена изменений таблицы всех студентов
void Main_Widget::on_ReturnTableAllButton_clicked()
{
    model_all_stud->revertAll();
}

//сохранение таблицы групп в бд
void Main_Widget::on_SaveTableGroupButton_clicked()
{
    if(model_all_groups->submitAll()){
        QString group_name =ui->tableView_all_group->model()->index(added_group_row_index,1).data().toString();
        QString table_name = "SubjectsFor_"+group_name;
        QSqlQuery q(db);
        qDebug() << "CREATE TABLE IF NOT EXISTS " + table_name;
        if(!q.exec("CREATE TABLE IF NOT EXISTS " + table_name + "(" +
                            "id INTEGER NOT NULL UNIQUE, " +
                            "Subject TEXT NOT NULL UNIQUE, " +
                            "PRIMARY KEY(id AUTOINCREMENT)" +
                            ")")){
            qDebug() << "failure";
        }
        this->UpdateAllGroupsInfo();
    }
}

//отмена изменений таблицы групп
void Main_Widget::on_ReturnTableGroupButton_clicked()
{
    model_all_groups->revertAll();
}

//сохранение таблицы дисциплин в бд
void Main_Widget::on_SaveTableSubjButton_clicked()
{
    model_subj->submitAll();
}

//отмена изменений таблицы дисциплин
void Main_Widget::on_ReturnTableSubjButton_clicked()
{
    model_subj->revertAll();
}

//сохранение таблицы дисциплин по группам в бд
void Main_Widget::on_SaveTableGroupSubjButton_clicked()
{
    qDebug() << "save group-subject button was pressed";
    //проверяем, существует ли предмет, добавляемый в учебный план группы
    bool flag = false;
    for(int i = 0; i < model_subj->rowCount(); i++){
        if(model_group_subj->index(added_group_subj_row_index,1).data().toString() == model_subj->index(i,1).data().toString()){
            flag = true;
        }
    }
    //если существует, то сохраняем
    if(flag){
        if(model_group_subj->submitAll()){
            QString group_name = model_all_groups->index(selected_group_row_index,1).data().toString();
            QString subject_name = model_group_subj->index(added_group_subj_row_index,1).data().toString();
            QString table_name = "Subj_"+group_name+"_"+subject_name;
            QSqlQuery q(db);
            qDebug() << "CREATE TABLE IF NOT EXISTS " + table_name;
            if(!q.exec("CREATE TABLE IF NOT EXISTS " + table_name + "(" +
                                "id INTEGER NOT NULL UNIQUE, " +
                                "StudentName TEXT NOT NULL, " +
                                "StudentStatus TEXT NOT NULL, " +
                                "PRIMARY KEY(id AUTOINCREMENT)" +
                                ")"
                       )){
                qDebug() << "failure";
            }
        }
    } else {
        QMessageBox ms;
        ms.setWindowTitle("Предупреждение");
        ms.setWindowIcon(favicon);
        ms.setText("Такого предмета не существует");
        ms.setIcon(QMessageBox::Warning);
        ms.addButton("Окей, босс",QMessageBox::ApplyRole);
        ms.exec();
    }
}

//отмена изменений таблицы дисциплин по группам
void Main_Widget::on_ReturnTableGroupSubjButton_clicked()
{
    model_group_subj->revertAll();
}

//сохранение таблицы занятий в бд
void Main_Widget::on_SaveTableClassButton_clicked()
{
    qDebug() << "Save class table";
    model_current_group_subj->submitAll();

}

//отмена изменений таблицы занятий
void Main_Widget::on_ReturnTableClassButton_clicked()
{
    qDebug() << "Revert class table";
    model_current_group_subj->revertAll();
}

//логин в учётную запись
void Main_Widget::on_SignInButton_clicked()
{

    if (ui->LoginLE->text() == "")
    {
        QMessageBox::warning(this, "Error", "Введите логин!");
        return;
    }
    ui->label_5->setVisible(false);
    this->resize(1160,650);
    this->setMinimumSize(1160,650);
    this->setMaximumSize(1160,650);
    this->setWindowTitle("Журнал куратора");
    ui->label_CurName->setText("Куратор: " + ui->LoginLE->text());
    ui->pushButton_SwitchWidget->setText("Перейти к отдельной группе");
    this->FillAllStudTable();
    this->FillAllGroupTable();
    this->FillSubjTable();
    this->FillGroupComboBox();
    ui->stackedWidget->setCurrentIndex(2);
}

//выход из учётной записи
void Main_Widget::on_SignOutButton_clicked()
{
    this->resize(200,130);
    this->setMinimumSize(200,130);
    this->setMaximumSize(200,130);
    this->setWindowTitle("Вход");
    ui->label_5->setVisible(true);
    ui->LoginLE->setText("");
    ui->stackedWidget->setCurrentIndex(0);
    ui->pushButton_SwitchWidget->setText("Перейти к отдельной группе");
    ui->pushButton_GroupControl->setText("Управление группами");
}


void Main_Widget::on_SwtchWidgetButton_clicked()
{
    if(ui->pushButton_SwitchWidget->text() == "Перейти к отдельной группе"){
        this->FillAllStudTable();
        this->FillAllGroupTable();
        this->FillSubjTable();
        this->FillGroupComboBox();
        ui->stackedWidget->setCurrentIndex(1);
        ui->pushButton_SwitchWidget->setText("Открыть список всех студентов");
        ui->pushButton_GroupControl->setText("Управление группами");
    }
    else{
        this->FillAllStudTable();
        this->FillAllGroupTable();
        ui->stackedWidget->setCurrentIndex(2);
        ui->pushButton_SwitchWidget->setText("Перейти к отдельной группе");
        ui->pushButton_GroupControl->setText("Управление группами");
    }
}

void Main_Widget::on_EditGroupButton_clicked()
{
    if(ui->pushButton_GroupControl->text() == "Управление группами"){
        this->FillAllStudTable();
        this->FillAllGroupTable();
        this->FillSubjTable();
        ui->stackedWidget->setCurrentIndex(3);
        ui->pushButton_GroupControl->setText("Вернуться ко всем студентам");
        ui->pushButton_SwitchWidget->setText("Перейти к отдельной группе");
    }
    else{
        this->FillAllStudTable();
        this->FillAllGroupTable();
        this->FillSubjTable();
        ui->stackedWidget->setCurrentIndex(2);
        ui->pushButton_GroupControl->setText("Управление группами");
        ui->pushButton_SwitchWidget->setText("Перейти к отдельной группе");
    }
}

void Main_Widget::closeEvent(QCloseEvent *event)
{
    event->ignore();
    QMessageBox ms;
    ms.setIcon(QMessageBox::Warning);
    ms.setWindowIcon(favicon);
    ms.setWindowTitle("Выход");
    QAbstractButton *yes = ms.addButton("Да",QMessageBox::YesRole);
    ms.addButton("Нет",QMessageBox::NoRole);
    ms.setText("Уверены?");
    ms.exec();
    if(ms.clickedButton() == yes) event->accept();
}

Main_Widget::~Main_Widget()
{
    delete ui;
}
