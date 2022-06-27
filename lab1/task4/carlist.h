#ifndef CARLIST_H
#define CARLIST_H
#include "car.h"

class CarList
{
public:
    CarList() = delete;
    CarList(const CarList &) = delete;

    CarList(const std::string &path);

    int size() const;

    const Car &at(int i) const;

    void insert(int pos, const Car& car);
    void remove(int pos);
    void replace(int i, const Car &replacableCar);
    void update();

    bool areEpmty() const;

    static bool fileIsCorrect(const QString &path);

    void sort(Car::ParameterType parameter);

    std::string &path();

private:
    std::string m_path;
    Car *m_carList;
    int m_size;

    // статическая функция вычисляющая кол-во структур в фаиле
    static int numberOfCarInFile(const std::string &path);

    static int numberOfStringInFile(const std::string &path);

    void qsortByModel(int first, int last);

    void qsortByArray(int *arr, int first, int last);


};

#endif // CARLIST_H
