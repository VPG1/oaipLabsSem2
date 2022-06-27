#include "carlist.h"
#include <fstream>
#include <iostream>
#include <strstream>





CarList::CarList(const std::string &path) : m_path(path)
{
    m_size = numberOfCarInFile(m_path);
    m_carList = new Car[m_size];

    std::ifstream fin(m_path);
    assert(fin.is_open());

    for(int i = 0; i < m_size; ++i){
        fin >> m_carList[i];
    }

    fin.close();
}

int CarList::size() const
{
    return m_size;
}

const Car &CarList::at(int i) const
{
    return m_carList[i];
}

void CarList::insert(int pos, const Car &car)
{
    ++m_size;

    std::ofstream fout(m_path);
    assert(fout.is_open());

    Car *tmpCarVector = new Car[m_size];

    for(int i = 0, j = 0; i < m_size; ++i){
        if(i == pos){
            fout << car;

            tmpCarVector[i] = car;
            continue;
        }
        fout << m_carList[j];

        tmpCarVector[i] = m_carList[j];
        ++j;
    }


    fout.close();

    delete[] m_carList;
    m_carList = tmpCarVector;

}

void CarList::remove(int pos)
{
    --m_size;

    std::ofstream fout(m_path);
    assert(fout.is_open());

    Car *tmpCarVector = new Car[m_size];

//    for(int i = 0, j = 0; i < m_size; ++i){
//        if(i == pos){
//            continue;
//        }
//        tmpCarVector[j] = m_carVector[i];

//        fout << m_carVector[i];
//        ++j;
//    }
    for(int i = 0, j = 0; i < m_size + 1; ++i){
        if(i == pos)
            continue;
        tmpCarVector[j] = m_carList[i];

        fout << m_carList[i] << "\n";
        ++j;
    }

    fout.close();

    delete[] m_carList;
    m_carList = tmpCarVector;
}

void CarList::replace(int i, const Car &replacableCar)
{
    m_carList[i] = replacableCar;

    std::ofstream fout(m_path);
    assert(fout.is_open());

    for(int i = 0; i < m_size; ++i){
        fout << m_carList[i] << "\n";
    }

    fout.close();
}

void CarList::update()
{
    delete[] m_carList;

    m_size = numberOfCarInFile(m_path);
    m_carList = new Car[m_size];

    std::ifstream fin(m_path);
    assert(fin.is_open());

    for(int i = 0; i < m_size; ++i){
        fin >> m_carList[i];
    }

    fin.close();
}

bool CarList::areEpmty() const
{
    return m_size == 0 ? true : false;
}

bool CarList::fileIsCorrect(const QString &path)
{
    std::ifstream fin(path.toStdString());
    assert(fin.is_open());
    while(!fin.eof()){
        std::string line;

        for(int i = 0; i < 7; ++i){
            std::string tmpString;
            fin >> tmpString;

            if(tmpString == "" && i == 0){
                return true;
            }

            line += tmpString + " ";
        }

        if(!Car::isCorrectCarString(QString::fromStdString(line))){
            return false;
        }
    }
    return true;
}

void CarList::sort(Car::ParameterType parameter)
{
    qsortByModel(0, m_size - 1);

    int parameterArray[m_size];
    for(int i = 0; i < m_size; ++i){
        qDebug() << QString::fromStdString(m_carList[i].model());
        parameterArray[i] = m_carList[i].getParameter(parameter);
    }

    std::string prevCountryFirstLetter = m_carList[0].model();
    for(int i = 0, pos = 0; i < m_size; ++i){
        std::string curCountryFirstLetter = m_carList[i].model();



        if(prevCountryFirstLetter != curCountryFirstLetter){
            qsortByArray(parameterArray, pos, i - 1);
            pos = i;
        }
        if(i == m_size - 1){
            qsortByArray(parameterArray, pos, m_size - 1);
        }


        prevCountryFirstLetter = curCountryFirstLetter;
    }


    std::ofstream fout(m_path);
    assert(fout.is_open());

    for(int i = 0; i < m_size; ++i){
        fout << m_carList[i] << '\n';
    }

    fout.close();
}

std::string &CarList::path()
{
    return m_path;
}





int CarList::numberOfCarInFile(const std::string &path)
{
    int size = 0;
    int numberOfString = numberOfStringInFile(path);

    std::ifstream fin(path);
    assert(fin.is_open());

    while(!fin.eof()){
        Car tmpCar;
        fin >> tmpCar;

        ++size;
    }
    if(numberOfString % 7 == 1){
        --size;
    }

    fin.close();

    return size;
}

int CarList::numberOfStringInFile(const std::string &path)
{
    int numberOfString = 0;

    std::ifstream fin(path);
    assert(fin.is_open());

    while(!fin.eof()){
        std::string tmpStr;
        fin >> tmpStr;

        ++numberOfString;
    }

    fin.close();

    return numberOfString;
}

void CarList::qsortByModel(int first, int last)
{
    int f = first, l = last;
    std::string middle = m_carList[(f + l) / 2].model();

    do {
        while(m_carList[f].model() < middle) ++f;
        while(m_carList[l].model() > middle) --l;
        if(f <= l){
            Car temp = m_carList[f];
            m_carList[f] = m_carList[l];
            m_carList[l] = temp;
            ++f;
            --l;
        }
    }while(f < l);
    if(first < l) qsortByModel(first, l);
    if(f < last) qsortByModel(f, last);
}

void CarList::qsortByArray(int *arr, int first, int last)
{
    int f = first, l = last;
    int middle = arr[(f + l) / 2];
    do{
        while(arr[f] < middle) ++f;
        while(arr[l] > middle) --l;
        if(f <= l){
            int tempInt = arr[f];
            arr[f] = arr[l];
            arr[l] = tempInt;
            Car temp = m_carList[f];
            m_carList[f] = m_carList[l];
            m_carList[l] = temp;
            ++f;
            --l;
        }
    }while(f < l);
    if(first < l) qsortByArray(arr, first, l);
    if(f < last) qsortByArray(arr, f, last);
}
