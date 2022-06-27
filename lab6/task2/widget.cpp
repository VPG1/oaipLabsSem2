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

    auto v = hashTable.hashTableView();

    for(auto el : v){
        ui->listWidget->addItem(QString::fromStdString(el));
    }
}

int Widget::getRandomNumber(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

void Widget::on_pushButton_clicked()
{
    hashTable.insert(ui->spinBox->value(), ui->lineEdit->text().toStdString());

    updateListWidget();
}


void Widget::on_pushButton_2_clicked()
{
    hashTable.erase(ui->spinBox_2->value());

    updateListWidget();
}


void Widget::on_pushButton_3_clicked()
{
    std::optional<std::string> str = hashTable.find(ui->spinBox_3->value());

    QMessageBox::information(this, "find", str.has_value() ?
                                 ("Value: " + QString::fromStdString(str.value())) :
                                 ("There are no elements with this key"));
}


void Widget::on_pushButton_4_clicked()
{
    std::optional<std::string> str = hashTable.findElementWithLargestKey();

    QMessageBox::information(this, "find", str.has_value() ?
                                 ("Value: " + QString::fromStdString(str.value())) :
                                 ("Hast table empty"));

}

