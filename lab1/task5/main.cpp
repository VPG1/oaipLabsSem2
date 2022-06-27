#include <iostream>
#include <iomanip>

class Expression{
public:
    static int numberOfEvalutes;
    virtual ~Expression(){}
    virtual double evalute() const = 0;

};
int Expression::numberOfEvalutes = 0;


class Number : public Expression{
public:
    Number(double value) : m_value(value){}

    double evalute() const override{
        ++numberOfEvalutes;
        return m_value;
    }

private:
    double m_value;
};


class BinaryOperation : public Expression{
public:
    BinaryOperation(Expression const *left, char op, Expression const *right)
        : m_left(left), m_op(op), m_right(right){}

    ~BinaryOperation(){
        delete m_left;
        delete m_right;
    }

    double evalute() const override{
        ++numberOfEvalutes;
        switch(m_op){
        case '+':
            return m_left->evalute() + m_right->evalute();
        case '-':
            return m_left->evalute() - m_right->evalute();
        case '*':
            return m_left->evalute() * m_right->evalute();
        case '/':
            return m_left->evalute() / m_right->evalute();
        }
    }
private:
    Expression const *m_left;
    char m_op;
    Expression const *m_right;
};


//bool check_equals(Expression const *left, Expression const *right){
//    int previousNumberOfEvalute = Expression::numberOfEvalutes;

//    bool leftIsNumber;
//    bool rightIsNumber;

//    left->evalute();
//    int deltaLeft = Expression::numberOfEvalutes - previousNumberOfEvalute;
//    if(deltaLeft == 1){
//        leftIsNumber = true;
//    }
//    else{
//        leftIsNumber = false;
//    }
//    previousNumberOfEvalute = Expression::numberOfEvalutes;


//    right->evalute();
//    int deltaRight = Expression::numberOfEvalutes - previousNumberOfEvalute;
//    if(deltaRight == 1){
//        rightIsNumber = true;
//    }
//    else{
//        rightIsNumber = false;
//    }

//    return (leftIsNumber == rightIsNumber);
//}


bool check_equals(Expression const *left, Expression const *right){
    return *reinterpret_cast<const int*>(left) == *reinterpret_cast<const int*>(right);
}

int main(){
    Expression *pN1 = new Number(3);
    Expression *pN2 = new Number(4);
    Expression *pN3 = new Number(5);
    Expression *pBO1 = new BinaryOperation(new Number(3), '+', pN1);
    Expression *pBO2 = new BinaryOperation(pN2, '*', pN3);
    Expression *pBO3 = new BinaryOperation(new Number(4), '/', new Number(5));

    std::cout << std::boolalpha << check_equals(pN1, pBO1) << std::endl; // false
    std::cout << check_equals(pN2, pN3) << std::endl; // true
    std::cout << check_equals(pBO3, pBO2) << std::endl; // true
    std::cout << check_equals(pN3, pBO2) << std::endl; // false
    std::cout << check_equals(pN1, pN2) << std::endl; // true
    std::cout << check_equals(pN2, pBO3) << std::endl; // false

    delete pBO1;
    delete pBO2;
    delete pBO3;

    return 0;
}
