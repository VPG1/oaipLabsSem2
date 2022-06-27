#ifndef CAR_H
#define CAR_H
#include <string>
#include <iostream>
#include <QVariant>

class Car
{
public:
    static const int maxCost = 2000000000;
    static const int maxGasolineConsumption = 200;
    static const int maxReliability = 200;
    static const int maxComfort = 100;

    enum ParameterType{
        COST,
        GASOLINE_CONSUMPTION,
        RELIABILITY,
        COMFORT
    };


    Car();
    Car(const std::string &country, const std::string &model,
        const std::string &engineType, int price, int gasolineConsumption,
        int reliability, int comfort);

    QString getQStringForView() const;
    QString toQString() const;
    static Car fromQString(const QString &str);


    friend std::istream &operator>>(std::istream &in, Car &car);
    friend std::ostream &operator<<(std::ostream &in, const Car &car);

    static bool isCorrectCarString(const QString &str);

    bool isCorrectCar();

    const std::string &country() const;

    const std::string &model() const;

    const std::string &engineType() const;

    int cost() const;

    int gasolineConsumption() const;

    int reliability() const;

    int comfort() const;

    int getParameter(ParameterType parametr);

private:
    std::string m_country;
    std::string m_model;
    std::string m_engineType;
    int m_cost;
    int m_gasolineConsumption; // расход бензина на 100 км
    int m_reliability; // число лет безотказной работы
    int m_comfort; // от 1 до 100

};



#endif // CAR_H
