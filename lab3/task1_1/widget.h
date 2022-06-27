#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "ListAndFile.h"
#include <QResizeEvent>

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
    void slotFinishEditing();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

    void on_lineEdit_textEdited(const QString &arg1);

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    Ui::Widget *ui;
    ListAndFile statementFileList;

    int currentRow;
    int currentColumn;

    // если переменная true то при focusOut ничего неделаем
    // нужно для открытия фаила
    bool areOpeningFile = false;
};
#endif // WIDGET_H
