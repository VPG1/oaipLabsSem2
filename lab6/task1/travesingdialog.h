#ifndef TRAVESINGDIALOG_H
#define TRAVESINGDIALOG_H

#include <QDialog>
#include <vector>

namespace Ui {
class TravesingDialog;
}

class TravesingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TravesingDialog(QWidget *parent = nullptr);
    ~TravesingDialog();
    static void showTraversing(const std::vector<std::string> &preorder,
                          const std::vector<std::string> &postorder,
                          const std::vector<std::string> &inorder);

private slots:
    void on_pushButton_clicked();

private:
    Ui::TravesingDialog *ui;
};

#endif // TRAVESINGDIALOG_H
