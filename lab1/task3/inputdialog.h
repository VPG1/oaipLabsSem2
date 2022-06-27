#ifndef INPUTDIALOG2H_H
#define INPUTDIALOG2H_H

#include <QInputDialog>

class InputDialog : public QDialog
{
    Q_OBJECT
public:
    InputDialog(const QString &msg, QWidget *parent = nullptr, Qt::WindowFlags flags = Qt::WindowFlags());
    static QString createInputDialog(const QString &msg);

private:
    QLineEdit *pLineEdit;
    QPushButton *pOkPushButton;
public slots:
    void isCorrectInput();

};

#endif // INPUTDIALOG2H_H
