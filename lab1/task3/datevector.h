#ifndef DATEVECTOR_H
#define DATEVECTOR_H
#include "date.h"

class DateVector
{
public:
    DateVector();
    DateVector(int i);
    void append(const Date &date);
    Date &operator[](int index);
    ~DateVector();
    int size() const;
    void clear();

private:
    Date *m_dateVector;
    int m_size;
};

#endif // DATEVECTOR_H
