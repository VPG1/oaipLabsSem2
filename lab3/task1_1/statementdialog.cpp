#include "statementdialog.h"
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QRegularExpressionValidator>
#include <QDoubleSpinBox>
#include "statement.h"

void StatementDialog::checkingInput()
{

    if(pLineEditLastName->text().isEmpty() || pLineEditName->text().isEmpty()
            || pLineEditPatronymic->text().isEmpty() || pLineEditGroup->text().isEmpty())
    {
        pPushButton->setEnabled(false);
    }
    else{
        pPushButton->setEnabled(true);
    }
}

void StatementDialog::okPushed()
{

    close();
}

StatementDialog::StatementDialog(QWidget *parent) : QDialog(parent)
{
    pLineEditLastName = new QLineEdit;
    connect(pLineEditLastName, SIGNAL(textEdited(const QString &)), SLOT(checkingInput()));
    pLineEditLastName->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-ZА-Яa-zа-я]+")));

    pLineEditName = new QLineEdit;
    connect(pLineEditName, SIGNAL(textEdited(const QString &)), SLOT(checkingInput()));
    pLineEditName->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-ZА-Яa-zа-я]+")));

    pLineEditPatronymic = new QLineEdit;
    connect(pLineEditPatronymic, SIGNAL(textEdited(const QString &)), SLOT(checkingInput()));
    pLineEditPatronymic->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-ZА-Яa-zа-я]+")));

    pLineEditGroup = new QLineEdit;
    connect(pLineEditGroup, SIGNAL(textEdited(const QString &)), SLOT(checkingInput()));
    pLineEditGroup->setValidator(new QRegularExpressionValidator(QRegularExpression("^[A-ZА-Яa-zа-я]+")));

    pDoubleSpinBox = new QDoubleSpinBox;
    pDoubleSpinBox->setRange(0, 10);

    pPushButton = new QPushButton("ok");
    connect(pPushButton, SIGNAL(clicked()), SLOT(okPushed()));
    pPushButton->setEnabled(false);

    // Layout setup
    QGridLayout *pLayout = new QGridLayout;
    pLayout->addWidget(new QLabel("last name:"), 0, 0);
    pLayout->addWidget(pLineEditLastName, 0, 1);

    pLayout->addWidget(new QLabel("name:"), 1, 0);
    pLayout->addWidget(pLineEditName, 1, 1);

    pLayout->addWidget(new QLabel("patronymic:"), 2, 0);
    pLayout->addWidget(pLineEditPatronymic, 2, 1);

    pLayout->addWidget(new QLabel("town:"), 3, 0);
    pLayout->addWidget(pLineEditGroup, 3, 1);

    pLayout->addWidget(new QLabel("grade:"), 4, 0);
    pLayout->addWidget(pDoubleSpinBox, 4, 1);

    pLayout->addWidget(pPushButton, 5, 1);

    setLayout(pLayout);
}

std::string StatementDialog::input(QWidget *parent)
{
    StatementDialog statementDialog;
    statementDialog.exec();

    return statementDialog.pLineEditLastName->text().toStdString() + " " + statementDialog.pLineEditName->text().toStdString() + " " +
                     statementDialog.pLineEditPatronymic->text().toStdString ()+ " " + statementDialog.pLineEditGroup->text().toStdString() + " " +
                     QString::number(statementDialog.pDoubleSpinBox->value()).toStdString() + '\n';
}
