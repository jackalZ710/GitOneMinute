#include "mainwindow.h"
#include <QMainWindow>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QHBoxlayout>
#include<QVBoxlayout>
#include<QWidget>
#include<QDialog>
#include<QDir>
#include<QFileDialog>
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),QLabelimage(new QLabel(this)),QLineEditselect(new QLineEdit(this)),QPushButtonrun(new QPushButton(this)),QLabelimage_show(new QLabel(this))
    ,QPushButtonrun_run(new QPushButton())

{
    this->setFixedSize(1000,500);
    connect(QPushButtonrun,&QPushButton::clicked,this,&::MainWindow::onload_clicked);
    connect(this,&MainWindow::sig_reset,this,&MainWindow::sig_on_reset);
    intiwight();
}

MainWindow::~MainWindow() {}


void MainWindow::intiwight()
{
    QLabelimage->setText("select image");
    QPushButtonrun_run->setText("run");
    QPushButtonrun->setText("load");
    QPushButtonrun->setToolTip("select");
    QPushButtonrun->setFixedHeight(28);
   QLabelimage_show->setStyleSheet("background-color: rgb(255, 0, 127)");

    QHBoxLayout* select_layout = new QHBoxLayout();
    select_layout->addWidget(QLabelimage);
    select_layout->addWidget(QLineEditselect);
    select_layout->addWidget(QPushButtonrun);

    QVBoxLayout* left_layout = new QVBoxLayout();
    QWidget* left_widget = new  QWidget(this);
    left_layout->addLayout(select_layout);
    left_layout->addStretch();
    left_layout->addWidget(QPushButtonrun_run);
    left_widget->setLayout(left_layout);
    left_widget->setFixedWidth(350);
    left_widget->setStyleSheet("background-color: rgb(170, 0, 255);");



    QHBoxLayout* center_layout = new QHBoxLayout();
    QWidget* center_widget = new  QWidget(this);
    center_layout->addWidget(left_widget);
    center_layout->addWidget(QLabelimage_show);
    center_widget->setLayout(center_layout);
    this->setCentralWidget(center_widget);
}
void MainWindow::sig_on_reset()
{
    QLineEditselect->clear();
    QLabelimage_show->clear();
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
    QLineEditselect->setText(filename);
    auto srcQImage = QImage(filename);
   QLabelimage_show->setPixmap(QPixmap::fromImage(srcQImage).scaled(QLabelimage_show->size(),Qt::KeepAspectRatio, Qt::SmoothTransformation));
}




void MainWindow::on_run_clicked()
{
    emit sig_reset();
}
