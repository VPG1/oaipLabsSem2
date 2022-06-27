#include "date.h"
#include <cmath>

Date::Date(int day, MonthType mounth, int year)
    :m_day(day), m_month(mounth), m_year(year){}

Date::Date(const QString &date)
{
    assert(inputIsDateFormat(date));

    m_day = date[0].digitValue() * 10 + date[1].digitValue();
    m_month = static_cast<MonthType>(date[3].digitValue() * 10 + date[4].digitValue());
    m_year = date[6].digitValue() * 1000 + date[7].digitValue() * 100
            + date[8].digitValue() * 10 + date[9].digitValue();
}


Date Date::nextDate() const{
    Date nextDay;

    // используем приватный метод daysInMounth для определения количества дней в году
    if(m_day + 1 > daysInMonth(m_month, isLeap()) && m_month + 1 > 12){
        nextDay.m_year = m_year + 1;
        nextDay.m_month = JANUARY;
        nextDay.m_day = 1;
    }
    else if(m_day + 1 > daysInMonth(m_month, isLeap())){
        nextDay.m_year = m_year;
        nextDay.m_month = static_cast<MonthType>(m_month + 1);
        nextDay.m_day = 1;
    }
    else{
        nextDay.m_year = m_year;
        nextDay.m_month = m_month;
        nextDay.m_day = m_day + 1;
    }

    return nextDay;
}

Date Date::previousDate() const{
    Date previousDay;

    // используем приватный метод daysInMounth для определения количества дней в году
    if(m_day - 1 <= 0 && m_month - 1 <= 0){
        previousDay.m_year = m_year - 1;
        previousDay.m_month = DECEMBER;
        previousDay.m_day = 31;
    }
    else if(m_day - 1 <= 0){
        previousDay.m_year = m_year;
        previousDay.m_month = static_cast<MonthType>(m_month - 1);
        previousDay.m_day = daysInMonth(m_month, isLeap());
    }
    else{
        previousDay.m_year = m_year;
        previousDay.m_month = m_month;
        previousDay.m_day = m_day - 1;
    }

    return previousDay;
}

short Date::weekNumber() const{// номер недели расчитывается по стандарту ISO 8601
    DayOfTheWeekType firstDayOfTheWeekInYear = Date(1, JANUARY, m_year).dayOfTheWeek();


    int DayInYear = Date(1, JANUARY, m_year).duration(*this);

    if(firstDayOfTheWeekInYear > 3){
        return (DayInYear + (firstDayOfTheWeekInYear - 1)) / 7;
    }
    else{
        return (DayInYear + (firstDayOfTheWeekInYear - 1))/ 7 + 1;
    }
}



bool Date::isLeap() const{
    return isLeapYear(m_year);
}

int Date::daysTillYourBirthDay(const Date &birthDay) const{
    if(m_month < birthDay.m_month || (m_month == birthDay.m_month && m_day <= birthDay.m_day)){
        return duration(Date(birthDay.m_day, birthDay.m_month, m_year));
    }
    else{
        return duration(Date(birthDay.m_day, birthDay.m_month, m_year + 1));
    }
}



int Date::duration(const Date &date) const{
    // количество лет между датами в днях
    // может быть отрицательным, если поле this->year > date.year
    int deltaYears = 0;
    if(date.m_year >= m_year){
        for(int i = 0; i < date.m_year - m_year; ++i){
            if(isLeapYear(m_year + i + 1)){
                deltaYears += 366; // кол-во дней в високосном году
            }
            else{
                deltaYears += 365; // кол-во дней в невисокосном году
            }
        }
    }
    else{
        for(int i = 0; i < m_year - date.m_year; ++i){
            if(isLeapYear(date.m_year + i + 1)){
                deltaYears -= 366; // кол-во дней в високосном году
            }
            else{
                deltaYears -= 365; // кол-во дней в невисокосном году
            }
        }
    }

    // количество дней между датами в днях
    int deltaMounths = 0;
    // весокосность была учтена при вычислении deltaYears
    // поэтому считаем deltaMounth для невисокосного года
    if(date.m_month >= m_month){
        for(int i = 0; i < date.m_month - m_month; ++i){
            deltaMounths += daysInMonth(static_cast<MonthType>(m_month + i), false);
        }
    }
    else{
        for(int i = 0; i < m_month - date.m_month; ++i){
            deltaMounths -= daysInMonth(static_cast<MonthType>(date.m_month + i), false);
        }
    }

    // вычисляем разницу дат
    int deltaDays = date.m_day - m_day;


   return abs(deltaYears + deltaMounths + deltaDays);
}

QString Date::dateToString() const{
    QString dayString = QString::number(m_day / 10) + QString::number(m_day % 10);

    QString monthString = QString::number(m_month / 10) + QString::number(m_month % 10);

    QString yearString = QString::number(m_year / 1000) + QString::number((m_year / 100) % 10)
            + QString::number((m_year / 10) % 10) + QString::number(m_year % 10);

//    QString reverseYearString;
//    int tmpYear = m_year;
//    while(tmpYear != 0){
//        reverseYearString += QString::number(tmpYear % 10);
//        tmpYear /= 10;
//    }
//    QString yearString;
//    for(int i = 0, stringSize = reverseYearString.size(); i < stringSize; ++i){
//        yearString[i] = reverseYearString[stringSize - i - 1];
//    }


    return QString("%1.%2.%3").arg(dayString).arg(monthString).arg(yearString);
}

/*static*/ bool Date::inputIsDateFormat(const QString &date)
{
    // формат даты, # - цифра
    QString dateFormat = "##.##.####";

    if(date.size() != dateFormat.size())
        return false;

    for(int i = 0; i < date.size(); ++i){
        switch (dateFormat[i].unicode()){
        case (QChar('#').unicode()):
            if(!date[i].isDigit())
                return false;
            break;
        default:
            if(dateFormat[i] != date[i])
                return false;
        }
    }


    int year = date[6].digitValue() * 1000 + date[7].digitValue() * 100
            + date[8].digitValue() * 10 + date[9].digitValue();

    int integerMonth = date[3].digitValue() * 10 + date[4].digitValue();
    if(integerMonth > 12 || integerMonth < 0)
        return false;

    int day = date[0].digitValue() * 10 + date[1].digitValue();
    if(day > daysInMonth(static_cast<MonthType>(integerMonth), isLeapYear(year)) || day < 0)
        return false;

    return true;
}

/*static*/ short Date::daysInMonth(MonthType mounth, bool isLeap){
    if(isLeap && mounth == FEBRUARY){
        return  29;
    }
    else if(mounth == FEBRUARY){
        return 28;
    }
    else if(mounth <= JULY){
        return 30 + (mounth) % 2;
    }
    else{
        return 30 + (mounth + 1) % 2;
    }
}


// приватный методы вычисления дня недели
Date::DayOfTheWeekType Date::dayOfTheWeek() const{
    // день недели вычисляем по формуле X = abs(floor(2.6*m-0.2)+d+y/4+y+c/4-2*c) % 7
    // где d, m и y - день в месяце, месяц и год дня если бы отсчёт начинался на 2 месяца раньше
    // а X от 0 до 6 (0 - 6 == воскресенье - суббота)
    short m;
    short y;
    if(m_month == JANUARY || m_month == FEBRUARY){
        y = (m_year - 1) % 100;
        m = static_cast<MonthType>(m_month + 10);
    }
    else{
        y = m_year % 100;
        m = static_cast<MonthType>(m_month - 2);
    }
    short c = y / 100;

    int X = static_cast<int>(abs(floor(2.6 * m - 0.2) + m_day + y / 4 + y + c / 4 - 2 * c)) % 7;

    if(X == 0){
        return SUNDAY;
    }
    else{
        return static_cast<DayOfTheWeekType>(X - 1);
    }
}

/*static*/ bool Date::isLeapYear(int year){
    if(year % 100 == 0 && year % 400 == 0){
        return true;
    }else if(year % 4 == 0){
        return true;
    }
    return false;
}

// перегрузка оператора извлечения
std::istream &operator>>(std::istream &in, Date &date){
    char point;

    in >> date.m_day;

    in >> point;

    int integerMonth;
    in >> integerMonth;
    date.m_month = static_cast<Date::MonthType>(integerMonth);

    in >> point;

    in >> date.m_year;

    return in;
}

std::ostream &operator<<(std::ostream &out, const Date &date){
    out << date.dateToString().toStdString();
    return out;
}



