#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QPushButton>
#include "randoms.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void clear_Butt();
    int check();
    void clearMatrix();

    void setActive(bool a);
    void checkWin();

    void checkBut(int b);

    void AI();
    QPushButton* getButton(int n);
    void newGame();
    int winAI(int b);

    int randAI();

    void colorizeWinner(int xo);

private slots:
    void on_pushButton_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_comboBox_activated(int index);

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_22_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_31_clicked();

    void on_pushButton_32_clicked();

    void on_pushButton_33_clicked();



private:
    Ui::MainWindow *ui;
    int mode;
    int move;
    int diff;
    int matrix[9];
    int colors[3];

};

#endif // MAINWINDOW_H
