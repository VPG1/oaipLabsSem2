#include "carlistmodel.h"
#include "car.h"


CarListModel::CarListModel(const std::string &path,
                           QObject *parent)
    : QAbstractListModel(parent), m_carList(path)
{

}

QVariant CarListModel::data(const QModelIndex &index, int nRole) const /*override*/
{
    if(!index.isValid()){
        return QVariant();
    }

    if(index.row() < 0 || index.row() >= m_carList.size()){
        return QVariant();
    }

    switch(nRole){
    case COST_ROLE:
        return m_carList.at(index.row()).cost();
    case GASOLINE_CONSUPTION_ROLE:
        return m_carList.at(index.row()).gasolineConsumption();
    case RELIABILITY_ROLE:
        return m_carList.at(index.row()).reliability();
    case COMFORT_ROLE:
        return m_carList.at(index.row()).comfort();
    }

    QString strParameter;

    switch (m_parameter) {
    case Car::COST:
        strParameter = "\tcost: " + QString::number(m_carList.at(index.row()).cost());
        break;
    case Car::GASOLINE_CONSUMPTION:
        strParameter = "\tgasoline consumpion "
                       "per 100 km: " + QString::number(m_carList.at(index.row()).gasolineConsumption());
        break;
    case Car::RELIABILITY:
        strParameter = "\treliability: " + QString::number(m_carList.at(index.row()).reliability());
        break;
    case Car::COMFORT:
        strParameter = "\tcomfort: " + QString::number(m_carList.at(index.row()).comfort());
        break;
    }


    return (nRole == Qt::DisplayRole)
            ? "model: " + QString::fromStdString(m_carList.at(index.row()).model())
              + strParameter
            : QVariant();
}

bool CarListModel::setData(const QModelIndex &index, const QVariant &value, int nRole)
{
    if(index.isValid()){
        m_carList.replace(index.row(),
                          Car::fromQString(value.value<QString>()));
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

int CarListModel::rowCount(const QModelIndex &parent /*= QModelIndex*/) const /*override*/
{
    if(parent.isValid()){
        return 0;
    }

    return m_carList.size();
}


bool CarListModel::insertRows(int nRow, int nCount, const QModelIndex &parent)
{
    if(parent.isValid()){
        return false;
    }

    beginInsertRows(QModelIndex(), nRow, nRow + nCount - 1);
    for(int i = 0; i < nCount; ++i){
        m_carList.insert(nRow, Car());
    }
    endInsertRows();

    return true;
}

bool CarListModel::removeRows(int nRow, int nCount, const QModelIndex &parent)
{
    if(parent.isValid()){
        return false;
    }

    beginRemoveRows(QModelIndex(), nRow, nRow + nCount - 1);
    for(int i = 0; i < nCount; ++i){
        m_carList.remove(nRow);
    }
    endRemoveRows();

    return true;
}

void CarListModel::updateModel()
{
    beginResetModel();
    m_carList.update();
    endResetModel();
}

void CarListModel::sortCarsList(Car::ParameterType parameter)
{
    m_carList.sort(parameter);
}


CarList &CarListModel::carList()
{
    return m_carList;
}

void CarListModel::setParameter(Car::ParameterType newParameter)
{
    m_parameter = newParameter;
}




