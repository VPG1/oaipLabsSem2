#ifndef INFORMATION_H
#define INFORMATION_H
#include <string>
#include <sstream>
#include <QString>

class Information
{
    std::string m_lastName;
    std::string m_name;
    std::string m_patronymic;
    std::string m_group;
    double m_grade;
    unsigned long long m_income;

public:
    Information();
    Information(const std::string &lastName, const std::string &name,
                const std::string &patronymic, const std::string &group,
                double grade, unsigned long long income);

    Information(const std::string &str);

    static bool informationStringIsCorrect(const std::string &statementString){
        bool ok1;
        bool ok2;
        int numberOfFields = 6;
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
                double d = QString::fromStdString(tmpStdString).toDouble(&ok1);
                if(d < 0 || d > 10)
                    ok1 = false;
            }

            if(i == 5){
                QString::fromStdString(tmpStdString).toULongLong(&ok2);
            }
        }

        std::string tmp;
        ss >> tmp;
        if(!tmp.empty())
            return false;

        return ok1 && ok2;
    }

    const std::string &lastName() const;
    const std::string &name() const;
    const std::string &patronymic() const;
    const std::string &group() const;
    double grade() const;
    unsigned long long income() const;

    friend std::ostream &operator<<(std::ostream &out, Information information);
};

#endif // INFORMATION_H
