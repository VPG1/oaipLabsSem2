#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->spinBox_2->setRange(0, numberOfBits - 1);
    ui->spinBox_3->setRange(0, numberOfBits - 1);
    ui->spinBox_4->setRange(0, numberOfBits - 1);
    ui->spinBox_5->setRange(0, numberOfBits - 1);

    updateBitsetView();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::updateBitsetView()
{
    ui->label_2->setText(QString::fromStdString(bts.to_string()));
}



void Widget::on_pushButton_clicked()
{
    QMessageBox::information(this, "all", bts.all() ? "true" : "false");
}


void Widget::on_pushButton_3_clicked()
{
    QMessageBox::information(this, "none", bts.none() ? "true" : "false");

}


void Widget::on_pushButton_2_clicked()
{
    QMessageBox::information(this, "any", bts.any() ? "true" : "false");
}


void Widget::on_pushButton_4_clicked()
{
    QMessageBox::information(this, "count", QString::number(bts.count()));
}


void Widget::on_pushButton_8_clicked()
{
    QMessageBox::information(this, "size", QString::number(bts.size()));

}


void Widget::on_pushButton_10_clicked()
{
    QMessageBox::information(this, "to_string", QString::fromStdString(bts.to_string()));
}


void Widget::on_pushButton_11_clicked()
{
    QMessageBox::information(this, "size", QString::number(bts.to_ullong()));
}


void Widget::on_pushButton_12_clicked()
{
    QMessageBox::information(this, "size", QString::number(bts.to_ulong()));

}


void Widget::on_pushButton_7_clicked()
{
    bts.set(ui->spinBox_4->value());
    updateBitsetView();
}


void Widget::on_pushButton_6_clicked()
{
    bts.reset(ui->spinBox_2->value());
    updateBitsetView();
}




void Widget::on_pushButton_5_clicked()
{
    bts.flip(ui->spinBox_3->value());
    updateBitsetView();
}


void Widget::on_pushButton_9_clicked()
{
    QMessageBox::information(this, "none", bts.test(ui->spinBox_5->value()) ? "true" : "false");
    bts.test(ui->spinBox_5->value());
    updateBitsetView();
}

