#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include<QLabel>
#include <QMainWindow>

#define player1 1
#define player2 2
#define coin_width 101
#define coin_height 91

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int turn=player1;
    int coins_in_col[7];
    QLabel *coin;

    QVector<QVector<int>>squares{6,QVector<int>(7,0)};

private slots:
    void on_pushButton_1_clicked();

    void handle(int column_number,int &coins_in_columns);

    void update_data();

    int check_win(int row,int column);

    void update_squares(int row,int column);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
