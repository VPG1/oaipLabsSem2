#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <string>

class Expression
{
    std::string expr;
    double a;
    double b;
    double c;
    double d;
    double e;
public:
    Expression(const std::string &expr, double a, double b, double c, double d, double e);

    const std::string &getExpr() const;

    double getA() const;
    double getB() const;
    double getC() const;
    double getD() const;
    double getE() const;
};

#endif // EXPRESSION_H
