#ifndef STATEMENTDIALOG_H
#define STATEMENTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include "statement.h"
#include <QDoubleSpinBox>

class StatementDialog : public QDialog
{
    Q_OBJECT

    QPushButton *pPushButton;
    QLineEdit *pLineEditLastName;
    QLineEdit *pLineEditName;
    QLineEdit *pLineEditPatronymic;
    QLineEdit *pLineEditGroup;
    QDoubleSpinBox *pDoubleSpinBox;

private slots:
    void checkingInput();
    void okPushed();

public:
    StatementDialog(QWidget *parent = nullptr);

    static std::string input(QWidget *parent = nullptr);
};

#endif // STATEMENTDIALOG_H
