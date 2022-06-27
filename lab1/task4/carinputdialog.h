#ifndef CARINPUTDIALOG_H
#define CARINPUTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include "car.h"

class CarInputDialog : public QDialog
{
    Q_OBJECT

public:
    CarInputDialog(QWidget *parent = nullptr);

    static Car getCarInput();

private:
    QLineEdit *pLineEditCountry;
    bool bCountryCorrect;

    QLineEdit *pLineEditModel;
    bool bModelCorrect;

    QLineEdit *pLineEditEngineType;
    bool bEditEngineType;

    QLineEdit *pLineEditCost;
    bool bCostCorrect;

    QLineEdit *pLineEditGasolineConsumption;
    bool bGasolineConsumptionCorrect;

    QLineEdit *pLineEditReliability;
    bool bReliabilityCorrect;

    QLineEdit *pLineEditComfort;
    bool bComfortCorrect;

    QPushButton *pPushButtonOk;

    static void setLineEditPinkBackground(QLineEdit *pLineEdit);
    static void unsetLineEditPinkBackground(QLineEdit *pLineEdit);

public slots:
    void inputCountryIsCorrect(const QString &text);
    void inputModelIsCorrect(const QString &text);
    void inputEngineTypeIsCorrect(const QString &text);
    void inputCostIsCorrect(const QString &text);
    void inputGasolineConsumptionIsCorrect(const QString &text);
    void inputReliabilityIsCorrect(const QString &text);
    void inputComfortIsCorrect(const QString &text);

    void okPressed();

};

#endif // CARINPUTDIALOG_H
