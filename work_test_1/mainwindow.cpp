#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QIcon>
#include <QPushButton>
#include <QVector>
#include <QDebug>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMinimumSize(220, 340);
    setMaximumSize(220, 340);
    setWindowTitle(tr("Xs and Os"));

    ui->comboBox->addItem("Easy");
    ui->comboBox->addItem("Hard");

    ui->comboBox->setEnabled(false);

    diff=0;
    mode=0;
    colors[0]=0;
    colors[1]=0;
    colors[2]=0;
    newGame();


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    newGame();
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    //Game mode
    newGame();

    if(arg1==0)
    {
        ui->comboBox->setEnabled(false);
        mode=0;
    }
    else
    {
        ui->comboBox->setEnabled(true);
        mode=1;
    }

}


void MainWindow::clearMatrix()
{
    for(int i = 0;i<9;i++){
        matrix[i]=0;
    }
    move=0;
}

void MainWindow::on_comboBox_activated(int index)
{
    diff=index;
    newGame();
}

void MainWindow::on_pushButton_11_clicked()
{
    checkBut(0);
}

void MainWindow::on_pushButton_12_clicked()
{
    checkBut(1);
}

void MainWindow::on_pushButton_13_clicked()
{
    checkBut(2);
}

void MainWindow::on_pushButton_21_clicked()
{
    checkBut(3);
}

void MainWindow::on_pushButton_22_clicked()
{
    checkBut(4);
}

void MainWindow::on_pushButton_23_clicked()
{
    checkBut(5);
}

void MainWindow::on_pushButton_31_clicked()
{

    checkBut(6);
}

void MainWindow::on_pushButton_32_clicked()
{
    checkBut(7);
}

void MainWindow::on_pushButton_33_clicked()
{
    checkBut(8);
}




void MainWindow::clear_Butt()
{
    QPushButton * butt;
    for(int i = 0; i < 9; i++)
    {
        butt = getButton(i);
        butt->setIcon(QIcon(":/pics/E.png"));
        butt->setIconSize(QSize(60,60));
    }
}

int MainWindow::check()
{
    int i;
    for(i=0;i<3;i++)
    {
        if ((matrix[i*3] == matrix[i*3+1]) && (matrix[i*3+1] == matrix[i*3+2]))
        {
            colors[0]=i*3;
            colors[1]=i*3+1;
            colors[2]=i*3+2;

            return matrix[i*3];
        }
        if ((matrix[i] == matrix[i+3]) && (matrix[i+3] == matrix[i+6]))
        {
            colors[0]=i;
            colors[1]=i+3;
            colors[2]=i+6;
            return matrix[i];
        }
    }
    if ((matrix[2] == matrix[4] && matrix[4] == matrix[6]))
    {
        colors[0]=2;
        colors[1]=4;
        colors[2]=6;
        return matrix[4];
    }
    else
    {
        if((matrix[0] == matrix[4] && matrix[4] == matrix[8]))
        {
            colors[0]=0;
            colors[1]=4;
            colors[2]=8;
            return matrix[4];
        }
        else
        {
            return 0;
        }
    }
}

void MainWindow::setActive(bool a)
{
    QPushButton *butt;
    for(int i=0;i<9;i++)
    {
        butt = getButton(i);
        butt->blockSignals(!a);
    }
}

void MainWindow::checkWin()
{
    int r;
    if(move>3)
    {
        r=check();
        if(r==1)
        {
            ui->label_2->setText("X wins");
            setActive(false);
            colorizeWinner(1);

            move=8;
        }
        else
        {
            if(r==2)
            {
                ui->label_2->setText("O wins");
                setActive(false);

                colorizeWinner(2);

                move=8;

            }
            else
            {
                if(move==8)
                {
                    ui->label_2->setText("No wins");
                    setActive(false);
                }
            }
        }
    }
}

void MainWindow::checkBut(int b)
{
    QPushButton *butt;
    butt = getButton(b);

    if(matrix[b]==0)
    {
        if(move%2==0)
        {
            butt->setIcon(QIcon(":/pics/X.png"));
            butt->setIconSize(QSize(60,60));
            matrix[b]=1;

            checkWin();

            move++;

            if(mode==1 && move<9)
            {
                AI();
            }
        }
        else
        {
            butt->setIcon(QIcon(":/pics/O.png"));
            butt->setIconSize(QSize(60,60));
            matrix[b]=2;
            checkWin();
            move++;
        }
    }
}

void MainWindow::colorizeWinner(int xo)
{
    QPushButton *butt;
    for(int i=0; i<3;i++)
    {
        butt = getButton(colors[i]);
        if(xo==1)
        {
            butt->setIcon(QIcon(":/pics/X_g.png"));
            butt->setIconSize(QSize(60,60));
        }
        else
        {
            butt->setIcon(QIcon(":/pics/O_g.png"));
            butt->setIconSize(QSize(60,60));
        }
    }
}

void MainWindow::AI()
{
    int a;
    if(diff==0)
    {
        a=randAI();
    }
    else
    {
        a=winAI(2);
        if(a==9)
        {
            a=winAI(1);
            if(a==9)
            {
                a = randAI();
            }
        }
    }
    checkBut(a);

}

int MainWindow::randAI()
{
    int k =0;
    static int count;
    while(k==0)
    {
        count = Random::get(0,8);
        if(matrix[count]==0)
        {
            k=1;
        }
    }
    return count;
}

int MainWindow::winAI(int b)
{
    int i,k;
    int choise = 9;
    for(i=0;i<3;i++)
    {
        //Lines
        for(k=0;k<3;k++)
        {
            if(((matrix[i*3]==b)||((k==0)&&matrix[i*3]==0))
                    &&((matrix[i*3+1]==b)||((k==1)&&matrix[i*3+1]==0))
                    &&((matrix[i*3+2]==b)||((k==2)&&matrix[i*3+2]==0)))
            {
                choise = (i*3+k);
                break;
            }

            //Columns

            if(((matrix[i]==b)||((k==0)&&matrix[i]==0))
                    &&((matrix[i+3]==b)||((k==1)&&matrix[i+3]==0))
                    &&((matrix[i+6]==b)||((k==2)&&matrix[i+6]==0)))
            {
                choise = (i+3*k);
                break;
            }
        }
    }
    //Diagonals
    if(choise==9)
    {
        for(k=0;k<3;k++)
        {
            if(((matrix[0]==b)||((k==0)&&matrix[0]==0))
                    &&((matrix[4]==b)||((k==1)&&matrix[4]==0))
                    &&((matrix[8]==b)||((k==2)&&matrix[8]==0)))
            {
                choise = (4*k);
                break;
            }

            if(((matrix[2]==b)||((k==0)&&matrix[2]==0))
                    &&((matrix[4]==b)||((k==1)&&matrix[4]==0))
                    &&((matrix[6]==b)||((k==2)&&matrix[6]==0)))
            {
                choise = (2+2*k);
                break;
            }
        }
    }
    return choise;

}

QPushButton* MainWindow::getButton(int n)
{
    QPushButton *butt;
    switch (n)
    {
    case 0:
        butt=ui->pushButton_11;
        break;
    case 1:
        butt=ui->pushButton_12;
        break;
    case 2:
        butt=ui->pushButton_13;
        break;
    case 3:
        butt=ui->pushButton_21;
        break;
    case 4:
        butt=ui->pushButton_22;
        break;
    case 5:
        butt=ui->pushButton_23;
        break;
    case 6:
        butt=ui->pushButton_31;
        break;
    case 7:
        butt=ui->pushButton_32;
        break;
    case 8:
        butt=ui->pushButton_33;
        break;
    default:
        butt=nullptr;
        break;

    }
    return butt;
}

void MainWindow::newGame()
{
    clear_Butt();
    clearMatrix();
    ui->label_2->clear();
    setActive(true);
    move = 0;
}

