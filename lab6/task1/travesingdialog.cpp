#include "travesingdialog.h"
#include "ui_travesingdialog.h"

TravesingDialog::TravesingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TravesingDialog)
{
    ui->setupUi(this);

}

TravesingDialog::~TravesingDialog()
{
    delete ui;
}

void TravesingDialog::showTraversing(const std::vector<std::string> &preorder, const std::vector<std::string> &postorder, const std::vector<std::string> &inorder)
{
    TravesingDialog dialog;
    for(auto el : preorder){
        dialog.ui->listWidget->addItem(QString::fromStdString(el));
    }
    for(auto el : postorder){
        dialog.ui->listWidget_2->addItem(QString::fromStdString(el));
    }
    for(auto el : inorder){
        dialog.ui->listWidget_3->addItem(QString::fromStdString(el));
    }

    dialog.exec();
}

void TravesingDialog::on_pushButton_clicked()
{
    close();
}

