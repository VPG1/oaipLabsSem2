#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    string str;
    std::cout << "qwer";
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    Tokenizer tokenizer(ui->plainTextEdit->toPlainText().toLatin1().data());
    Parser parser(tokenizer.tokenize());
    parser.parse();

    for(int i = 0; i < ui->treeWidget->topLevelItemCount(); ++i)
        delete ui->treeWidget->topLevelItem(0)->child(i);

    ui->treeWidget->clear();


    // отображаем переменные
    auto varMap = parser.getVars();
    auto topLvlItemVars = new QTreeWidgetItem(ui->treeWidget);

    int numOfLocalVariables = 0;
    for(auto el1 : varMap){
        auto item = new QTreeWidgetItem(ui->treeWidget->topLevelItem(0));

        int numOfVars  = 0;
        for(auto el2 : el1.second){
            QString pos;
            if(el2.getIsLocal()){
                pos = QString("\tposition: (%1, %2)").arg(el2.getPos().first).arg(el2.getPos().second);
                ++numOfLocalVariables;
            }
            QString value;
            if(el2.getValue().has_value()){
                value = QString("\tvalue: %1").arg(el2.getValue().value().c_str());
            }

            auto item2 = new QTreeWidgetItem(item);
            item2->setText(0, QString::fromLatin1(el2.getName().c_str()) + pos + value);
            ++numOfVars;
        }

        item->setText(0, QString::fromLatin1(el1.first.c_str()) + QString("\tcount: %1").arg(numOfVars));
    }

    topLvlItemVars->setText(0, "variables" + QString("\tlocal: %1").arg(numOfLocalVariables));


    // отображаем функции
    auto funcsMap = parser.getFuncs();
    auto topLvlItemFuncs = new QTreeWidgetItem(ui->treeWidget);

    for(auto el1 : funcsMap){
        auto item = new QTreeWidgetItem(ui->treeWidget->topLevelItem(1));

        item->setText(0, QString::fromLatin1(el1.first.c_str()) + (el1.second.size() >= 2 ? QString("\tnumber of overload: %1").arg(el1.second.size() - 1) : ""));
        for(auto el2 : el1.second){
            auto item2 = new QTreeWidgetItem(item);
            item2->setText(0, QString::fromLatin1(el2.getFuncString().c_str()) + QString("\tposition: (%1, %2)").arg(el2.getPos().first).arg(el2.getPos().second));
        }
    }

    topLvlItemFuncs->setText(0, "functions");


    // отображаем количество символов
    auto topLvlItemNumOfArray = new QTreeWidgetItem(ui->treeWidget);

    topLvlItemNumOfArray->setText(0, QString("number of arrays: %1").arg(parser.getNumOfArray()));


    // отображаем позиции изменения
    auto topLvlItemChangingPos = new QTreeWidgetItem(ui->treeWidget);

    topLvlItemChangingPos->setText(0, QString("variable change coordinates"));

    for(auto el : parser.getCoordsOfChanging()){
        auto item = new QTreeWidgetItem(topLvlItemChangingPos);

        item->setText(0, QString("(%1, %2)").arg(el.first).arg(el.second));
    }



    // отображаем глубину всех ветвлений
    auto topLvlItemBranching = new QTreeWidgetItem(ui->treeWidget);
    topLvlItemBranching->setText(0, "branching");

    for(auto el : parser.getDepthOfBranching()){
        auto item = new QTreeWidgetItem(topLvlItemBranching);
        item->setText(0, QString::number(el));
    }


    // отоброжаем координаты логических ошибок
    auto topLvlItemLogicalError = new QTreeWidgetItem(ui->treeWidget);
    topLvlItemLogicalError->setText(0, "coords of logical errors\tcount:" + QString::number(parser.getCoordsOfErrors().size()));

    for(auto el : parser.getCoordsOfErrors()){
        auto item = new QTreeWidgetItem(topLvlItemLogicalError);
        item->setText(0, QString("(%1, %2)").arg(el.first).arg(el.second));
    }

    ui->treeWidget->expandAll();
}

void Widget::on_pushButton_2_clicked()
{
    QString selectedPath = QFileDialog::getOpenFileName(this, "Chose src file",
                                               QDir::rootPath(), "Source file (*.cpp *.h)");

    if(selectedPath == ""){
        return;
    }

    QFile file(selectedPath);
    if(!file.open(QIODevice::ReadOnly)){
        return;
    }

    QByteArray data;
    data = file.readAll();


    ui->plainTextEdit->setPlainText(QString(data));
}

