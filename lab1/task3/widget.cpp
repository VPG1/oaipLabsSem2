
#include "widget.h"
#include "inputdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStringList>
#include <QTableWidget>
#include <QPushButton>
#include <QDate>
#include <ctime>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QProcess>
#include "inputdialog.h"
#include <cstdlib>
#include <fstream>
#include "datevector.h"
#include <QGridLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      m_currentDay(QDate::currentDate().day(),
                 static_cast<Date::MonthType>(QDate::currentDate().month()),
                 QDate::currentDate().year()
                 ),
      m_currentPath(""),
      m_currentRow(-1),
      m_currentColumn(-1)
{
    pTableWidget = new QTableWidget;
    pTableWidget->setColumnCount(3);
    pTableWidget->setHorizontalHeaderLabels(QStringList()
                                            << "current day"
                                            << "next day"
                                            << "difference between current and next element in the collection"
                                            );

    pTableWidget->setColumnWidth(2, pTableWidget->width()
                                 - pTableWidget->columnWidth(0) - pTableWidget->columnWidth(1));

    // делаем таблицу недоступной для реактирования
    pTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QPushButton *pPushButtonAdd = new QPushButton("add");
    QPushButton *pPushButtonChange = new QPushButton("change");
    QPushButton *pPushButtonForOpenFile = new QPushButton("open .txt file");


    QLabel *pLabel = new QLabel("Enter your date of birth:");
    pLineEdit = new QLineEdit();


    pLabelForMethods = new QLabel;
    pLabelForMethods->setAlignment(Qt::AlignCenter);
    pPushButtonForMethods = new QPushButton("Calculate");
    // делаем кнопку изначально недоступной
    pPushButtonForMethods->setEnabled(false);



    //Layout setup
    QGridLayout *pBottomLeftHBoxLayout = new QGridLayout;
    pBottomLeftHBoxLayout->addWidget(pPushButtonAdd, 0, 0);
    pBottomLeftHBoxLayout->addWidget(pPushButtonChange, 0, 1);
    pBottomLeftHBoxLayout->addWidget(pPushButtonForOpenFile, 1, 0, 1, 2);

    QVBoxLayout *pLeftVBoxLayout = new QVBoxLayout;
    pLeftVBoxLayout->addWidget(pTableWidget);
    pLeftVBoxLayout->addLayout(pBottomLeftHBoxLayout);



    QHBoxLayout *pBottomRightHBoxLayout = new QHBoxLayout;
    pBottomRightHBoxLayout->addWidget(pLabel);
    pBottomRightHBoxLayout->addWidget(pLineEdit);
    pBottomRightHBoxLayout->addWidget(pPushButtonForMethods);

    QVBoxLayout *pRightVBoxLayout = new QVBoxLayout;
    pRightVBoxLayout->addWidget(pLabelForMethods);
    pRightVBoxLayout->addLayout(pBottomRightHBoxLayout);



    QHBoxLayout *pMainLayout = new QHBoxLayout;
    pMainLayout->addLayout(pLeftVBoxLayout);
    pMainLayout->addLayout(pRightVBoxLayout);

    setLayout(pMainLayout);

    // проверяем ввод на корректность
    connect(pLineEdit, SIGNAL(textEdited(QString)), SLOT(isCorrectInput()));
    // при нажатии на кнопку создается окно ввода
    connect(pPushButtonForMethods, SIGNAL(clicked()), SLOT(demonstrateMethods()));
    //
    connect(pPushButtonForOpenFile, SIGNAL(clicked()), SLOT(openTxtFile()));

    connect(pPushButtonAdd, SIGNAL(clicked()), SLOT(addDate()));

    connect(pTableWidget, SIGNAL(cellClicked(int, int)), SLOT(coordOfCell(int, int)));

    connect(pTableWidget, SIGNAL(itemSelectionChanged()), SLOT(checkNumberOfSelectedItem()));

    connect(pPushButtonChange, SIGNAL(clicked()), SLOT(changeDate()));

}

bool Widget::isCorrectFile(const QString &path)
{
    std::ifstream fin(path.toStdString());

    assert(fin.is_open());

    while(!fin.eof()){
        std::string date;
        fin >> date;

        if(date == "")
            break;
        if(!Date::inputIsDateFormat(QString::fromStdString(date))){
            fin.close();
            return false;
        }
    }

    fin.close();
    return true;
}

void Widget::fillTable(const QString &path)
{
    qDebug() << path << '\n';
    std::ifstream fin(path.toStdString());

    assert(fin.is_open());

    while(!fin.eof()){
        std::string date;
        fin >> date;

        if(date == "")
            break;

        assert(Date::inputIsDateFormat(QString::fromStdString(date)));
        array.append(Date(QString::fromStdString(date)));
    }

    fin.close();

    pTableWidget->setRowCount(array.size());

    for(int i = 0; i < array.size(); ++i){
        pTableWidget->setItem(i, 0, new QTableWidgetItem(array[i].dateToString()));

        pTableWidget->setItem(i, 1, new QTableWidgetItem(array[i].nextDate().dateToString()));

        if(i != array.size() - 1){
            pTableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(array[i].duration(array[i + 1]))));
        }
        else{
            pTableWidget->setItem(i, 2, new QTableWidgetItem("last element of collection"));
        }

    }

}


void Widget::isCorrectInput()
{
    if(Date::inputIsDateFormat(pLineEdit->text())){
        pPushButtonForMethods->setEnabled(true);
        connect(pLineEdit, SIGNAL(returnPressed()), pPushButtonForMethods, SIGNAL(clicked()));
    }
    else{
        pPushButtonForMethods->setEnabled(false);
        disconnect(pLineEdit, SIGNAL(returnPressed()), pPushButtonForMethods, SIGNAL(clicked()));
    }
}



void Widget::demonstrateMethods()
{
    QString input = InputDialog::createInputDialog("enter the date the number "
                                                   "of days until which you want to know");

    //учитываем нажатие пользователем крестика
    if(!Date::inputIsDateFormat(input)){
        return;
    }


    pLabelForMethods->setText(QString("current day: %1\n"
                                      "next day: %2\n"
                                      "previous day: %3\n"
                                      "week number: %4\n"
                                      "%5\n"
                                      "days till your birthday: %6\n"
                                      "days till %7: %8")
                              .arg(m_currentDay.dateToString())
                              .arg(m_currentDay.nextDate().dateToString())
                              .arg(m_currentDay.previousDate().dateToString())
                              .arg(m_currentDay.weekNumber())
                              .arg(m_currentDay.isLeap() ? "year is Leap" : "year isn't leap")
                              .arg(m_currentDay.daysTillYourBirthDay(Date(pLineEdit->text())))
                              .arg(input).arg(m_currentDay.duration(Date(input)))
                              );
}


void Widget::openTxtFile()
{
    QString selectedPath = QFileDialog::getOpenFileName(this, "Chose .txt file",
                                               QDir::rootPath(), "Text files (*.txt)");
//    qDebug() << "what are";

//    system(("open " + m_currentPath).toLatin1().data());

    // проверкой на то что selectedPath не является пустой строкой мы учитываем нажате пользователем кнопки отмены
    if(selectedPath == ""){
        return;
    }

    if(isCorrectFile(selectedPath)){
        // очищаем массив перед заполнением
        array.clear();
        // меняем текущий путь на выбранный
        m_currentPath = selectedPath;
        // заполняем таблицу
        fillTable(m_currentPath);
    }
    else{
        QMessageBox::warning(this, "warning", "this file is't suitable");
    }
}

void Widget::addDate()
{
    // проверям на то выбрал ли пользователь какой либо путь
    // переменная m_currentPath инициализируется пустой строкой
    if(m_currentPath == "")
        return;

    QString input = InputDialog::createInputDialog("Enter date");

    //учитываем нажатие пользователем крестика
    if(Date::inputIsDateFormat(input)){
        return;
    }

    std::ofstream fout(m_currentPath.toStdString(), std::ios::app);
    assert(fout.is_open());

    fout << " " << input.toStdString();

    fout.close();

    array.append(Date(input));

    pTableWidget->setRowCount(array.size());

    // замения элемент последней строки третьего элемента
    int indexOfLastEl = array.size() - 1;

    pTableWidget->setItem(indexOfLastEl - 1, 2,
                          new QTableWidgetItem(QString::number(array[indexOfLastEl - 1].duration(array[indexOfLastEl]))));

    // добовляем строку
    pTableWidget->setItem(indexOfLastEl, 0, new QTableWidgetItem(array[indexOfLastEl].dateToString()));
    pTableWidget->setItem(indexOfLastEl, 1, new QTableWidgetItem(array[indexOfLastEl].nextDate().dateToString()));
    pTableWidget->setItem(indexOfLastEl, 2, new QTableWidgetItem("last element of collection"));
}

void Widget::changeDate()
{

    if((m_currentRow == -1 && m_currentColumn == -1))
        return;

    QString date = InputDialog::createInputDialog("Enter new current date");

    //учитываем нажатие пользователем крестика
    if(Date::inputIsDateFormat(date)){
        return;
    }

    array[m_currentRow] = Date(date);

    pTableWidget->setItem(m_currentRow, 0, new QTableWidgetItem(array[m_currentRow].dateToString()));
    pTableWidget->setItem(m_currentRow, 1, new QTableWidgetItem(array[m_currentRow].nextDate().dateToString()));

    if(m_currentRow != array.size() - 1){
        pTableWidget->setItem(m_currentRow, 2,
                              new QTableWidgetItem(QString::number(array[m_currentRow].duration(array[m_currentRow + 1]))));
    }

    if(m_currentRow != 0){
        pTableWidget->setItem(m_currentRow - 1, 2,
                              new QTableWidgetItem(QString::number(array[m_currentRow - 1].duration(array[m_currentRow]))));
    }

    std::ofstream fout(m_currentPath.toStdString(), std::ios::trunc);
    assert(fout.is_open());
    for(int i = 0; i < array.size(); ++i){
        fout << array[i];
        if(i != array.size() - 1)
            fout << " ";
    }
    fout.close();
}

void Widget::coordOfCell(int row, int column)
{
    m_currentRow = row;
    m_currentColumn = column;
}

void Widget::checkNumberOfSelectedItem()
{
    if(pTableWidget->selectedItems().size() > 1){
        m_currentRow = -1;
        m_currentColumn = -1;
    }
}



