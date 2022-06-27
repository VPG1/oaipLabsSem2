#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include "informationlist.h"
#include "information.h"
#include "listonarray.h"
#include <QMessageBox>
#include "mylineedit.h"
#include <QDoubleSpinBox>
#include "informationdialog.h"
#include "form.h"
#include <QInputDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->tableWidget->setEnabled(false);

    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);

    ui->pushButton_5->setEnabled(false);
    ui->pushButton_6->setEnabled(false);
    ui->pushButton_7->setEnabled(false);

    ui->lineEdit_2->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-ZА-Яa-zа-я]+")));
    ui->lineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9]{0,18}")));
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_4_clicked()
{

    areOpeningFile = true;

    QString path = QFileDialog::getOpenFileName(this, "open file",
                                                QDir::rootPath(), "text file (*.txt)");
    if(path.isEmpty()){
        return;
    }


    qDebug() << ui->tableWidget->rowCount();
    while(ui->tableWidget->rowCount()){

        ui->tableWidget->removeRow(0);
        qDebug() << ui->tableWidget->rowCount();
    }



    qDebug() << "w1";
    if(!InformationList::fileIsCorrect(path.toStdString())){
        qDebug() << "w2";
        ui->tableWidget->setEnabled(false);

        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);

        ui->pushButton_5->setEnabled(false);
        ui->pushButton_6->setEnabled(false);
        ui->pushButton_7->setEnabled(false);
        QMessageBox::warning(this, "warning", "file doesn't fit");
        return;
    }

    ui->tableWidget->setEnabled(true);

    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);

    ui->pushButton_5->setEnabled(true);
    ui->pushButton_6->setEnabled(true);
    ui->pushButton_7->setEnabled(true);

    informationList.setFilePath(path.toStdString());


    int i = 0;
    for(auto it = informationList.list().begin(); it != informationList.list().end(); ++it, ++i){
//        if(it == ListOnArray<InformationList>::iterator(nullptr))
//            return;

        ui->tableWidget->insertRow(i);

        MyLineEdit *editor;

        editor = new MyLineEdit(this);
        connect(editor, SIGNAL(myEditingFinished()), SLOT(slotFinishEditing()));
//        connect(editor, SIGNAL(textEdited(const QString &)), SLOT(slotFinishEditing(const QString &)));
        editor->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-ZА-Яa-zа-я]+")));
        editor->setText(QString::fromStdString(it->lastName()));
        ui->tableWidget->setCellWidget(i, 0, editor);

        editor = new MyLineEdit(this);
        connect(editor, SIGNAL(myEditingFinished()), SLOT(slotFinishEditing()));
//        connect(editor, SIGNAL(textEdited(const QString &)), SLOT(slotFinishEditing(const QString &)));
        editor->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-ZА-Яa-zа-я]+")));
        editor->setText(QString::fromStdString(it->name()));
        ui->tableWidget->setCellWidget(i, 1, editor);

        editor = new MyLineEdit(this);
        connect(editor, SIGNAL(myEditingFinished()), SLOT(slotFinishEditing()));
//        connect(editor, SIGNAL(textEdited(const QString &)), SLOT(slotFinishEditing(const QString &)));
        editor->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-ZА-Яa-zа-я]+")));
        editor->setText(QString::fromStdString(it->patronymic()));
        ui->tableWidget->setCellWidget(i, 2, editor);

        editor = new MyLineEdit(this);
        editor->setEmptyString("0");
        connect(editor, SIGNAL(myEditingFinished()), SLOT(slotFinishEditing()));
//        connect(editor, SIGNAL(textEdited(const QString &)), SLOT(slotFinishEditing(const QString &)));
        editor->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9]{0,6}")));
//        editor->setInputMask("999999");
        editor->setText(QString::fromStdString(it->group()));
        ui->tableWidget->setCellWidget(i, 3, editor);

        QDoubleSpinBox *doubleSpinBox = new QDoubleSpinBox;
        connect(doubleSpinBox, SIGNAL(editingFinished()), SLOT(slotFinishEditing()));
        doubleSpinBox->setRange(0, 10);
        doubleSpinBox->setValue(it->grade());
        ui->tableWidget->setCellWidget(i, 4, doubleSpinBox);

        editor = new MyLineEdit(this);
        editor->setEmptyString("0");
        connect(editor, SIGNAL(myEditingFinished()), SLOT(slotFinishEditing()));
        editor->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9]{0,18}")));
        editor->setText(QString::number(it->income()));
        ui->tableWidget->setCellWidget(i, 5, editor);
    }

    areOpeningFile = false;

    on_lineEdit_textEdited(ui->lineEdit->text());
    on_lineEdit_2_textEdited(ui->lineEdit_2->text());
}

void Widget::slotFinishEditing()
{
    if(areOpeningFile)
        return;

    qDebug() << "w3";
    ListOnArray<Information> list;


    for(int i = 0; i < informationList.list().size(); ++i){
        list.push_back(Information(static_cast<MyLineEdit *>(ui->tableWidget->cellWidget(i, 0))->text().toStdString(),
                                   static_cast<MyLineEdit *>(ui->tableWidget->cellWidget(i, 1))->text().toStdString(),
                                   static_cast<MyLineEdit *>(ui->tableWidget->cellWidget(i, 2))->text().toStdString(),
                                   static_cast<MyLineEdit *>(ui->tableWidget->cellWidget(i, 3))->text().toStdString(),
                                   static_cast<QDoubleSpinBox *>(ui->tableWidget->cellWidget(i, 4))->value(),
                                   static_cast<MyLineEdit *>(ui->tableWidget->cellWidget(i, 5))->text().toULongLong()));
    }
    informationList.setList(std::move(list));
}


void Widget::on_pushButton_clicked()
{
    std::string temp = InformationDialog::input(this);

    if(!Information::informationStringIsCorrect(temp))
        return;

    Information information(temp);

    ui->tableWidget->insertRow(informationList.list().size());

    MyLineEdit *editor;

    editor = new MyLineEdit(this);
    connect(editor, SIGNAL(myEditingFinished()), SLOT(slotFinishEditing()));
//        connect(editor, SIGNAL(textEdited(const QString &)), SLOT(slotFinishEditing(const QString &)));
    editor->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-ZА-Яa-zа-я]+")));
    editor->setText(QString::fromStdString(information.lastName()));
    ui->tableWidget->setCellWidget(informationList.list().size(), 0, editor);

    editor = new MyLineEdit(this);
    connect(editor, SIGNAL(myEditingFinished()), SLOT(slotFinishEditing()));
//        connect(editor, SIGNAL(textEdited(const QString &)), SLOT(slotFinishEditing(const QString &)));
    editor->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-ZА-Яa-zа-я]+")));
    editor->setText(QString::fromStdString(information.name()));
    ui->tableWidget->setCellWidget(informationList.list().size(), 1, editor);

    editor = new MyLineEdit(this);
    connect(editor, SIGNAL(myEditingFinished()), SLOT(slotFinishEditing()));
//        connect(editor, SIGNAL(textEdited(const QString &)), SLOT(slotFinishEditing(const QString &)));
    editor->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-ZА-Яa-zа-я]+")));
    editor->setText(QString::fromStdString(information.patronymic()));
    ui->tableWidget->setCellWidget(informationList.list().size(), 2, editor);

    editor = new MyLineEdit(this);
    editor->setEmptyString("0");
    connect(editor, SIGNAL(myEditingFinished()), SLOT(slotFinishEditing()));
//        connect(editor, SIGNAL(textEdited(const QString &)), SLOT(slotFinishEditing(const QString &)));
    editor->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9]{0,6}")));
//        editor->setInputMask("999999");
    editor->setText(QString::fromStdString(information.group()));
    ui->tableWidget->setCellWidget(informationList.list().size(), 3, editor);

    QDoubleSpinBox *doubleSpinBox = new QDoubleSpinBox;
    connect(doubleSpinBox, SIGNAL(editingFinished()), SLOT(slotFinishEditing()));
    doubleSpinBox->setRange(0, 10);
    doubleSpinBox->setValue(information.grade());
    ui->tableWidget->setCellWidget(informationList.list().size(), 4, doubleSpinBox);

    editor = new MyLineEdit(this);
    editor->setEmptyString("0");
    connect(editor, SIGNAL(myEditingFinished()), SLOT(slotFinishEditing()));
    editor->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9]{0,18}")));
    editor->setText(QString::number(information.income()));
    ui->tableWidget->setCellWidget(informationList.list().size(), 5, editor);

    informationList.pushBack(std::move(information));
}


void Widget::on_pushButton_3_clicked()
{
    informationList.qsort();

    areOpeningFile = true;

    while(ui->tableWidget->rowCount()){

        ui->tableWidget->removeRow(0);
        qDebug() << ui->tableWidget->rowCount();
    }

    int i = 0;
    for(auto it = informationList.list().begin(); it != informationList.list().end(); ++it, ++i){
//        if(it == ListOnArray<InformationList>::iterator(nullptr))
//            return;

        ui->tableWidget->insertRow(i);

        MyLineEdit *editor;

        editor = new MyLineEdit(this);
        connect(editor, SIGNAL(myEditingFinished()), SLOT(slotFinishEditing()));
//        connect(editor, SIGNAL(textEdited(const QString &)), SLOT(slotFinishEditing(const QString &)));
        editor->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-ZА-Яa-zа-я]+")));
        editor->setText(QString::fromStdString(it->lastName()));
        ui->tableWidget->setCellWidget(i, 0, editor);

        editor = new MyLineEdit(this);
        connect(editor, SIGNAL(myEditingFinished()), SLOT(slotFinishEditing()));
//        connect(editor, SIGNAL(textEdited(const QString &)), SLOT(slotFinishEditing(const QString &)));
        editor->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-ZА-Яa-zа-я]+")));
        editor->setText(QString::fromStdString(it->name()));
        ui->tableWidget->setCellWidget(i, 1, editor);

        editor = new MyLineEdit(this);
        connect(editor, SIGNAL(myEditingFinished()), SLOT(slotFinishEditing()));
//        connect(editor, SIGNAL(textEdited(const QString &)), SLOT(slotFinishEditing(const QString &)));
        editor->setValidator(new QRegularExpressionValidator(QRegularExpression("^^[A-ZА-Яa-zа-я]+")));
        editor->setText(QString::fromStdString(it->patronymic()));
        ui->tableWidget->setCellWidget(i, 2, editor);

        editor = new MyLineEdit(this);
        editor->setEmptyString("0");
        connect(editor, SIGNAL(myEditingFinished()), SLOT(slotFinishEditing()));
//        connect(editor, SIGNAL(textEdited(const QString &)), SLOT(slotFinishEditing(const QString &)));
        editor->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9]{0,6}")));
//        editor->setInputMask("999999");
        editor->setText(QString::fromStdString(it->group()));
        ui->tableWidget->setCellWidget(i, 3, editor);

        QDoubleSpinBox *doubleSpinBox = new QDoubleSpinBox;
        connect(doubleSpinBox, SIGNAL(editingFinished()), SLOT(slotFinishEditing()));
        doubleSpinBox->setRange(0, 10);
        doubleSpinBox->setValue(it->grade());
        ui->tableWidget->setCellWidget(i, 4, doubleSpinBox);

        editor = new MyLineEdit(this);
        editor->setEmptyString("0");
        connect(editor, SIGNAL(myEditingFinished()), SLOT(slotFinishEditing()));
        editor->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9]{0,18}")));
        editor->setText(QString::number(it->income()));
        ui->tableWidget->setCellWidget(i, 5, editor);
    }

    areOpeningFile = false;
}


void Widget::on_pushButton_5_clicked()
{
    Form::showTable(informationList.searchByLastName(ui->lineEdit_2->text().toStdString()));
}


void Widget::on_pushButton_6_clicked()
{
    Form::showTable(informationList.searchByIncome(ui->lineEdit->text().toULongLong()));
}


void Widget::on_pushButton_7_clicked()
{
    Form::showTable(informationList.searchByIncome());
}


void Widget::on_lineEdit_2_textEdited(const QString &arg1)
{
    if(arg1.isEmpty() || !ui->tableWidget->isEnabled())
        ui->pushButton_5->setEnabled(false);
    else
        ui->pushButton_5->setEnabled(true);
}


void Widget::on_lineEdit_textEdited(const QString &arg1)
{
    if(arg1.isEmpty() || !ui->tableWidget->isEnabled())
        ui->pushButton_6->setEnabled(false);
    else
        ui->pushButton_6->setEnabled(true);
}


void Widget::on_pushButton_2_clicked()
{
    if(informationList.list().size() == 0)
        return;
    bool ok;
    int selectedRow = QInputDialog::getInt(this, "deleteing", "Select the line to be deleted",
                                     1, 1, ui->tableWidget->rowCount(), 1, &ok);
    if(!ok)
        return;

    ui->tableWidget->removeRow(selectedRow - 1);
    informationList.erase(selectedRow - 1);
}

