#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QListView>
#include <QLabel>
#include <QComboBox>
#include <QItemSelectionModel>
#include "carlistmodel.h"
#include "mysortfilterproxymodel.h"
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);

private:
    QString m_path;

    QListView *pView;

    QPushButton *pPushButtonAdd;
    QPushButton *pPushButtonDelete;
    QPushButton *pPushButtonSort;


    QLabel *pLabelInformation;

    QSpinBox *pSpinBoxMinCost;
    QSpinBox *pSpinBoxMaxCost;

    QSpinBox *pSpinBoxMinGasolineConsupmtion;
    QSpinBox *pSpinBoxMaxGasolineConsupmtion;

    QSpinBox *pSpinBoxMinReliability;
    QSpinBox *pSpinBoxMaxReliability;

    QSpinBox *pSpinBoxMinComfort;
    QSpinBox *pSpinBoxMaxComfort;


    QComboBox *pComboBoxSortVariant;

    CarListModel *pModel;
    MySortFilterProxyModel *pProxyModel;

public slots:
    void showSelectedItem(const QItemSelection &selected,
         const QItemSelection &deselected);

    void updateView(int index);

    void updateCostFilter();
    void updateGasolineConsupmtionFilter();
    void updateReliabilityFilter();
    void updateComfortFilter();

    void addCar();
    void deleteCar();
    void sortCars();
    void openCarsFile();
    void updateCarsView();

};
#endif // WIDGET_H

