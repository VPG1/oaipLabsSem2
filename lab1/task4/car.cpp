#include "car.h"
#include <sstream>

Car::Car()
{

}

Car::Car(const std::string &country, const std::string &model, const std::string &engineType,
         int price, int gasolineConsumption, int reliability, int comfort)
    : m_country(country), m_model(model), m_engineType(engineType),
      m_cost(price), m_gasolineConsumption(gasolineConsumption),
      m_reliability(reliability), m_comfort(comfort)
{

}

QString Car::getQStringForView() const
{
    return "model: " + QString::fromStdString(m_model) + "\tcoast: " + QString::number(m_cost);
}

QString Car::toQString() const
{
    return QString::fromStdString(m_country + " " + m_model + " " + m_engineType)
            + " " + QString::number(m_cost) + " " + QString::number(m_gasolineConsumption)
            + " " + QString::number(m_reliability) + " " + QString::number(m_comfort);
}

Car Car::fromQString(const QString &str)
{
//    assert(isCorrectCarString(str));
    std::stringstream strStream;
    int nClassFields = 7;
    for(int i = 0; i < nClassFields; ++i){
        strStream << str.toStdString() << " ";
    }
    Car car;
    strStream >> car;
    return car;
}

bool Car::isCorrectCarString(const QString &str)
{
    std::string stdStr = str.toStdString();
    std::stringstream strStream;
    strStream << stdStr;
    for(int i = 0; i < 8; ++i){
        std::string tmpStr;
        strStream >> tmpStr;

        if(i == 3){
            bool ok;
            int value = QString::fromStdString(tmpStr).toInt(&ok);
            if(!ok || value < 0 || value > maxCost){
                return false;
            }
        }
        else if(i == 4){
            bool ok;
            int value = QString::fromStdString(tmpStr).toInt(&ok);
            if(!ok || value < 0 || value > maxGasolineConsumption){
                return false;
            }
        }
        else if(i == 5){
            bool ok;
            int value = QString::fromStdString(tmpStr).toInt(&ok);
            if(!ok || value < 0 || value > maxReliability){
                return false;
            }
        }
        else if(i == 6){
            bool ok;
            int value = QString::fromStdString(tmpStr).toInt(&ok);
            if(!ok || value <= 0 || value > maxComfort){
                return false;
            }
        }
        else if(i == 7){
            if(tmpStr != ""){
                return false;
            }
        }
        else{
            if(tmpStr == ""){
                return false;
            }
        }

    }
    return true;
}

bool Car::isCorrectCar()
{
    if(m_country == ""){
        return false;
    }
    if(m_model == ""){
        return false;
    }
    if(m_engineType == ""){
        return false;
    }
    if(m_cost < 0 || m_cost > maxCost){
        return false;
    }
    if(m_gasolineConsumption < 0 || m_cost > maxGasolineConsumption){
        return false;
    }
    if(m_reliability < 0 || m_cost > maxReliability){
        return false;
    }
    if(m_comfort <= 0 || m_comfort > maxComfort){
        return false;
    }

    return false;
}

const std::string &Car::country() const
{
    return m_country;
}

const std::string &Car::model() const
{
    return m_model;
}

const std::string &Car::engineType() const
{
    return m_engineType;
}

int Car::cost() const
{
    return m_cost;
}

int Car::gasolineConsumption() const
{
    return m_gasolineConsumption;
}

int Car::reliability() const
{
    return m_reliability;
}

int Car::comfort() const
{
    return m_comfort;
}

int Car::getParameter(ParameterType parametr)
{
    switch(parametr){
    case COST:
        return m_cost;
    case GASOLINE_CONSUMPTION:
        return m_gasolineConsumption;
    case RELIABILITY:
        return m_reliability;
    case COMFORT:
        return m_comfort;
    }
}


std::istream &operator>>(std::istream &in, Car &car){
    in >> car.m_country;
    in >> car.m_model;
    in >> car.m_engineType;
    in >> car.m_cost;
    in >> car.m_gasolineConsumption;
    in >> car.m_reliability;
    in >> car.m_comfort;
    return in;
}

std::ostream &operator<<(std::ostream &out, const Car &car){
    out << car.m_country;
    out << " ";
    out << car.m_model;
    out << " ";
    out << car.m_engineType;
    out << " ";
    out << car.m_cost;
    out << " ";
    out << car.m_gasolineConsumption;
    out << " ";
    out << car.m_reliability;
    out << " ";
    out << car.m_comfort;
    return out;
}
