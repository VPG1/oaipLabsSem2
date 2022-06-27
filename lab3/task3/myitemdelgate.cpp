#include "myitemdelgate.h"
#include <QSpinBox>
#include <QLineEdit>
#include <QRegularExpressionValidator>

MyItemDelegate::MyItemDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{
}

QWidget *MyItemDelegate::createEditor(QWidget *parent,
                                       const QStyleOptionViewItem &/* option */,
                                       const QModelIndex &/* index */) const
{
    QLineEdit *editor = new QLineEdit(parent);
    editor->setFrame(false);
//    editor->setValidator(new QRegularExpressionValidator
//                         (QRegularExpression("[a-e()/*+-]+")));
    editor->setValidator(new QRegularExpressionValidator(exp));
    return editor;

//    QSpinBox *editor = new QSpinBox(parent);
//    editor->setFrame(false);
//    editor->setMinimum(0);
//    editor->setMaximum(100);

//    return editor;
}

void MyItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString str = index.model()->data(index, Qt::EditRole).toString();

    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    lineEdit->setText(str);
}

void MyItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
//    lineEdit->interpretText();
    QString text = lineEdit->text();

    model->setData(index, text, Qt::EditRole);
}

void MyItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}

void MyItemDelegate::setRegExp(QRegularExpression &&regExp)
{
    exp = std::move(regExp);
}

