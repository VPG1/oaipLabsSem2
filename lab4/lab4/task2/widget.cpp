#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->spinBox->setRange(1, 10000);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    Timer t;

    vector<vector<char>> A(10000, vector<char>(200, 'q'));
    vector<vector<char>> B(10000, vector<char>(200, 'q'));

    A[0][0] = '0';

    int counterB, n = ui->spinBox->value(), counterA = 1, k = 1, counterBIN = 1, tmp;


    while (n >= counterBIN)
    {
        tmp = counterB = 0;

        for (int i = 0; i < counterA; i++)
        {
            if (!k_bit(A[i], k))
            {
                A[tmp] = A[i];
                tmp++;
            }
        }

        counterA = tmp;

        for (int i = 0; i < counterA; i++)
        {
            B[i] = powstr(A[i], k - 1);
            counterB++;
        }

        for (int i = 0; i < counterB; i++)
        {
            A[counterA] = B[i];
            counterA++;
        }

        counterBIN += counterB;
        k++;
    }

    std::string str;
    for (int i = 0; i < B[counterB - (counterBIN - n)].size(); i++)
    {
        if (B[counterB - (counterBIN - n)][i] == 'q')
        {
            break;
        }

        str += B[counterB - (counterBIN - n)][i];
    }

    double time =  t.elapsed();

    ui->label_3->setText("timer: " + QString::number(time));

    ui->label->setText("answer: " + QString::fromStdString(str));
}

