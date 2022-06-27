#ifndef WIDGET_H
#define WIDGET_H


#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


private slots:

    void on_plainTextEdit_textChanged();

    void on_pushButton_clicked();

private:

    void checkText(const std::string &str);

    struct Bracket{
        char bracket;
        int indexOfRow;
        int indexOfColumn;

        operator char(){
            return bracket;
        }
    };

    Ui::Widget *ui;
    int indexOfRow;
    int indexOfColumn;
};
#endif // WIDGET_H
