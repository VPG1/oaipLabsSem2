#include "mylineedit.h"



void MyLineEdit::setEmptyString(const std::string &newEmptyString)
{
    emptyString = newEmptyString;
}

MyLineEdit::MyLineEdit(QWidget *parent) : QLineEdit(parent)
{
}

void MyLineEdit::focusOutEvent(QFocusEvent *e)
{

    if(text().isEmpty())
        setText(QString::fromStdString(emptyString));
    emit myEditingFinished();
    QLineEdit::focusOutEvent(e);
}
