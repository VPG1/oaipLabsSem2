#include "mylineedit.h"



MyLineEdit::MyLineEdit(QWidget *parent) : QLineEdit(parent)
{
}

void MyLineEdit::focusOutEvent(QFocusEvent *e)
{

    if(text().isEmpty())
        setText("Empty");
    emit myEditingFinished();
    QLineEdit::focusOutEvent(e);
}
