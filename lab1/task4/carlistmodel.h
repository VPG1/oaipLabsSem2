#ifndef CARLISTMODEL_H
#define CARLISTMODEL_H

#include <QAbstractListModel>
#include <QVariant>
#include "carlist.h"


class CarListModel : public QAbstractListModel
{
public:
    enum ParameterRoleType{
        COST_ROLE = Qt::UserRole + 1,
        GASOLINE_CONSUPTION_ROLE,
        RELIABILITY_ROLE,
        COMFORT_ROLE
    };

    CarListModel(const std::string &path,
                          QObject *parent = nullptr);
    QVariant data(const QModelIndex &index,
                  int nRole) const override;

    bool setData(const QModelIndex &index,
                 const QVariant &value,
                 int nRole) override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    bool insertRows(int nRow,
                    int nCount,
                    const QModelIndex &parent = QModelIndex()
            ) override;
    bool removeRows(int nRow,
                    int nCount,
                    const QModelIndex &parent = QModelIndex()
            ) override;

    void updateModel();

    void sortCarsList(Car::ParameterType parameter);


    CarList &carList();


    void setParameter(Car::ParameterType newParameter);

private:
    CarList m_carList;

    Car::ParameterType m_parameter;
};

#endif // CARLISTMODEL_H
