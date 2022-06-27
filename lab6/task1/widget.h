#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "arraydialog.h"
#include "binary_search_tree.h"
#include "binarynodeinput.h"
#include <QTreeWidgetItem>
#include <queue>
#include <QInputDialog>
#include <QMessageBox>
#include "travesingdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();


    void on_pushButton_7_clicked();

private:
    Ui::Widget *ui;
    BinaryNode<int, std::string> *root = nullptr;


    void updateTreeWidget();
    void updateTreeWidgetRoot(BinaryNode<int ,std::string> *node, QTreeWidgetItem *treeWidgetNode);
};
#endif // WIDGET_H
