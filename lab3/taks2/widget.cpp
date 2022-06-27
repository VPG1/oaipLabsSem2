#include "widget.h"
#include "ui_widget.h"
#include "stack.h"
#include <QFileDialog>
#include <fstream>
#include <QMessageBox>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->label->setText("Success\n\n");
    ui->label->setStyleSheet("color: rgb(99, 200, 86)");

}

Widget::~Widget()
{

    delete ui;
}



void Widget::on_plainTextEdit_textChanged()
{
    checkText(ui->plainTextEdit->toPlainText().toStdString());
    if(indexOfRow == -1 && indexOfColumn == -1){
        ui->label->setText("Success\n\n");
        ui->label->setStyleSheet("color: rgb(99, 200, 86)");

    }
    else{
        ui->label->setText(QString("Unsucces\n"
                                   "Row: %1\n"
                                   "Column: %2").arg(indexOfRow).arg(indexOfColumn));
        ui->label->setStyleSheet("color: rgb(237, 107, 96)");
    }
}

void Widget::checkText(const std::string &text)
{
    Stack<Bracket> stack;

    indexOfRow = 1;
    indexOfColumn = 1;
    for(std::size_t i = 0; i < text.size(); ++i, ++indexOfColumn){
        switch(static_cast<char>(text[i])){
        case '(':
            stack.push(Bracket{')', indexOfRow, indexOfColumn + 1});
            break;
        case '[':
            stack.push(Bracket{']', indexOfRow, indexOfColumn + 1});
            break;
        case '{':
            stack.push(Bracket{'}', indexOfRow, indexOfColumn + 1});
            break;
        case ')':
        case ']':
        case '}':
            if(stack.empty()){
//                indexOfColumn = i + 1;
                return;
            }

            if(stack.top() != text[i]){
//                indexOfColumn = i + 1;
                return;
            }

            stack.pop();

            break;

        case '\n':
            ++indexOfRow;
            indexOfColumn = 1;
            break;
        default:
            break;
        }
    }

    if(stack.empty()){
        indexOfRow = -1;
        indexOfColumn = -1;
        return;
    }

    int tempSize = stack.size();
    for(int i = 0; i < tempSize - 1; ++i){
        stack.pop();
    }
    indexOfRow = stack.top().indexOfRow;
    indexOfColumn = stack.top().indexOfColumn;
}


void Widget::on_pushButton_clicked()
{
    QString selectedPath = QFileDialog::getOpenFileName(this, "Chose .txt file",
                                               QDir::rootPath(), "Text files (*.txt)");

    if(selectedPath == "")
        return;

    std::ifstream in(selectedPath.toStdString());
    assert(in.is_open());

    std::string text;

    while(!in.eof()){
        std::string tmp;
        getline(in, tmp);
        text += tmp + '\n';
    }
    in.close();

    checkText(text);

    if(indexOfRow == -1 && indexOfColumn == -1)
        QMessageBox::about(this, "about", "Success");
    else
        QMessageBox::about(this, "about", QString("Unsucess\n"
                                                  "Row: %1\n"
                                                  "Column: %2\n").arg(indexOfRow).arg(indexOfColumn));
}

