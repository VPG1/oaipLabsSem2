#include "widget.h"
#include "ui_widget.h"
#include "form.h"
#include <QFileDialog>
#include <QLineEdit>
#include <QRegularExpressionValidator>
#include <QMessageBox>
#include <QDoubleSpinBox>
#include "mylineedit.h"
#include "statementdialog.h"
#include <QInputDialog>
#include <QModelIndex>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
//    ui->tableWidget->setHorizontalHeaderLabels(
//                QStringList() << "last name"
//                << "name" << "patronymic"
//                << "address" << "grade");
    ui->tableWidget->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_4->setEnabled(false);
    ui->pushButton_5->setEnabled(false);
    ui->pushButton_6->setEnabled(false);

    ui->lineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-ZА-Яa-zа-я]+")));

//    ui->tableWidget->resizeColumnsToContents();

}

Widget::~Widget()
{
    delete ui;
}




void Widget::on_pushButton_clicked()
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
    if(!ListAndFile::fileIsCorrect(path.toStdString())){
        qDebug() << "w2";
        ui->tableWidget->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
        ui->pushButton_6->setEnabled(false);
        QMessageBox::warning(this, "warning", "file doesn't fit");
        return;
    }

    ui->tableWidget->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(true);
    ui->pushButton_5->setEnabled(true);
    ui->pushButton_6->setEnabled(true);
    statementFileList.setFilePath(path.toStdString());


    int i = 0;
    for(auto it = statementFileList.getList().begin(); it != statementFileList.getList().end(); ++it, ++i){
        if(it == List<Statement>::iterator(nullptr))
            return;

        ui->tableWidget->insertRow(i);

        QLineEdit *editor;

        editor = new MyLineEdit(this);
        connect(editor, SIGNAL(myEditingFinished()), SLOT(slotFinishEditing()));
//        connect(editor, SIGNAL(textEdited(const QString &)), SLOT(slotFinishEditing(const QString &)));
        editor->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-ZА-Яa-zа-я]+")));
        editor->setText(QString::fromStdString((*it).lastName()));
        ui->tableWidget->setCellWidget(i, 0, editor);

        editor = new MyLineEdit(this);
        connect(editor, SIGNAL(myEditingFinished()), SLOT(slotFinishEditing()));
//        connect(editor, SIGNAL(textEdited(const QString &)), SLOT(slotFinishEditing(const QString &)));
        editor->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-ZА-Яa-zа-я]+")));
        editor->setText(QString::fromStdString((*it).name()));
        ui->tableWidget->setCellWidget(i, 1, editor);

        editor = new MyLineEdit(this);
        connect(editor, SIGNAL(myEditingFinished()), SLOT(slotFinishEditing()));
//        connect(editor, SIGNAL(textEdited(const QString &)), SLOT(slotFinishEditing(const QString &)));
        editor->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-ZА-Яa-zа-я]+")));
        editor->setText(QString::fromStdString((*it).patronymic()));
        ui->tableWidget->setCellWidget(i, 2, editor);

        editor = new MyLineEdit(this);
        connect(editor, SIGNAL(myEditingFinished()), SLOT(slotFinishEditing()));
//        connect(editor, SIGNAL(textEdited(const QString &)), SLOT(slotFinishEditing(const QString &)));
        editor->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-ZА-Яa-zа-я]+")));
        editor->setText(QString::fromStdString((*it).address()));
        ui->tableWidget->setCellWidget(i, 3, editor);

//        editor = new QLineEdit(this);
//        editor->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9]{1}[.,][0-9]+$")));
//        editor->setInputMask("");
//        editor->setText(QString::number((*it).grade()));
        QDoubleSpinBox *doubleSpinBox = new QDoubleSpinBox;
        connect(doubleSpinBox, SIGNAL(editingFinished()), SLOT(slotFinishEditing()));
        doubleSpinBox->setRange(0, 10);
        doubleSpinBox->setValue((*it).grade());
        ui->tableWidget->setCellWidget(i, 4, doubleSpinBox);

    }

    areOpeningFile = false;

    on_lineEdit_textEdited(ui->lineEdit->text());

}

void Widget::slotFinishEditing()
{
    if(areOpeningFile)
        return;

    qDebug() << "w3";
    List<Statement> list;


    for(int i = 0; i < statementFileList.getList().size(); ++i){
        list.push_back(Statement(static_cast<MyLineEdit *>(ui->tableWidget->cellWidget(i, 0))->text().toStdString(),
                                  static_cast<MyLineEdit *>(ui->tableWidget->cellWidget(i, 1))->text().toStdString(),
                                  static_cast<MyLineEdit *>(ui->tableWidget->cellWidget(i, 2))->text().toStdString(),
                                  static_cast<MyLineEdit *>(ui->tableWidget->cellWidget(i, 3))->text().toStdString(),
                                  static_cast<QDoubleSpinBox *>(ui->tableWidget->cellWidget(i, 4))->value()
                                  ));
    }
    statementFileList.setList(std::move(list));
}



void Widget::on_pushButton_2_clicked()
{
    std::string temp = StatementDialog::input(this);
    if(!Statement::statementStringIsCorrect(temp)){
        return;
    }

    Statement statement(temp);

    ui->tableWidget->insertRow(statementFileList.getList().size());

    QLineEdit *editor;

    editor = new MyLineEdit(this);
    connect(editor, SIGNAL(myEditingFinished()), SLOT(slotFinishEditing()));
    editor->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-ZА-Яa-zа-я]+")));
    editor->setText(QString::fromStdString(statement.lastName()));
    ui->tableWidget->setCellWidget(statementFileList.getList().size(), 0, editor);

    editor = new MyLineEdit(this);
    connect(editor, SIGNAL(myEditingFinished()), SLOT(slotFinishEditing()));
    editor->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-ZА-Яa-zа-я]+")));
    editor->setText(QString::fromStdString(statement.name()));
    ui->tableWidget->setCellWidget(statementFileList.getList().size(), 1, editor);

    editor = new MyLineEdit(this);
    connect(editor, SIGNAL(myEditingFinished()), SLOT(slotFinishEditing()));
    editor->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-ZА-Яa-zа-я]+")));
    editor->setText(QString::fromStdString(statement.patronymic()));
    ui->tableWidget->setCellWidget(statementFileList.getList().size(), 2, editor);

    editor = new MyLineEdit(this);
    connect(editor, SIGNAL(myEditingFinished()), SLOT(slotFinishEditing()));
    editor->setValidator(new QRegularExpressionValidator(QRegularExpression("v")));
    editor->setText(QString::fromStdString(statement.address()));
    ui->tableWidget->setCellWidget(statementFileList.getList().size(), 3, editor);

    QDoubleSpinBox *doubleSpinBox = new QDoubleSpinBox;
    connect(doubleSpinBox, SIGNAL(editingFinished()), SLOT(slotFinishEditing()));
    doubleSpinBox->setRange(0, 10);
    doubleSpinBox->setValue((statement.grade()));
    ui->tableWidget->setCellWidget(statementFileList.getList().size(), 4, doubleSpinBox);

    statementFileList.pushBack(std::move(statement));

//    ui->tableWidget->model()->data();
}


void Widget::on_pushButton_3_clicked()
{
    if(statementFileList.getList().size() == 0)
        return;
    bool ok;
    int selectedRow = QInputDialog::getInt(this, "deleting", "Select the line to be deleted",
                                       1, 1, ui->tableWidget->rowCount(), 1, &ok);
    if(!ok)
        return;

    ui->tableWidget->removeRow(selectedRow - 1);
    statementFileList.erase(selectedRow - 1);
}

void Widget::resizeEvent(QResizeEvent *event)
{
    int tableWidgetWidth = ui->tableWidget->width();

    ui->tableWidget->setColumnWidth(0, tableWidgetWidth / 5);
    ui->tableWidget->setColumnWidth(1, tableWidgetWidth / 5);
    ui->tableWidget->setColumnWidth(2, tableWidgetWidth / 5);
    ui->tableWidget->setColumnWidth(3, tableWidgetWidth / 5);
    ui->tableWidget->setColumnWidth(4, tableWidgetWidth / 5 - 16);

    QWidget::resizeEvent(event);
}

void Widget::on_lineEdit_textEdited(const QString &arg1)
{
    if(!arg1.isEmpty() && ui->tableWidget->isEnabled())
        ui->pushButton_4->setEnabled(true);
    else
        ui->pushButton_4->setEnabled(false);

}


void Widget::on_pushButton_4_clicked()
{
    Form::showTable(statementFileList.search(ui->lineEdit->text().toStdString()));

}


void Widget::on_pushButton_5_clicked()
{
    int i = 0;
    for(auto it = statementFileList.getList().begin(); it != statementFileList.getList().end();){
        qDebug() << (*it).grade();
        if((*it).grade() < ui->doubleSpinBox->value()){
            ++it;
            statementFileList.erase(i);
            ui->tableWidget->removeRow(i);
        }else{
            ++it;
            ++i;
        }
    }
}


void Widget::on_pushButton_6_clicked()
{
    statementFileList.qsort();

    areOpeningFile = true;

    while(ui->tableWidget->rowCount()){

        ui->tableWidget->removeRow(0);
        qDebug() << ui->tableWidget->rowCount();
    }

    int i = 0;
    for(auto it = statementFileList.getList().begin(); it != statementFileList.getList().end(); ++it, ++i){
        if(it == List<Statement>::iterator(nullptr))
            return;

        ui->tableWidget->insertRow(i);

        QLineEdit *editor;

        editor = new MyLineEdit(this);
        connect(editor, SIGNAL(myEditingFinished()), SLOT(slotFinishEditing()));
//        connect(editor, SIGNAL(textEdited(const QString &)), SLOT(slotFinishEditing(const QString &)));
        editor->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-ZА-Яa-zа-я]+")));
        editor->setText(QString::fromStdString((*it).lastName()));
        ui->tableWidget->setCellWidget(i, 0, editor);

        editor = new MyLineEdit(this);
        connect(editor, SIGNAL(myEditingFinished()), SLOT(slotFinishEditing()));
//        connect(editor, SIGNAL(textEdited(const QString &)), SLOT(slotFinishEditing(const QString &)));
        editor->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-ZА-Яa-zа-я]+")));
        editor->setText(QString::fromStdString((*it).name()));
        ui->tableWidget->setCellWidget(i, 1, editor);

        editor = new MyLineEdit(this);
        connect(editor, SIGNAL(myEditingFinished()), SLOT(slotFinishEditing()));
//        connect(editor, SIGNAL(textEdited(const QString &)), SLOT(slotFinishEditing(const QString &)));
        editor->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-ZА-Яa-zа-я]+")));
        editor->setText(QString::fromStdString((*it).patronymic()));
        ui->tableWidget->setCellWidget(i, 2, editor);

        editor = new MyLineEdit(this);
        connect(editor, SIGNAL(myEditingFinished()), SLOT(slotFinishEditing()));
//        connect(editor, SIGNAL(textEdited(const QString &)), SLOT(slotFinishEditing(const QString &)));
        editor->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-ZА-Яa-zа-я]+")));
        editor->setText(QString::fromStdString((*it).address()));
        ui->tableWidget->setCellWidget(i, 3, editor);

//        editor = new QLineEdit(this);
//        editor->setValidator(new QRegularExpressionValidator(QRegularExpression("^[0-9]{1}[.,][0-9]+$")));
//        editor->setInputMask("");
//        editor->setText(QString::number((*it).grade()));
        QDoubleSpinBox *doubleSpinBox = new QDoubleSpinBox;
        connect(doubleSpinBox, SIGNAL(editingFinished()), SLOT(slotFinishEditing()));
        doubleSpinBox->setRange(0, 10);
        doubleSpinBox->setValue((*it).grade());
        ui->tableWidget->setCellWidget(i, 4, doubleSpinBox);

    }
    areOpeningFile = false;
}

