#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{

    bool ok;
    int inputNumber = QInputDialog::getInt(this, "push", "Emter number", 0, INT_MIN, INT_MAX, 1, &ok);
    if(!ok){
        return;
    }

    queue.push(inputNumber);
    ui->listWidget->addItem(QString::number(inputNumber));

    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
}


void Widget::on_pushButton_2_clicked()
{
    queue.pop();
    delete ui->listWidget->item(0);

    if(ui->listWidget->count() == 0){
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
    }
}


void Widget::on_pushButton_3_clicked()
{
    QMessageBox::information(this, "top", "Top element: " + QString::number(queue.top()));
}


void Widget::on_pushButton_4_clicked()
{
    while(ui->listWidget_2->count()){
        delete ui->listWidget_2->item(0);
        randomNumbersList.pop_back();
    }

    for(int i = 0; i < ui->spinBox->value(); ++i){
        int randomNumber = getRandomNumber(-1000, 1000);
        randomNumbersList.push_back(randomNumber);
        ui->listWidget_2->addItem(QString::number(randomNumber));
    }
}

int Widget::getRandomNumber(int min, int max)
{
    return rand() % (max - min + 1) + min;
}


void Widget::on_pushButton_5_clicked()
{
    Queue<int> tempQueue;

    while(randomNumbersList.size()){
        if(randomNumbersList.back() >= 0){
            tempQueue.push(randomNumbersList.back());
        }
        randomNumbersList.pop_back();
    }

    while(!tempQueue.empty()){
        randomNumbersList.push_front(tempQueue.top());
        tempQueue.pop();
    }

    while(ui->listWidget_2->count()){
        delete ui->listWidget_2->item(0);
    }

    for(auto it = randomNumbersList.begin(); it != randomNumbersList.end(); ++it){
        ui->listWidget_2->addItem(QString::number(*it));
    }
}

