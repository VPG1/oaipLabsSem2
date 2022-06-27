
#include "inputdialog.h"
#include "date.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>



InputDialog::InputDialog(const QString &msg, QWidget *parent, Qt::WindowFlags flags)
    : QDialog(parent, flags)
{
    pLineEdit = new QLineEdit;

    pOkPushButton = new QPushButton("Ok");
    pOkPushButton->setEnabled(false);

    // layout setup
    QHBoxLayout *pBottomLayout = new QHBoxLayout;
    pBottomLayout->addStretch(1);
    pBottomLayout->addWidget(pOkPushButton);

    QVBoxLayout *pMainVBoxLayout = new QVBoxLayout;
    pMainVBoxLayout->addWidget(
                new QLabel(msg));
    pMainVBoxLayout->addWidget(pLineEdit);
    pMainVBoxLayout->addLayout(pBottomLayout);

    setLayout(pMainVBoxLayout);

    connect(pLineEdit, SIGNAL(textEdited(const QString &)), SLOT(isCorrectInput()));
    connect(pOkPushButton, SIGNAL(clicked()), SLOT(close()));
}

/*static*/  QString InputDialog::createInputDialog(const QString &msg)
{
    InputDialog inputDialog(msg,
                            nullptr,
                            Qt::WindowSystemMenuHint);
    inputDialog.exec();
    return inputDialog.pLineEdit->text();
}


void InputDialog::isCorrectInput()
{
    if(Date::inputIsDateFormat(pLineEdit->text())){
        pOkPushButton->setEnabled(true);
    }
    else{
        pOkPushButton->setEnabled(false);
    }
}
