#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <stack>

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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;

    static int opPriority(char c);

    static bool isVar(char c);

    static bool isOp(char c);

public:
    static std::string convertToPostfixForm(const std::string &str);

    static double calculate(const std::string &str, double a, double b,
                            double c, double d, double e);

    static bool expressionAreCorrect(const std::string &str);
};
#endif // WIDGET_H
