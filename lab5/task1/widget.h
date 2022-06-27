#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "my_queue.h"
#include <QInputDialog>
#include <QMessageBox>
#include <cstdlib>
#include <ctime>
#include <list>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Widget *ui;

    Queue<int> queue;
    std::list<int> randomNumbersList;

    int getRandomNumber(int min, int max);
};
#endif // WIDGET_H
