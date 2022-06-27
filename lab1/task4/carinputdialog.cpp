#include "carinputdialog.h"
#include <QLabel>
#include <QGridLayout>
#include <QPalette>


CarInputDialog::CarInputDialog(QWidget *parent) : QDialog(parent),
    bCountryCorrect(false), bModelCorrect(false),
    bEditEngineType(false), bCostCorrect(false),
    bGasolineConsumptionCorrect(false),
    bReliabilityCorrect(false), bComfortCorrect(false)
{
    QLabel *pLabelInformation = new QLabel("Enter informaiton about car");

    QLabel *pLabelCountry = new QLabel("country:");
    pLineEditCountry = new QLineEdit;

    QLabel *pLabelModel = new QLabel("model:");
    pLineEditModel = new QLineEdit;

    QLabel *pLabelEngineType = new QLabel("engine type:");
    pLineEditEngineType = new QLineEdit;

    QLabel *pLabelCost = new QLabel(QString("cost(0 - %1):").arg(Car::maxCost));
    pLineEditCost= new QLineEdit;

    QLabel *pLabelGasolineConsumption = new QLabel(QString("gasoline consumption per 100 km(0 - %1):").arg(Car::maxGasolineConsumption));
    pLineEditGasolineConsumption = new QLineEdit;

    QLabel *pLabelReliability = new QLabel(QString("reliability(0 - %1)").arg(Car::maxReliability));
    pLineEditReliability = new QLineEdit;

    QLabel *pLabelComfort = new QLabel(QString("comfort(1 - %1):").arg(Car::maxComfort));
    pLineEditComfort = new QLineEdit;

    pPushButtonOk = new QPushButton("ok");
//    pPushButtonOk->setEnabled(false);


    // Layout setup
    QGridLayout *pMainGridLayout = new QGridLayout;

    pMainGridLayout->addWidget(pLabelInformation, 0, 0, 1, 2, Qt::AlignCenter);

    pMainGridLayout->addWidget(pLabelCountry, 1, 0, Qt::AlignRight);
    pMainGridLayout->addWidget(pLineEditCountry, 1, 1);

    pMainGridLayout->addWidget(pLabelModel, 2, 0, Qt::AlignRight);
    pMainGridLayout->addWidget(pLineEditModel, 2, 1);

    pMainGridLayout->addWidget(pLabelEngineType, 3, 0, Qt::AlignRight);
    pMainGridLayout->addWidget(pLineEditEngineType, 3, 1);

    pMainGridLayout->addWidget(pLabelCost, 4, 0, Qt::AlignRight);
    pMainGridLayout->addWidget(pLineEditCost, 4, 1);

    pMainGridLayout->addWidget(pLabelGasolineConsumption, 5, 0, Qt::AlignRight);
    pMainGridLayout->addWidget(pLineEditGasolineConsumption, 5, 1);

    pMainGridLayout->addWidget(pLabelReliability, 6, 0, Qt::AlignRight);
    pMainGridLayout->addWidget(pLineEditReliability, 6, 1);

    pMainGridLayout->addWidget(pLabelComfort, 7, 0, Qt::AlignRight);
    pMainGridLayout->addWidget(pLineEditComfort, 7, 1);

    pMainGridLayout->addWidget(pPushButtonOk, 8, 1, Qt::AlignRight);

    setLayout(pMainGridLayout);

    qDebug() << connect(pPushButtonOk, SIGNAL(clicked()), SLOT(okPressed()));
}

Car CarInputDialog::getCarInput()
{
    CarInputDialog dialog;
    dialog.exec();
    return Car::fromQString(dialog.pLineEditCountry->text() + " " + dialog.pLineEditModel->text() + " "
            + dialog.pLineEditEngineType->text() + " " + dialog.pLineEditCost->text() + " "
            + dialog.pLineEditGasolineConsumption->text() + " " + dialog.pLineEditReliability->text() + " "
            + dialog.pLineEditComfort->text());
}

void CarInputDialog::setLineEditPinkBackground(QLineEdit *pLineEdit)
{
    pLineEdit->setStyleSheet("QLineEdit { background-color: pink }");
}

void CarInputDialog::unsetLineEditPinkBackground(QLineEdit *pLineEdit)
{
    pLineEdit->setStyleSheet("QLineEdit { background-color: white }");

}



void CarInputDialog::inputCountryIsCorrect(const QString &text)
{
    assert(text.size() <= 32767);

    if(text.isEmpty() || text.contains(' '))
    {
        setLineEditPinkBackground(pLineEditCountry);

        bCountryCorrect = false;
    }
    else
    {
        unsetLineEditPinkBackground(pLineEditCountry);
        bCountryCorrect = true;
    }
}

void CarInputDialog::inputModelIsCorrect(const QString &text)
{
    assert(text.size() <= 32767);

    if(text.isEmpty() || text.contains(' '))
    {
        setLineEditPinkBackground(pLineEditModel);

        bModelCorrect = false;
    }
    else
    {
        unsetLineEditPinkBackground(pLineEditModel);
        bModelCorrect = true;
    }
}

void CarInputDialog::inputEngineTypeIsCorrect(const QString &text)
{
    assert(text.size() <= 32767);

    if(text.isEmpty() || text.contains(' '))
    {
        setLineEditPinkBackground(pLineEditEngineType);

        bEditEngineType = false;
    }
    else
    {
        unsetLineEditPinkBackground(pLineEditEngineType);
        bEditEngineType = true;
    }
}

void CarInputDialog::inputCostIsCorrect(const QString &text)
{
    int value = text.toInt(&bCostCorrect);
    if(!bCostCorrect || value < 0 || value > Car::maxCost)
    {
        setLineEditPinkBackground(pLineEditCost);
        bCostCorrect = false;
    }
    else{
        unsetLineEditPinkBackground(pLineEditCost);
    }
}

void CarInputDialog::inputGasolineConsumptionIsCorrect(const QString &text)
{
    int value = text.toInt(&bGasolineConsumptionCorrect);
    if(!bGasolineConsumptionCorrect || value < 0 || value > Car::maxGasolineConsumption)
    {
        setLineEditPinkBackground(pLineEditGasolineConsumption);
        bGasolineConsumptionCorrect = false;
    }
    else{
        unsetLineEditPinkBackground(pLineEditGasolineConsumption);
    }
}

void CarInputDialog::inputReliabilityIsCorrect(const QString &text)
{
    int value = text.toInt(&bReliabilityCorrect);
    if(!bReliabilityCorrect || value < 0 || value > Car::maxReliability)
    {
        setLineEditPinkBackground(pLineEditReliability);
        bReliabilityCorrect = false;
    }
    else{
        unsetLineEditPinkBackground(pLineEditReliability);
    }
}

void CarInputDialog::inputComfortIsCorrect(const QString &text)
{
    int value = text.toInt(&bComfortCorrect);
    if(!bComfortCorrect || value <= 0 || value > Car::maxComfort)
    {
        setLineEditPinkBackground(pLineEditComfort);
        bComfortCorrect = false;
    }
    else{
        unsetLineEditPinkBackground(pLineEditComfort);
    }
}



void CarInputDialog::okPressed()
{
    inputCountryIsCorrect(pLineEditCountry->text());

    inputModelIsCorrect(pLineEditModel->text());

    inputEngineTypeIsCorrect(pLineEditEngineType->text());

    inputCostIsCorrect(pLineEditCost->text());

    inputGasolineConsumptionIsCorrect(pLineEditGasolineConsumption->text());

    inputReliabilityIsCorrect(pLineEditReliability->text());

    inputComfortIsCorrect(pLineEditComfort->text());


    if(!bCountryCorrect || !bModelCorrect || !bEditEngineType
            || !bCostCorrect || !bGasolineConsumptionCorrect
            || !bReliabilityCorrect || !bComfortCorrect)
    {
        connect(pLineEditCountry, SIGNAL(textEdited(const QString &)),
                SLOT(inputCountryIsCorrect(const QString &)));


        connect(pLineEditModel, SIGNAL(textEdited(const QString &)),
                SLOT(inputModelIsCorrect(const QString &)));


        connect(pLineEditEngineType, SIGNAL(textEdited(const QString &)),
                SLOT(inputEngineTypeIsCorrect(const QString &)));


        connect(pLineEditCost, SIGNAL(textEdited(const QString &)),
                SLOT(inputCostIsCorrect(const QString &)));


        connect(pLineEditGasolineConsumption, SIGNAL(textEdited(const QString &)),
                SLOT(inputGasolineConsumptionIsCorrect(const QString &)));


        connect(pLineEditReliability, SIGNAL(textEdited(const QString &)),
                SLOT(inputReliabilityIsCorrect(const QString &)));


        connect(pLineEditComfort, SIGNAL(textEdited(const QString &)),
                SLOT(inputComfortIsCorrect(const QString &)));
    }
    else
    {
        close();
    }
}






