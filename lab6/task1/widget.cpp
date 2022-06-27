#include "widget.h"
#include "ui_widget.h"
#include "avltree.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->spinBox->setRange(INT_MIN, INT_MAX);
}

Widget::~Widget()
{
    BinarySearchTreeMethod<int , std::string>::clear(root);
    delete ui;
}


void Widget::updateTreeWidget()
{
    delete ui->treeWidget->topLevelItem(0);

    qDebug() << root;
    if(root)
        updateTreeWidgetRoot(root, new QTreeWidgetItem(ui->treeWidget));

    ui->treeWidget->expandAll();
}


void Widget::updateTreeWidgetRoot(BinaryNode<int, std::string> *node, QTreeWidgetItem *treeWidgetNode)
{
    treeWidgetNode->setText(0, QString::number(node->key));
    treeWidgetNode->setText(1, QString::fromStdString(node->value));

    if(node->left){
        updateTreeWidgetRoot(node->left, new QTreeWidgetItem(treeWidgetNode));
    }
    else{
        (new QTreeWidgetItem(treeWidgetNode))->setText(0, "null");
    }
    if(node->right){
        updateTreeWidgetRoot(node->right, new QTreeWidgetItem(treeWidgetNode));
    }
    else{
        (new QTreeWidgetItem(treeWidgetNode))->setText(0, "null");
    }

}


void Widget::on_pushButton_clicked()
{
    auto v = ArrayDialog::getVector();
    root = BinarySearchTreeMethod<int, std::string>::arrayToBTS(v, 0, v.size() - 1);

    updateTreeWidget();
}

void Widget::on_pushButton_2_clicked()
{
    if(!root) return;
    root = BinarySearchTreeMethod<int, std::string>::balance(root);

    updateTreeWidget();
}

void Widget::on_pushButton_3_clicked()
{
    qDebug() << root;
    auto keyAndValue = BinaryNodeInput::getTreeElement();
    BinarySearchTreeMethod<int, std::string>::insert(keyAndValue.first, keyAndValue.second, root);
    qDebug() << root;
    updateTreeWidget();
}

void Widget::on_pushButton_4_clicked()
{

    std::optional<std::string> findingData = BinarySearchTreeMethod<int, std::string>::find(ui->spinBox->value(), root);
    if(findingData.has_value()){
        QMessageBox::information(this, "find", "Value: " + QString::fromStdString(findingData.value()));
    }

}

void Widget::on_pushButton_5_clicked()
{
    if(!root) return;

    bool ok;
    int key = QInputDialog::getInt(this, "erase", "Enter key:", 0, INT_MIN, INT_MAX, 1, &ok);
    if(!ok) return;

    BinarySearchTreeMethod<int, std::string>::erase(key, root);
    updateTreeWidget();
}

void Widget::on_pushButton_6_clicked()
{
    if(!root) return;
    TravesingDialog::showTraversing(BinarySearchTreeMethod<int, std::string>::traversePreorder(root),
                                    BinarySearchTreeMethod<int, std::string>::traversePostorder(root),
                                    BinarySearchTreeMethod<int, std::string>::traverseInorder(root));
}





void Widget::on_pushButton_7_clicked()
{
    if(!root || !root->left) return;
    BinarySearchTreeMethod<int, std::string>::clear(BinarySearchTreeMethod<int, std::string>::toRightestChild(root->left));
    updateTreeWidget();
}

