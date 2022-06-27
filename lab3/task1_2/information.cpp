#include "information.h"

const std::string &Information::lastName() const
{
    return m_lastName;
}

const std::string &Information::name() const
{
    return m_name;
}

const std::string &Information::patronymic() const
{
    return m_patronymic;
}

const std::string &Information::group() const
{
    return m_group;
}

double Information::grade() const
{
    return m_grade;
}

unsigned long long Information::income() const
{
    return m_income;
}

Information::Information()
{

}

Information::Information(const std::string &lastName, const std::string &name,
                         const std::string &patronymic, const std::string &group,
                         double grade, unsigned long long income) :
    m_lastName(lastName),
    m_name(name),
    m_patronymic(patronymic),
    m_group(group),
    m_grade(grade),
    m_income(income)
{}

Information::Information(const std::string &str)
{
    std::stringstream ss(str);
    ss >> m_lastName;
    ss >> m_name;
    ss >> m_patronymic;
    ss >> m_group;
    ss >> m_grade;
    ss >> m_income;
}

std::ostream &operator<<(std::ostream &out, Information information){
    return out << information.m_lastName << " " << information.m_name << " "
               << information.m_patronymic << " " << information.m_group << " "
               << information.m_grade << " " << information.m_income;

}

//bool informationStringIsCorrect(const std::string &statementString){
//    int numberOfFields = 6;
//    std::stringstream ss(statementString);
//    for(int i = 0; i < numberOfFields; ++ i){
//        std::string tmpStdString;
//        ss >> tmpStdString;
//        if(tmpStdString.empty() && i == 0){
//            return true;
//        }
//        if(tmpStdString.empty()){
//            return false;
//        }

//        if(i == 4){
//            bool ok;
//            double d = QString::fromStdString(tmpStdString).toDouble(&ok);
//            if(d >= 0 && d <= 10)
//                return ok;
//            return false;
//        }

//        if(i == 5){
//            bool ok;
//            QString::fromStdString(tmpStdString).toULongLong(&ok);
//            return ok;
//        }
//    }
//    return true;
//}
