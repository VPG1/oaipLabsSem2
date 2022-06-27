#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QDialog>
#include "list.h"
#include "statement.h"

namespace Ui {
class Form;
}

class Form : public QDialog
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    Form(List<Statement> &&statementList, QWidget *parent = nullptr);
    ~Form();

    static void showTable(List<Statement> &&statementList);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Form *ui;
};

#endif // FORM_H
