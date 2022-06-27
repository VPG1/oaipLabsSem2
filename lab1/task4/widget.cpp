#include "widget.h"
#include "carinputdialog.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QStringList>
#include <QDir>
#include "carlist.h"
#include <QMessageBox>
#include <QSpinBox>
#include <QApplication>
#include <QSortFilterProxyModel>
#include <fstream>
#include <QFileDialog>


Widget::Widget(QWidget *parent)
    : QWidget(parent), m_path("cars.txt")
{

    std::ofstream fout(m_path.toStdString());
    assert(fout.is_open());
    fout.close();


    while(!CarList::fileIsCorrect("cars.txt")){
        auto button = QMessageBox::warning(this, "warning", "Incorrect file. Please edit it.",
                                           QMessageBox::Ok, QMessageBox::Close);
        if(button == QMessageBox::Close){
            qApp->quit();
        }

        // for mac os
        //    system(QString("open %1").arg(m_path).toLatin1());

        // for windows
        system(QString("notepad %1").arg(m_path).toLatin1());
    }


    pModel = new CarListModel("cars.txt", this);
    pProxyModel = new MySortFilterProxyModel(this);
    pProxyModel->setDynamicSortFilter(true);
    pProxyModel->setSourceModel(pModel);

    pLabelInformation = new QLabel;



    pSpinBoxMinCost = new QSpinBox;
    pSpinBoxMinCost->setRange(0, Car::maxCost);

    pSpinBoxMaxCost = new QSpinBox;
    pSpinBoxMaxCost->setRange(0, Car::maxCost);
    pSpinBoxMaxCost->setValue(Car::maxCost);


    pSpinBoxMinGasolineConsupmtion = new QSpinBox;
    pSpinBoxMinGasolineConsupmtion->setRange(0, Car::maxGasolineConsumption);

    pSpinBoxMaxGasolineConsupmtion = new QSpinBox;
    pSpinBoxMaxGasolineConsupmtion->setRange(0, Car::maxGasolineConsumption);
    pSpinBoxMaxGasolineConsupmtion->setValue(Car::maxGasolineConsumption);


    pSpinBoxMinReliability = new QSpinBox;
    pSpinBoxMinReliability->setRange(0, Car::maxReliability);

    pSpinBoxMaxReliability = new QSpinBox;
    pSpinBoxMaxReliability->setRange(0, Car::maxReliability);
    pSpinBoxMaxReliability->setValue(Car::maxReliability);


    pSpinBoxMinComfort = new QSpinBox;
    pSpinBoxMinComfort->setRange(1, Car::maxComfort);

    pSpinBoxMaxComfort = new QSpinBox;
    pSpinBoxMaxComfort->setRange(1, Car::maxComfort);
    pSpinBoxMaxComfort->setValue(Car::maxComfort);



    QLabel *pLabel = new QLabel("sort by");
    pComboBoxSortVariant = new QComboBox;
    pComboBoxSortVariant->addItems(QStringList()
                                   << "cost"
                                   << "gasoline consumption per 100 km"
                                   << "reliability(number of years of uptime)"
                                   << "comfort");



    pView = new QListView;
    pView->setModel(pProxyModel);
    pView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    pPushButtonAdd = new QPushButton("add");
    pPushButtonDelete = new QPushButton("delete");
    pPushButtonSort = new QPushButton("sort");
    QPushButton *pPushButtonOpen = new QPushButton("open file");
//    QPushButton *pPushButtonUpdate = new QPushButton("update");




    // layout setup


    QGridLayout *pLeftLayout = new QGridLayout;
    pLeftLayout->addWidget(pLabelInformation,
                           0, 0, 1, 4,
                           Qt::AlignHCenter| Qt::AlignTop);
    pLeftLayout->addWidget(pLabel, 1, 0, Qt::AlignRight);
    pLeftLayout->addWidget(pComboBoxSortVariant, 1, 1, 1, 3);

    pLeftLayout->addWidget(new QLabel(QString("cost(0 - %1) from:").arg(Car::maxCost)), 2, 0, Qt::AlignRight);
    pLeftLayout->addWidget(pSpinBoxMinCost, 2 , 1);
    pLeftLayout->addWidget(new QLabel("to:"), 2, 2, Qt::AlignRight);
    pLeftLayout->addWidget(pSpinBoxMaxCost, 2, 3);

    pLeftLayout->addWidget(new QLabel(QString("gasoline consumption(0 - %1) from:").arg(Car::maxGasolineConsumption)), 3, 0, Qt::AlignRight);
    pLeftLayout->addWidget(pSpinBoxMinGasolineConsupmtion, 3, 1);
    pLeftLayout->addWidget(new QLabel("to:"), 3, 2, Qt::AlignRight);
    pLeftLayout->addWidget(pSpinBoxMaxGasolineConsupmtion, 3, 3);

    pLeftLayout->addWidget(new QLabel(QString("reliability(0 - %1) from:").arg(Car::maxReliability)), 4, 0, Qt::AlignRight);
    pLeftLayout->addWidget(pSpinBoxMinReliability, 4, 1);
    pLeftLayout->addWidget(new QLabel("to:"), 4, 2, Qt::AlignRight);
    pLeftLayout->addWidget(pSpinBoxMaxReliability, 4, 3);

    pLeftLayout->addWidget(new QLabel(QString("comfort(1 - %1) from:").arg(Car::maxComfort)), 5, 0, Qt::AlignRight);
    pLeftLayout->addWidget(pSpinBoxMinComfort, 5, 1);
    pLeftLayout->addWidget(new QLabel("to:"), 5, 2, Qt::AlignRight);
    pLeftLayout->addWidget(pSpinBoxMaxComfort, 5, 3);



    QVBoxLayout *pRightLayout = new QVBoxLayout;
    pRightLayout->addWidget(pView);
    pRightLayout->addWidget(pPushButtonAdd);
    pRightLayout->addWidget(pPushButtonDelete);
    pRightLayout->addWidget(pPushButtonSort);
    pRightLayout->addWidget(pPushButtonOpen);
//    pRightLayout->addWidget(pPushButtonUpdate);


    QHBoxLayout *pMainLayout = new QHBoxLayout;
    pMainLayout->addLayout(pLeftLayout);
    pMainLayout->addLayout(pRightLayout);

    setLayout(pMainLayout);


    connect(pPushButtonAdd, SIGNAL(clicked()), SLOT(addCar()));
    connect(pPushButtonDelete, SIGNAL(clicked()), SLOT(deleteCar()));
    connect(pPushButtonSort, SIGNAL(clicked()), SLOT(sortCars()));
    connect(pPushButtonOpen, SIGNAL(clicked()), SLOT(openCarsFile()));
//    connect(pPushButtonUpdate, SIGNAL(clicked()), SLOT(updateCarsView()));

    connect(pComboBoxSortVariant, SIGNAL(activated(int)), SLOT(updateView(int)));


    connect(pSpinBoxMinCost, SIGNAL(valueChanged(int)), SLOT(updateCostFilter()));
    connect(pSpinBoxMaxCost, SIGNAL(valueChanged(int)), SLOT(updateCostFilter()));

    connect(pSpinBoxMinGasolineConsupmtion,
            SIGNAL(valueChanged(int)), SLOT(updateGasolineConsupmtionFilter()));
    connect(pSpinBoxMaxGasolineConsupmtion,
            SIGNAL(valueChanged(int)), SLOT(updateGasolineConsupmtionFilter()));

    connect(pSpinBoxMinReliability,
            SIGNAL(valueChanged(int)), SLOT(updateReliabilityFilter()));
    connect(pSpinBoxMaxReliability,
            SIGNAL(valueChanged(int)), SLOT(updateReliabilityFilter()));

    connect(pSpinBoxMinComfort, SIGNAL(valueChanged(int)),
            SLOT(updateComfortFilter()));
    connect(pSpinBoxMaxComfort, SIGNAL(valueChanged(int)),
            SLOT(updateComfortFilter()));


    connect(pView->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            SLOT(showSelectedItem(const QItemSelection &, const QItemSelection &)));

    pView->setEnabled(false);
    pPushButtonAdd->setEnabled(false);
    pPushButtonDelete->setEnabled(false);
    pPushButtonSort->setEnabled(false);
}


void Widget::showSelectedItem(const QItemSelection &selected,
     const QItemSelection &deselected)
 {
    QModelIndexList items = selected.indexes();
    QModelIndex index;


    foreach(index , items){ // ?

        Car car = pModel->carList().at(index.row());

        pLabelInformation->setText(QString("country: %1\n"
                                   "model: %2\n"
                                   "engineType: %3\n"
                                   "cost: %4\n"
                                   "gasoline consumption: %5\n"
                                   "reliability: %6\n"
                                   "comfort: %7")
                                   .arg(QString::fromStdString(car.country()))
                                   .arg(QString::fromStdString(car.model()))
                                   .arg(QString::fromStdString(car.engineType()))
                                   .arg(car.cost())
                                   .arg(car.gasolineConsumption())
                                   .arg(car.reliability())
                                   .arg(car.comfort())
                                   );
    }

}

void Widget::updateView(int index)
{
    pModel->setParameter(static_cast<Car::ParameterType>(index));
    pView->reset();
}


void Widget::updateCostFilter()
{
    pProxyModel->setMinParameter(pSpinBoxMinCost->value(), Car::COST);
    pProxyModel->setMaxParameter(pSpinBoxMaxCost->value(), Car::COST);
}

void Widget::updateGasolineConsupmtionFilter()
{
    pProxyModel->setMinParameter(pSpinBoxMinGasolineConsupmtion->value(), Car::GASOLINE_CONSUMPTION);
    pProxyModel->setMaxParameter(pSpinBoxMaxGasolineConsupmtion->value(), Car::GASOLINE_CONSUMPTION);
}

void Widget::updateReliabilityFilter()
{
    pProxyModel->setMinParameter(pSpinBoxMinReliability->value(), Car::RELIABILITY);
    pProxyModel->setMaxParameter(pSpinBoxMaxReliability->value(), Car::RELIABILITY);
}

void Widget::updateComfortFilter()
{
    pProxyModel->setMinParameter(pSpinBoxMinComfort->value(), Car::COMFORT);
    pProxyModel->setMaxParameter(pSpinBoxMaxComfort->value(), Car::COMFORT);
}



void Widget::addCar()
{
    Car newCar = CarInputDialog::getCarInput();
    bool b =!Car::isCorrectCarString(newCar.toQString());

    if(b){
        return;
    }

    pModel->insertRows(0, 1);
    pModel->setData(pModel->index(0),
                    newCar.toQString(),
                    Qt::DisplayRole);

}

void Widget::deleteCar()
{

    if(!pView->currentIndex().isValid()){
        return;
    }

    pLabelInformation->setText("");
    pModel->removeRows(pView->currentIndex().row(), 1);

}

void Widget::sortCars()
{
    int itemIndex = pComboBoxSortVariant->currentIndex();
    if(itemIndex == -1){
        return;
    }

    switch(itemIndex){
    case 0:
        pModel->sortCarsList(Car::COST);
        pView->reset();

        break;
    case 1:
        pModel->sortCarsList(Car::GASOLINE_CONSUMPTION);
        pView->reset();

        break;
    case 2:
        pModel->sortCarsList(Car::RELIABILITY);
        pView->reset();

        break;
    case 3:
        pModel->sortCarsList(Car::COMFORT);
        pView->reset();

        break;
    default:
        return;
    }
}

void Widget::openCarsFile(){
//    setEnabled(false);

//    // for mac os
////    system(QString("open %1").arg(m_path).toLatin1());

//    // for windos

//    system(QString("notepad %1").arg(m_path).toLatin1());\

//    setEnabled(true);

//    updateCarsView();

    QString selectedPath = QFileDialog::getOpenFileName(this, "Chose .txt file",
                                               QDir::rootPath(), "Text files (*.txt)");
//    qDebug() << "what are";

//    system(("open " + m_currentPath).toLatin1().data());

    // проверкой на то что selectedPath не является пустой строкой мы учитываем нажате пользователем кнопки отмены
    if(selectedPath == ""){
        return;
    }

    if(CarList::fileIsCorrect(selectedPath)){
        // очищаем массив перед заполнением
        m_path = selectedPath;
        pModel->carList().path() = m_path.toStdString();
        pModel->updateModel();
        // меняем текущий путь на выбранный
        // заполняем таблицу
        pView->setEnabled(true);
        pPushButtonAdd->setEnabled(true);
        pPushButtonDelete->setEnabled(true);
        pPushButtonSort->setEnabled(true);
    }
    else{
        QMessageBox::warning(this, "warning", "this file is't suitable");
        m_path = "cars.txt";
        pModel->carList().path() = m_path.toStdString();
        pModel->updateModel();
        pView->setEnabled(false);
        pPushButtonAdd->setEnabled(false);
        pPushButtonDelete->setEnabled(false);
        pPushButtonSort->setEnabled(false);
    }
}

void Widget::updateCarsView()
{

//    if(!CarList::fileIsCorrect(m_path)){
//        QMessageBox::warning(this, "warning", "This source file is invalid.\n");

//        pView->setEnabled(false);
//        pPushButtonAdd->setEnabled(false);
//        pPushButtonDelete->setEnabled(false);
//        pPushButtonSort->setEnabled(false);

//        pLabelInformation->setText("");
//        return;
//    }
//    pModel->updateModel();
//    pView->reset();

//    pView->setEnabled(true);
//    pPushButtonAdd->setEnabled(true);
//    pPushButtonDelete->setEnabled(true);
//    pPushButtonSort->setEnabled(true);

}

