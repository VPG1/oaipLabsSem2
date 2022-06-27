#include "arraydialog.h"
#include "ui_arraydialog.h"

ArrayDialog::ArrayDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ArrayDialog)
{
    ui->setupUi(this);
    ui->lineEdit->setPlaceholderText("value");
}

ArrayDialog::~ArrayDialog()
{
    delete ui;
}

std::vector<std::string> ArrayDialog::getVector()
{
    ArrayDialog arrayDialog;
    arrayDialog.exec();

    return arrayDialog.array;
}

void ArrayDialog::on_pushButton_clicked()
{
    array.push_back(ui->lineEdit->text().toStdString());
    ui->listWidget->addItem(ui->lineEdit->text());
}



void ArrayDialog::on_pushButton_3_clicked()
{
    if(array.empty()) return;
    delete ui->listWidget->item(array.size() - 1);
    array.pop_back();
}


void ArrayDialog::on_pushButton_2_clicked()
{
    close();
}

