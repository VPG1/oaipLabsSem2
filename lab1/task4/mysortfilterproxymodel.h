#ifndef MYSORTFILTERPROXYMODEL_H
#define MYSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include "car.h"

class MySortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    MySortFilterProxyModel(QObject *parent = nullptr);

    void setMinParameter(int newMinParameter, Car::ParameterType parameter);

    void setMaxParameter(int newMaxParameter, Car::ParameterType parameter);

protected:

    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:
    bool parameterInRange(int parameterValue, Car::ParameterType parameter) const;

    int m_minCost;
    int m_maxCost;

    int m_minGasolineConsumption;
    int m_maxGasolineConsumption;

    int m_minReliability;
    int m_maxReliability;

    int m_minComfort;
    int m_maxComfort;
};

#endif // MYSORTFILTERPROXYMODEL_H
