/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_3;
    QSplitter *splitter;
    QWidget *param;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *load;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QDoubleSpinBox *thresord1_value;
    QComboBox *apturesize_value;
    QLabel *label_3;
    QDoubleSpinBox *thresord2_value;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label_5;
    QCheckBox *grad_value;
    QSpacerItem *verticalSpacer;
    QPushButton *run;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *src_image_label;
    QLabel *dstimagelabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->setEnabled(true);
        MainWindow->resize(1000, 600);
        MainWindow->setMinimumSize(QSize(1000, 0));
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        MainWindow->setSizeIncrement(QSize(0, 0));
        MainWindow->setBaseSize(QSize(0, 0));
        MainWindow->setIconSize(QSize(24, 24));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        horizontalLayout_3 = new QHBoxLayout(centralwidget);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 4, 0);
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Orientation::Horizontal);
        param = new QWidget(splitter);
        param->setObjectName("param");
        param->setMinimumSize(QSize(300, 0));
        param->setMaximumSize(QSize(500, 16777188));
        param->setStyleSheet(QString::fromUtf8(""));
        verticalLayout = new QVBoxLayout(param);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(param);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        lineEdit = new QLineEdit(param);
        lineEdit->setObjectName("lineEdit");

        horizontalLayout_2->addWidget(lineEdit);

        load = new QPushButton(param);
        load->setObjectName("load");
        load->setCheckable(true);

        horizontalLayout_2->addWidget(load);


        verticalLayout->addLayout(horizontalLayout_2);

        frame = new QFrame(param);
        frame->setObjectName("frame");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setStyleSheet(QString::fromUtf8(""));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName("verticalLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        thresord1_value = new QDoubleSpinBox(frame);
        thresord1_value->setObjectName("thresord1_value");

        gridLayout->addWidget(thresord1_value, 0, 1, 1, 1);

        apturesize_value = new QComboBox(frame);
        apturesize_value->addItem(QString());
        apturesize_value->addItem(QString());
        apturesize_value->addItem(QString());
        apturesize_value->setObjectName("apturesize_value");

        gridLayout->addWidget(apturesize_value, 2, 1, 1, 1);

        label_3 = new QLabel(frame);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        thresord2_value = new QDoubleSpinBox(frame);
        thresord2_value->setObjectName("thresord2_value");
        thresord2_value->setMaximum(10000.000000000000000);

        gridLayout->addWidget(thresord2_value, 1, 1, 1, 1);

        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label_4 = new QLabel(frame);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 2, 0, 1, 1);

        label_5 = new QLabel(frame);
        label_5->setObjectName("label_5");

        gridLayout->addWidget(label_5, 3, 0, 1, 1);

        grad_value = new QCheckBox(frame);
        grad_value->setObjectName("grad_value");

        gridLayout->addWidget(grad_value, 3, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        verticalLayout->addWidget(frame);

        run = new QPushButton(param);
        run->setObjectName("run");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(run->sizePolicy().hasHeightForWidth());
        run->setSizePolicy(sizePolicy2);
        run->setCheckable(true);

        verticalLayout->addWidget(run);

        splitter->addWidget(param);
        widget = new QWidget(splitter);
        widget->setObjectName("widget");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy3);
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 255);"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        src_image_label = new QLabel(widget);
        src_image_label->setObjectName("src_image_label");
        src_image_label->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 127);"));

        horizontalLayout->addWidget(src_image_label);

        dstimagelabel = new QLabel(widget);
        dstimagelabel->setObjectName("dstimagelabel");
        dstimagelabel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 85, 127);"));

        horizontalLayout->addWidget(dstimagelabel);

        splitter->addWidget(widget);

        horizontalLayout_3->addWidget(splitter);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1000, 18));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\205\245\345\233\276\347\211\207\357\274\232", nullptr));
        load->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\205\245", nullptr));
        apturesize_value->setItemText(0, QCoreApplication::translate("MainWindow", "3", nullptr));
        apturesize_value->setItemText(1, QCoreApplication::translate("MainWindow", "5", nullptr));
        apturesize_value->setItemText(2, QCoreApplication::translate("MainWindow", "7", nullptr));

        label_3->setText(QCoreApplication::translate("MainWindow", "thresord2", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "thresord1", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "apturesize", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "grad", nullptr));
        grad_value->setText(QCoreApplication::translate("MainWindow", "CheckBox", nullptr));
        run->setText(QCoreApplication::translate("MainWindow", "\346\211\247\350\241\214", nullptr));
        src_image_label->setText(QString());
        dstimagelabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
