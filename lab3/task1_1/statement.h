#ifndef STATEMENT_H
#define STATEMENT_H
#include <string>
#include <iostream>
#include <QString>
#include <sstream>

class Statement
{
    std::string m_lastName;
    std::string m_name;
    std::string m_patronymic;
    std::string m_address;
    double m_grade;

public:
    Statement();
    Statement(const std::string lastName, const std::string &name,
              const std::string &patronymic, const std::string &address,
              double grade);

    Statement(const std::string &str);

    static bool statementStringIsCorrect(const std::string &statementString){
        bool ok;

        int numberOfFields = 5;
        std::stringstream ss(statementString);
        for(int i = 0; i < numberOfFields; ++ i){
            std::string tmpStdString;
            ss >> tmpStdString;
            if(tmpStdString.empty() && i == 0){
                return true;
            }
            if(tmpStdString.empty()){
                return false;
            }

            if(i == 4){
                double d = QString::fromStdString(tmpStdString).toDouble(&ok);
                if(d < 0 || d > 10)
                    ok = false;
            }
        }
        std::string tmp;
        ss >> tmp;
        if(!tmp.empty())
            return false;
        return ok;
    }

    friend std::istream &operator>>(std::istream &in, Statement &statement);
    friend std::ostream &operator<<(std::ostream &out, const Statement &statement);
    const std::string &lastName() const;

    const std::string &name() const;
    const std::string &patronymic() const;
    const std::string &address() const;
    double grade() const;
};


#endif // STATEMENT_H
