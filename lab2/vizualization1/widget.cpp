#include "widget.h"
#include "ui_widget.h"
#include "stack.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->comboBox->addItem("unique_ptr");
    ui->comboBox->addItem("shared_ptr and weak_ptr");

    ui->pushButton->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);

    connect(ui->comboBox, &QComboBox::activated,
            ui->stackedWidget, &QStackedWidget::setCurrentIndex);

}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_lineEdit_2_textEdited(const QString &arg1)
{
    if(arg1.isEmpty()){
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        qDebug() << "empty";
    }
    else{
        ui->pushButton_3->setEnabled(true);
        ui->pushButton_4->setEnabled(true);
        qDebug() << "notEmpty";
    }
}


void Widget::on_lineEdit_textEdited(const QString &arg1)
{
    if(arg1.isEmpty()){
        ui->pushButton->setEnabled(false);
        qDebug() << "empty";
    }
    else{
        ui->pushButton->setEnabled(true);
        qDebug() << "notEmpty";
    }
}


void Widget::on_pushButton_clicked()
{
    stack.push(ui->lineEdit->text());
    ui->listWidget->addItem(ui->lineEdit->text());
}


void Widget::on_pushButton_2_clicked()
{
    if(stack.size() == 0)
        return;

    stack.pop();
    delete ui->listWidget->takeItem(stack.size());
}




void Widget::on_listWidget_2_currentRowChanged(int currentRow)
{
    currentIndex = currentRow;
}


void Widget::on_pushButton_3_clicked()
{
    if(currentIndex == -1){
        on_pushButton_4_clicked();
        return;
    }

//    list.insert(ui->lineEdit_2->text(), currentIndex);
    list.insert(ui->lineEdit_2->text(), currentIndex);
    ui->listWidget_2->insertItem(currentIndex, ui->lineEdit_2->text());
    ui->listWidget_2->setCurrentRow(currentIndex);
}


void Widget::on_pushButton_4_clicked()
{
    list.addTail(ui->lineEdit_2->text());
    ui->listWidget_2->addItem(ui->lineEdit_2->text());
}


void Widget::on_pushButton_5_clicked()
{
    if(currentIndex == -1 || list.size() == 0)
        return;

    if(currentIndex == list.size()){
        --currentIndex;
        ui->listWidget_2->setCurrentRow(currentIndex);
    }

    list.del(currentIndex);



    delete ui->listWidget_2->takeItem(currentIndex);
}

