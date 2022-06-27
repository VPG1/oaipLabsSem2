#include "expression.h"

const std::string &Expression::getExpr() const
{
    return expr;
}



double Expression::getA() const
{
    return a;
}

double Expression::getB() const
{
    return b;
}

double Expression::getC() const
{
    return c;
}

double Expression::getD() const
{
    return d;
}

double Expression::getE() const
{
    return e;
}

Expression::Expression(const std::string &expr, double a, double b, double c, double d, double e) : expr(expr),
    a(a),
    b(b),
    c(c),
    d(d),
    e(e)
{}
