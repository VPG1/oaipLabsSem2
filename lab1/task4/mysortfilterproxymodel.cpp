#include "mysortfilterproxymodel.h"
#include "carlistmodel.h"

MySortFilterProxyModel::MySortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent},
      m_minCost(0), m_maxCost(Car::maxCost),
      m_minGasolineConsumption(0), m_maxGasolineConsumption(Car::maxGasolineConsumption),
      m_minReliability(0), m_maxReliability(Car::maxReliability),
      m_minComfort(1), m_maxComfort(Car::maxComfort)
{

}




void MySortFilterProxyModel::setMinParameter(int newMinParameter, Car::ParameterType parameter)
{
    switch (parameter) {
    case Car::COST:
        m_minCost = newMinParameter;
        break;
    case Car::GASOLINE_CONSUMPTION:
        m_minGasolineConsumption = newMinParameter;
        break;
    case Car::RELIABILITY:
        m_minReliability = newMinParameter;
        break;
    case Car::COMFORT:
        m_minComfort = newMinParameter;
        break;
    }
    invalidateFilter();
}

void MySortFilterProxyModel::setMaxParameter(int newMaxParameter, Car::ParameterType parameter)
{
    switch (parameter) {
    case Car::COST:
        m_maxCost = newMaxParameter;
        break;
    case Car::GASOLINE_CONSUMPTION:
        m_maxGasolineConsumption = newMaxParameter;
        break;
    case Car::RELIABILITY:
        m_maxReliability = newMaxParameter;
        break;
    case Car::COMFORT:
        m_maxComfort = newMaxParameter;
        break;
    }
    invalidateFilter();
}

bool MySortFilterProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);

    return parameterInRange(sourceModel()->data(index, CarListModel::COST_ROLE).value<int>(),Car::COST)
            && parameterInRange(sourceModel()->data(index, CarListModel::GASOLINE_CONSUPTION_ROLE).value<int>(),Car::GASOLINE_CONSUMPTION)
            && parameterInRange(sourceModel()->data(index, CarListModel::RELIABILITY_ROLE).value<int>(),Car::RELIABILITY)
            && parameterInRange(sourceModel()->data(index, CarListModel::COMFORT_ROLE).value<int>(),Car::COMFORT);
}




bool MySortFilterProxyModel::parameterInRange(int paramterValue, Car::ParameterType parameter) const
{
    switch (parameter) {
    case Car::COST:
        return (paramterValue >= m_minCost
                && paramterValue <= m_maxCost);
    case Car::GASOLINE_CONSUMPTION:
        return (paramterValue >= m_minGasolineConsumption
                && paramterValue <= m_maxGasolineConsumption);
    case Car::RELIABILITY:
        return (paramterValue >= m_minReliability
                && paramterValue <= m_maxReliability);
    case Car::COMFORT:
        return (paramterValue >= m_minComfort
                && paramterValue <= m_maxComfort);
    }
}




