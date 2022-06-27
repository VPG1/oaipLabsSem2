#ifndef INFORMATIONDIALOG_H
#define INFORMATIONDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDoubleSpinBox>

class InformationDialog : public QDialog
{
    Q_OBJECT

    QPushButton *pPushButton;
    QLineEdit *pLineEditLastName;
    QLineEdit *pLineEditName;
    QLineEdit *pLineEditPatronymic;
    QLineEdit *pLineEditGroup;
    QDoubleSpinBox *pDoubleSpinBox;
    QLineEdit *pLineEditIncome;

private slots:
    void checkingInput();
    void okPushed();

public:
    InformationDialog(QWidget *parent = nullptr);

    static std::string input(QWidget *parent = nullptr);
};

#endif // INFORMATIONDIALOG_H
