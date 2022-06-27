#ifndef ARRAYDIALOG_H
#define ARRAYDIALOG_H

#include <QDialog>
#include <vector>
#include <QApplication>

namespace Ui {
class ArrayDialog;
}

class ArrayDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ArrayDialog(QWidget *parent = nullptr);
    ~ArrayDialog();

    static std::vector<std::string>getVector();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::ArrayDialog *ui;
    std::vector<std::string> array;
};

#endif // ARRAYDIALOG_H
