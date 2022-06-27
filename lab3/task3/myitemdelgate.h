#ifndef MYITEMDELGATE_H
#define MYITEMDELGATE_H

#include <QStyledItemDelegate>

class MyItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
    QRegularExpression exp;
public:
    MyItemDelegate(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const override;

    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                              const QModelIndex &index) const override;

    void setRegExp(QRegularExpression &&regExp);
};

#endif // MYITEMDELGATE_H
