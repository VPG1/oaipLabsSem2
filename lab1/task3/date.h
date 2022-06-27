#ifndef DATE_H
#define DATE_H
#include <QString>
#include <iostream>

class Date
{
public:
    enum MonthType{
        JANUARY = 1,
        FEBRUARY = 2,
        MARCH = 3,
        APRIL = 4,
        MAY = 5,
        JUNE = 6,
        JULY = 7,
        AUGUST = 8,
        SEPTEMBER = 9,
        OCTOBER = 10,
        NOVEMBER = 11,
        DECEMBER = 12
    };

    enum DayOfTheWeekType{
        MONDAY,
        TUESDAY,
        WEDNSDAY,
        THURSDAY,
        FRIDAY,
        SATURDAY,
        SUNDAY,
    };

    Date() = default;
    Date(int day, MonthType month, int year);
    Date(const QString &date);

    Date nextDate() const;
    Date previousDate() const;

    short weekNumber() const;
    bool isLeap() const;

    int daysTillYourBirthDay(const Date &birthDay) const;
    int duration(const Date &date) const;

    QString dateToString() const;

    // статическая функция для проверки возможности конвертирования строки в Date
    static bool inputIsDateFormat(const QString &date);

    // перегрузка оператора побитового сдвига
    friend std::istream &operator>>(std::istream &in, Date &date);
    friend std::ostream &operator<<(std::ostream &out, const Date &date);
private:
    int m_day;
    MonthType m_month;
    int m_year;

    // статический метод вычисления количества днй в месяце
    static short daysInMonth(MonthType month, bool isLeap);

    // метод вычисления дня недели
    Date::DayOfTheWeekType dayOfTheWeek() const;

    // статический метод поверки на весокосность
    static bool isLeapYear(int year);

};

#endif // DATE_H
