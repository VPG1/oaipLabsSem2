#include "form.h"
#include "ui_form.h"
#include <QTableWidgetItem>

Form::Form(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

}

Form::Form(ListOnArray<Information> &&informationList, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int i = 0;
    for(auto it = informationList.begin(); it != informationList.end(); ++it, ++i){
//        if(statementList.begin() == ListOnArray<Information>::iterator())
//            return;


        ui->tableWidget->insertRow(i);

        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString((it->lastName()))));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(it->name())));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(it->patronymic())));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString((it->group()))));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(it->grade())));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(QString::number(it->income())));

//        QTableWidgetItem *item = new QTableWidgetItem;
//        item->setText("0");
//        ui->tableWidget->setItem(i, 0, item);
//        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString((*it).name()), Qt::DisplayRole));
//        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString((*it).patronymic()), Qt::DisplayRole));
//        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString((*it).address()), Qt::DisplayRole));
//        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number((*it).grade()), Qt::DisplayRole));
    }
}

Form::~Form()
{
    delete ui;
}

void Form::showTable(ListOnArray<Information> &&statementList)
{
    Form form(std::move(statementList));
    form.exec();
}

void Form::on_pushButton_clicked()
{
    close();
}
