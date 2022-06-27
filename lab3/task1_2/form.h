#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QDialog>
#include "listonarray.h"
#include "information.h"

namespace Ui {
class Form;
}

class Form : public QDialog
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    Form(ListOnArray<Information> &&statementList, QWidget *parent = nullptr);
    ~Form();

    static void showTable(ListOnArray<Information> &&statementList);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Form *ui;
};

#endif // FORM_H
