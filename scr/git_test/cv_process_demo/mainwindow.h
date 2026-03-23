#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void sig_reset();


private slots:
    void sig_on_reset();
    void onload_clicked();

    void on_run_clicked();

private:
    Ui::MainWindow *ui;
    QImage _srcQImage;
};
#endif // MAINWINDOW_H
