#include "widget.h"
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
//    std::string infix = "a/b-((c+d)*e)";
//    std::string postfix = Widget::convertToPostfixForm(infix);
//    std::cout << postfix << '\n';
//    std::cout << Widget::calculate(postfix, 1.2, 0.7, 9.3, 6.5, 8.4) << '\n';
//    std::cout << Widget::expressionAreCorrect(infix);
//    return 0;
}
