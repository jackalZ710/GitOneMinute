#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void intiwight();
private:
    QLabel* QLabelimage;
    QLineEdit* QLineEditselect;
    QPushButton* QPushButtonrun;
    QPushButton* QPushButtonrun_run;
    QLabel* QLabelimage_show;
signals:
    void sig_reset();


private slots:
    void sig_on_reset();
    void onload_clicked();

    void on_run_clicked();

};
#endif // MAINWINDOW_H
