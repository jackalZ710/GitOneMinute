#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"imagelabel.h"
#include<QLabel>
#include<QDialog>
#include<QDir>
#include<QFileDialog>
#include<QMessageBox>
#include <opencv2/opencv.hpp>
#include <QDebug>
#include"imageconverter.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->run->setFixedHeight(32);
    connect(ui->load,&QPushButton::clicked,this,&::MainWindow::onload_clicked);
   connect(this,&MainWindow::sig_reset,this,&MainWindow::sig_on_reset);
    connect(ui->run,&QPushButton::clicked,this,&MainWindow::on_run_clicked);
   ui->thresord1_value->setValue(80);
    ui->thresord2_value->setValue(200);
}


MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::sig_on_reset()
{
    ui->lineEdit->clear();
    ui->src_image_label->clear();
}

void MainWindow::onload_clicked()
{
    QString curDir = QDir::currentPath();//选择文件
    QString filename = QFileDialog::getOpenFileName(this, "select Image", curDir,
                                                    "Images (*.png *.bmp *.jpg)");
    if (filename.isEmpty())
    {
        QMessageBox::critical(this, "Error", "Open Image Failed!");
        return;
    }
    ui->lineEdit->setText(filename);
    _srcQImage = QImage(filename);
    ui->src_image_label->setQImage(_srcQImage);
}


void MainWindow::on_run_clicked()
{

    cv::Mat srcImage = ImageConvert::QImage2cvMat(_srcQImage);

    int thresord1=ui->thresord1_value->value();
    int thresord2=ui->thresord2_value->value();
    int aptruesize=ui->apturesize_value->currentText().toInt();
     bool grad = ui->grad_value->isChecked();

    cv::Mat grayImg, dstImage;
    cv::cvtColor(srcImage, grayImg, cv::COLOR_RGB2GRAY);
    cv::Canny(grayImg, dstImage, thresord1, thresord2, aptruesize,grad);

    QImage dstQImage = ImageConvert::cvMat2QImage(dstImage);
    ui->dstimagelabel->setQImage(dstQImage);
}
