#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include "inputdialog.h"
#include "datevector.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
private:
    QTableWidget *pTableWidget;
    QLineEdit *pLineEdit;

// label для демонстации методов класса
    QLabel *pLabelForMethods;
    QPushButton *pPushButtonForMethods;

    Date m_currentDay;
    QString m_currentPath; // путь к текущему выбраному фаилу
    DateVector array;
    int m_currentRow;
    int m_currentColumn;

// метод заполнения таблицы
    bool isCorrectFile(const QString &path);
    void fillTable(const QString &path);

public slots:
    void isCorrectInput();
    void demonstrateMethods();
    void openTxtFile();
    void addDate();
    void changeDate();
    void coordOfCell(int row, int column);
    void checkNumberOfSelectedItem();
};
#endif // WIDGET_H
