#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPropertyAnimation>
#include<QMessageBox>
#include <QApplication>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->turn->setText("Player1 Turn");
    for (int i=0;i<7 ;i++ ) {
        coins_in_col[i]=5;
    }

    QPixmap pix(":/resources/img/FIAL_Board.png");
    int w=ui->label->width();
    int h=ui->label->height();
    ui->label->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    QPixmap pix1(":/resources/img/red.png");
    ui->coin_ui->setPixmap(pix1.scaled(coin_width,coin_height,Qt::KeepAspectRatio));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_data(){
    QPixmap pix2(":/resources/img/yellow.png");
    QPixmap pix(":/resources/img/red.png");

    if(turn==player1){
        turn=player2;
        ui->turn->setText("Player2 Turn");
        ui->coin_ui->setPixmap(pix2.scaled(coin_width,coin_height,Qt::KeepAspectRatio));
    }else if(turn ==player2){
        turn=player1;
        ui->turn->setText("Player1 Turn");
        ui->coin_ui->setPixmap(pix.scaled(coin_width,coin_height,Qt::KeepAspectRatio));
    }

}

void MainWindow::update_squares(int row,int col){
    squares[row][col]=turn;
}

void MainWindow::handle(int column_number,int &coins_in_columns){

    coin=new QLabel(this);
    coin->setGeometry(40+((column_number)*115),160,coin_width,coin_height);

    QPropertyAnimation *animation=new QPropertyAnimation(coin,"geometry");
    animation->setDuration(150*coins_in_columns);
    animation->setStartValue(coin->geometry());
    animation->setEndValue(QRect(40+((column_number)*115),160+coins_in_columns*115,coin_width,coin_height));
    animation->start();


    if(turn==player1){
        QPixmap pix1(":/resources/img/red.png");
        coin->setPixmap(pix1.scaled(coin_width,coin_height,Qt::KeepAspectRatio));

    }else if(turn==player2){
        QPixmap pix2(":/resources/img/yellow.png");
        coin->setPixmap(pix2.scaled(coin_width,coin_height,Qt::KeepAspectRatio));

    }
    coin->show();
    update_squares(coins_in_columns,column_number);
    int result=check_win(coins_in_columns,column_number);
    if(result==1){
        QMessageBox::StandardButton reply=
                QMessageBox::information(this,"Wining","congratulations to player"+
                                         QString::number(turn)+"\n play another game?",
                                         QMessageBox::Yes,QMessageBox::No);
        if(reply==QMessageBox::Yes){
            // restart:
            qApp->quit();
            QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
        }else{
            qApp->quit();
        }

    }else{
        update_data();
        coins_in_columns--;
    }

}

int MainWindow::check_win(int row,int column){
    int current_turn=turn;
    int path1=1,path2=0;

    //way1:check horizontal
    //left
    int temp_column=column;
    while(temp_column!=0 && squares[row][temp_column-1]==current_turn){
        path1++;
        temp_column--;
    }
    //right
    temp_column=column;
    while(temp_column!=6 && squares[row][temp_column+1]==current_turn){
        path2++;
        temp_column++;
    }
    if(path1+path2>3){
        return 1;
    }

    //way2:check vertical
    //up
    path1=1,path2=0;
    int temp_row=row;
    while(temp_row!=0 && squares[temp_row-1][column]==current_turn){
        path1++;
        temp_row--;
    }
    //down
    temp_row=row;
    while(temp_row!=5 && squares[temp_row+1][column]==current_turn){
        path2++;
        temp_row++;
    }
    if(path1+path2>3){
        return 1;
    }
    //way3:main-diagonal
    path1=1,path2=0;
    temp_row=row;
    temp_column=column;
    //left-down
    while(temp_row!=5 && temp_column!=0 && squares[temp_row+1][temp_column-1]==current_turn){
        path1++;
        temp_column--;
        temp_row++;
    }
    //right-up
    temp_row=row;
    temp_column=column;
    while(temp_column!=6 && temp_row!=0 && squares[temp_row-1][temp_column+1]==current_turn){
        path2++;
        temp_column++;
        temp_row--;
    }
    if(path1+path2>3){
        return 1;
    }
    //way4-opposite_diagonal
    path1=1,path2=0;
    temp_row=row;
    temp_column=column;
    //left-up
    while(temp_row!=0 && temp_column!=0 && squares[temp_row-1][temp_column-1]==current_turn){
        path1++;
        temp_column--;
        temp_row--;
    }
    //right-down
    temp_row=row;
    temp_column=column;
    while(temp_column!=6 && temp_row!=5 && squares[temp_row+1][temp_column+1]==current_turn){
        path2++;
        temp_column++;
        temp_row++;
    }
    if(path1+path2>3){
        return 1;
    }
    return 0;
}

void MainWindow::on_pushButton_1_clicked()
{
    if(coins_in_col[0]>-1){
         handle(0,coins_in_col[0]);

    }
}


void MainWindow::on_pushButton_2_clicked()
{
    if(coins_in_col[1]>-1){
        handle(1,coins_in_col[1]);
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    if(coins_in_col[2]>-1){
        handle(2,coins_in_col[2]);
    }
}


void MainWindow::on_pushButton_4_clicked()
{
    if(coins_in_col[3]>-1){
        handle(3,coins_in_col[3]);
    }
}


void MainWindow::on_pushButton_5_clicked()
{
    if(coins_in_col[4]>-1){
        handle(4,coins_in_col[4]);
    }
}


void MainWindow::on_pushButton_6_clicked()
{
    if(coins_in_col[5]>-1){
        handle(5,coins_in_col[5]);
    }
}


void MainWindow::on_pushButton_7_clicked()
{
    if(coins_in_col[6]>-1){
        handle(6,coins_in_col[6]);
    }

}

