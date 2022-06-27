#ifndef BINARYNODEINPUT_H
#define BINARYNODEINPUT_H

#include <QDialog>

namespace Ui {
class BinaryNodeInput;
}

class BinaryNodeInput : public QDialog
{
    Q_OBJECT

public:
    explicit BinaryNodeInput(QWidget *parent = nullptr);
    ~BinaryNodeInput();

    static std::pair<int, std::string> getTreeElement();

private slots:
    void on_pushButton_clicked();

private:
    Ui::BinaryNodeInput *ui;
};

#endif // BINARYNODEINPUT_H
