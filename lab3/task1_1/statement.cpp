#include "statement.h"
#include <iostream>
#include <sstream>
#include <QString>

const std::string &Statement::lastName() const
{
    return m_lastName;
}



const std::string &Statement::name() const
{
    return m_name;
}

const std::string &Statement::patronymic() const
{
    return m_patronymic;
}

const std::string &Statement::address() const
{
    return m_address;
}

double Statement::grade() const
{
    return m_grade;
}

Statement::Statement()
{
}

Statement::Statement(const std::string lastName, const std::string &name,
                     const std::string &patronymic, const std::string &address,
                     double grade)
    : m_lastName(lastName), m_name(name), m_patronymic(patronymic), m_address(address), m_grade(grade)
{
}

Statement::Statement(const std::string &str)
{
    std::stringstream ss(str);
    ss >> m_lastName;
    ss >> m_name;
    ss >> m_patronymic;
    ss >> m_address;
    ss >> m_grade;
}



std::istream &operator>>(std::istream &in, Statement &statement){
    return in >> statement.m_lastName >> statement.m_name >> statement.m_patronymic
              >> statement.m_address >> statement.m_grade;

}

std::ostream &operator<<(std::ostream &out, const Statement &statement){
    return out << statement.m_lastName << " " << statement.m_name << " "
               << statement.m_patronymic << " " << statement.m_address << " "
               << statement.m_grade;
}
