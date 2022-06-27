#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H

#include <QLineEdit>

class MyLineEdit : public QLineEdit
{
    Q_OBJECT

    std::string emptyString = "Empty";
public:
    MyLineEdit(QWidget *parent = nullptr);
    void setEmptyString(const std::string &newEmptyString);

protected:
    void focusOutEvent(QFocusEvent *e) override;
signals:
    void myEditingFinished();
};

#endif // MYLINEEDIT_H
