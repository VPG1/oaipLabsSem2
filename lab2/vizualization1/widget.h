#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "stack.h"
#include "list.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

    struct Weight{
        QString str;
        char weight[1000000];
        Weight(const QString &str) : str(str){}
    };

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
//    void on_lineEdit_textEdited(const QString &arg1);

////    void on_pushButton_clicked();

////    void on_pushButton_2_clicked();

////    void on_lineEdit_2_textEdited(const QString &arg1);

////    void on_pushButton_3_clicked();

////    void on_listWidget_2_currentRowChanged(int currentRow);

////    void on_pushButton_4_clicked();

////    void on_pushButton_5_clicked();

    void on_lineEdit_2_textEdited(const QString &arg1);

    void on_lineEdit_textEdited(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();


    void on_listWidget_2_currentRowChanged(int currentRow);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Widget *ui;

    Stack<QString> stack;
    List<QString> list;

    int currentIndex = -1;
};
#endif // WIDGET_H
