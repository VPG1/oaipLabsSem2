#include "datevector.h"

DateVector::DateVector()
{
    m_dateVector = nullptr;
    m_size = 0;
}

DateVector::DateVector(int size){
    m_dateVector= new Date[size];
    m_size = size;
}

DateVector::~DateVector()
{
    delete[] m_dateVector;
}

int DateVector::size() const
{
    return m_size;
}

void DateVector::clear()
{
    delete[] m_dateVector;
    m_dateVector = nullptr;
    m_size = 0;
}

void DateVector::append(const Date &date)
{

    Date *tmpDateVector = new Date[m_size + 1];
    for(int i = 0; i < m_size; ++i){
        tmpDateVector[i] = m_dateVector[i];
    }
    tmpDateVector[m_size] = date;
    m_size++;

    delete [] m_dateVector;
    m_dateVector = tmpDateVector;
}

Date &DateVector::operator[](int index)
{
    return m_dateVector[index];
}
