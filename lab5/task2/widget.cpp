#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    bool ok;
    int inputNum = QInputDialog::getInt(this, "push_back", "Enter number", 0, INT_MIN, INT_MAX, 1, &ok);
    if(!ok) return;

    deque.push_back(inputNum);
    fillListWidget();
}


void Widget::on_pushButton_2_clicked()
{
    bool ok;
    int inputNum = QInputDialog::getInt(this, "push_front", "Enter number", 0, INT_MIN, INT_MAX, 1, &ok);
    if(!ok) return;

    deque.push_front(inputNum);
    fillListWidget();
}


void Widget::on_pushButton_3_clicked()
{
    if(deque.empty()) return;

    deque.pop_back();
    fillListWidget();
}


void Widget::on_pushButton_4_clicked()
{
    if(deque.empty()) return;

    deque.pop_front();
    fillListWidget();
}


void Widget::on_pushButton_5_clicked()
{
    if(deque.empty()) return;

    deque.clear();
    fillListWidget();
}

void Widget::on_pushButton_6_clicked()
{
    QMessageBox::information(this, "size", "size of deque: " + QString::number(deque.size()));
}

void Widget::on_pushButton_7_clicked()
{
    QMessageBox::information(this, "empty", deque.empty() ? "Deque is empty" : "Deque isn't empty");
}

void Widget::on_pushButton_8_clicked()
{
    bool ok;
    int inputSize = QInputDialog::getInt(this, "resize", "Enter number",0, 0, INT_MAX, 1, &ok);
    if(!ok) return;

    deque.resize(inputSize);



    fillListWidget();
}

void Widget::fillListWidget()
{
    while(ui->listWidget->count()){
        delete ui->listWidget->item(0);
    }

    for(auto it = deque.begin(); it != deque.end(); ++it){
        ui->listWidget->addItem(QString::number(*it));
    }
}









