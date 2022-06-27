#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->spinBox->setRange(INT_MIN, INT_MAX);
    ui->spinBox_2->setRange(INT_MIN, INT_MAX);
    ui->spinBox_3->setRange(INT_MIN, INT_MAX);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::updateListWidget()
{
    while(ui->listWidget->count()){
        delete ui->listWidget->item(0);
    }

    auto v = uMap.getElements();

    for(auto it = v.begin(); it != v.end(); ++it){
        ui->listWidget->addItem(QString("%1\t%2").arg(it->first).arg(it->second.c_str()));
    }
}


void Widget::on_pushButton_clicked()
{
    QMessageBox::information(this, "contains", QString("Element with key %1 is").arg(ui->spinBox->value()) +
                             (uMap.contains(ui->spinBox->value()) ? "" : "n't") + " contained in the container");
}


void Widget::on_pushButton_2_clicked()
{
    uMap.insert({ui->spinBox_2->value(), ui->lineEdit->text().toStdString()});

    updateListWidget();
}



void Widget::on_pushButton_3_clicked()
{
    uMap.erase(ui->spinBox_3->value());

    updateListWidget();
}


void Widget::on_pushButton_4_clicked()
{
    uMap.clear();

    updateListWidget();
}

