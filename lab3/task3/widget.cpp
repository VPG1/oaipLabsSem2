#include "widget.h"
#include "ui_widget.h"
#include "myitemdelgate.h"
#include "expression.h"
#include <QMessageBox>
#include <iostream>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    MyItemDelegate *delegate1 = new MyItemDelegate(this);
    delegate1->setRegExp(QRegularExpression("[a-e()/*+-]+"));
    ui->tableWidget->setItemDelegateForColumn(0, delegate1);

    MyItemDelegate *delegate2 = new MyItemDelegate(this);
    delegate2->setRegExp(QRegularExpression("^(0|[1-9][0-9]*)([.][0-9]+)?"));
    for(int i = 1; i < 6; ++i){

        ui->tableWidget->setItemDelegateForColumn(i, delegate2);
    }

    const int arraySize = 15;
    Expression arr[arraySize] = {
        Expression("a/(b-c)*(d+e)", 8.6, 2.4, 5.1, 0.3, 7.9),
        Expression("(a+b)*(c-d)/e", 7.4, 3.6, 2.8, 9.5, 0.9),
        Expression("a-(b+c*d)/e", 3.1, 5.4, 0.2, 9.6, 7.8),
        Expression("a/b-((c+d)*e)", 1.2, 0.7, 9.3, 6.5, 8.4),
        Expression("a*(b-c+d)/e", 9.7, 8.2, 3.6, 4.1, 0.5),
        Expression("(a+b)*(c-d)/e", 0.8, 4.1, 7.9, 6.2, 3.5),
        Expression("a*(b-c)/(d+e)", 1.6, 4.9, 5.7, 0.8, 2.3),
        Expression("a/(b*(c+d))-e", 8.5, 0.3, 2.4, 7.9, 1.6),
        Expression("(a+(b/c-d))*e", 5.6, 7.4, 8.9, 3.1, 0.2),
        Expression("a*(b+c)/(d-e)", 0.4, 2.3, 6.7, 5.8, 9.1),
        Expression("a-(b/c*(d+e))", 5.6, 3.2, 0.9, 1.7, 4.8),
        Expression("(a-b)/(c+d)*e", 0.3, 6.7, 8.4, 9.5, 1.2),
        Expression("a/(b+c-d*e)", 7.6, 4.8, 3.5, 9.1, 0.2),
        Expression("a*(b-c)/(d+e)", 0.5, 6.1, 8.9, 2.4, 7.3),
        Expression("(a+b*c)/(d-e)", 9.1, 0.6, 2.4, 3.7, 8.5)
                         };


    for(int i = 0; i < arraySize; ++i){
        on_pushButton_clicked();
        ui->tableWidget->item(i, 0)->setText(QString::fromStdString(arr[i].getExpr()));
        ui->tableWidget->item(i, 1)->setText(QString::number(arr[i].getA()));
        ui->tableWidget->item(i, 2)->setText(QString::number(arr[i].getB()));
        ui->tableWidget->item(i, 3)->setText(QString::number(arr[i].getC()));
        ui->tableWidget->item(i, 4)->setText(QString::number(arr[i].getD()));
        ui->tableWidget->item(i, 5)->setText(QString::number(arr[i].getE()));

        assert(expressionAreCorrect(arr[i].getExpr()) && char('0' + i));

        qDebug() << QString::fromStdString(convertToPostfixForm(ui->tableWidget->item(i, 0)->text().toStdString()));

        ui->tableWidget->item(i, 6)->setText(QString::number(calculate(convertToPostfixForm(ui->tableWidget->item(i, 0)->text().toStdString()),
                                                                       ui->tableWidget->item(i, 1)->text().toDouble(),
                                                                       ui->tableWidget->item(i, 2)->text().toDouble(),
                                                                       ui->tableWidget->item(i, 3)->text().toDouble(),
                                                                       ui->tableWidget->item(i, 4)->text().toDouble(),
                                                                       ui->tableWidget->item(i, 5)->text().toDouble()), 'g', 4));
    }
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    int insertingRow = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(insertingRow);
    for(int i = 0; i < 6; ++i){
        QTableWidgetItem *item = new QTableWidgetItem;
        ui->tableWidget->setItem(insertingRow, i, item);
    }
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    ui->tableWidget->setItem(insertingRow, 6, item);
//    ui->tableWidget->setItemDelegate(
//    ui->tableWidget->item(insertingRow, 0)->setFlags(ui->tableWidget->item(insertingRow, 0)->flags() & ~Qt::ItemIsEditable);
//    Qt::ItemFlags
}

int Widget::opPriority(char c){
    switch(c){
    case '/':
    case '*':
        return 2;
    case '+':
    case '-':
        return 1;
    }
    assert(false);
}

bool Widget::isVar(char c){
    return c != '(' && c != ')' && c != '/' &&
            c != '*' && c != '+' && c != '-';
}

bool Widget::isOp(char c){
    return c == '/' || c == '*' || c == '+' || c == '-';
}

std::string Widget::convertToPostfixForm(const std::string &str){
    std::string resString;
    std::stack<char> stack;
    for(std::size_t i = 0; i < str.size(); ++i){
        if(isVar(str[i])){
            resString += str[i];
        }
        else if(isOp(str[i])){
            if(stack.empty() || stack.top() == '('){
                stack.push(str[i]);
            }
            else if(opPriority(str[i]) > opPriority(stack.top())){
                stack.push(str[i]);
            }
            else if(opPriority(str[i]) <= opPriority(stack.top())){
                while(!stack.empty() && stack.top() != '(' &&
                      opPriority(str[i]) <= opPriority(stack.top())){
                    resString += stack.top();
                    stack.pop();
                }
                stack.push(str[i]);
            }
        }
        else if(str[i] == '('){
            stack.push(str[i]);
        }
        else if(str[i] == ')'){
            while(stack.top() != '('){
                resString += stack.top();
                stack.pop();
            }
            stack.pop();
        }
    }
    while(!stack.empty()){
        resString += stack.top();
        stack.pop();
    }
    return resString;
}

double Widget::calculate(const std::string &str, double a, double b,
                         double c, double d, double e)
{
    std::stack<double> stack;
    for(std::size_t i = 0; i < str.size(); ++i){
        if(isVar(str[i])){
            switch(str[i]){
            case 'a':
                stack.push(a);
                break;
            case 'b':
                stack.push(b);
                break;
            case 'c':
                stack.push(c);
                break;
            case 'd':
                stack.push(d);
                break;
            case 'e':
                stack.push(e);
                break;
            default:
                assert(false);
            }
        }
        else if(isOp(str[i])){
            double rightOperator = stack.top();
            stack.pop();
            double leftOperator = stack.top();
            stack.pop();

            switch(str[i]){
            case '/':
                stack.push(leftOperator / rightOperator);
                break;
            case '*':
                stack.push(leftOperator * rightOperator);
                break;
            case '+':
                stack.push(leftOperator + rightOperator);
                break;
            case '-':
                stack.push(leftOperator - rightOperator);
            }
        }
    }

    return stack.top();
}

bool Widget::expressionAreCorrect(const std::string &str)
{
    qDebug() << QString::fromStdString(str);
    if(isOp(str[0])){
        return false;
    }
    if(isOp(str[str.size() - 1])){
        return false;
    }


    bool prevNonBracketSymbolExist = false;
    char prevNonBracketSymbol;
    std::stack<char> stack;
    bool opBetween = false;

    for(std::size_t i = 0; i < str.size(); ++i){


//        else if(str[i] == '('){
//            ++numberOfOpenBrackets;
//        }
//        else{
//            ++numberOfCloseBrackets;
//        }

        if(prevNonBracketSymbolExist && isOp(str[i]) && isOp(prevNonBracketSymbol)){
            return false;
        }
        if(prevNonBracketSymbolExist && isVar(str[i]) && isVar(prevNonBracketSymbol)){
            return false;
        }

        if(i != 0 && str[i] == ')' && isOp(str[i - 1])){
            return false;
        }
        if(i != str.size() - 1 && str[i] == '(' && isOp(str[i + 1])){
            return false;
        }



        switch(str[i]){
        case '(':
            stack.push(str[i]);
            break;
        case ')':
            if(stack.empty()){
                return false;
            }

            stack.pop();

            if(!opBetween){
               return false;
            }

            break;
        case '/':
        case '*':
        case '+':
        case '-':
            if(stack.empty()){
                break;
            }
            if(stack.top() == '('){
                opBetween = true;
            }
            else if(stack.top() == ')'){
                opBetween = false;
            }
            break;
        }


        if((str[i] != '(') && (str[i] != ')')){
            prevNonBracketSymbol = str[i];
            prevNonBracketSymbolExist = true;
        }
    }

    return stack.empty();
}


void Widget::on_pushButton_2_clicked()
{
    for(int i = 0; i < ui->tableWidget->rowCount(); ++i){
        if(!expressionAreCorrect(ui->tableWidget->item(i, 0)->text().toStdString()) || ui->tableWidget->item(i, 0)->text().isEmpty()){
            QMessageBox::warning(this, "warning", QString("incorrect expression in %1 row").arg(i + 1));
            return;
        }
        for(int j = 1; j < 6; ++j){
            if(ui->tableWidget->item(i, j)->text().isEmpty()){
                QMessageBox::warning(this, "warning", QString("cell(%1, %2) is empty").arg(i + 1).arg(char(j - 1 + 'a')));
                return;
            }
        }
        ui->tableWidget->item(i, 6)->setText(QString::number(calculate(convertToPostfixForm(ui->tableWidget->item(i, 0)->text().toStdString()),
                                                                       ui->tableWidget->item(i, 1)->text().toDouble(),
                                                                       ui->tableWidget->item(i, 2)->text().toDouble(),
                                                                       ui->tableWidget->item(i, 3)->text().toDouble(),
                                                                       ui->tableWidget->item(i, 4)->text().toDouble(),
                                                                       ui->tableWidget->item(i, 5)->text().toDouble()), 'g', 4));

    }


}

