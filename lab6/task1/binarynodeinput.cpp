#include "binarynodeinput.h"
#include "ui_binarynodeinput.h"

BinaryNodeInput::BinaryNodeInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BinaryNodeInput)
{
    ui->setupUi(this);
    ui->spinBox->setRange(INT_MIN, INT_MAX);
}

BinaryNodeInput::~BinaryNodeInput()
{
    delete ui;
}

std::pair<int, std::string> BinaryNodeInput::getTreeElement()
{
    BinaryNodeInput dialog;
    dialog.exec();
    return std::pair<int, std::string>(dialog.ui->spinBox->value(), dialog.ui->lineEdit->text().toStdString());
}

void BinaryNodeInput::on_pushButton_clicked()
{
    close();
}

