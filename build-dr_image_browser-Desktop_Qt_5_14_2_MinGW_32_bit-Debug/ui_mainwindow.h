/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
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
    QGridLayout *gridLayout_3;
    QWidget *widget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *select_2;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *return_2;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_14;
    QLineEdit *low;
    QHBoxLayout *horizontalLayout_12;
    QCheckBox *isws;
    QLabel *label_11;
    QLineEdit *scale_w;
    QHBoxLayout *horizontalLayout_13;
    QCheckBox *isr;
    QLabel *label_12;
    QLineEdit *rotation;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_13;
    QLineEdit *high;
    QHBoxLayout *horizontalLayout_11;
    QCheckBox *ishs;
    QLabel *label_10;
    QLineEdit *scale_h;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_7;
    QComboBox *mirror;
    QHBoxLayout *horizontalLayout_9;
    QCheckBox *iss;
    QLabel *label_9;
    QLineEdit *sharp;
    QCheckBox *isi;
    QCheckBox *ise;
    QSplitter *splitter;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QLabel *imlabel;
    QWidget *widget_2;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *select;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(967, 779);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_3 = new QGridLayout(centralwidget);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(400, 500));
        widget->setMaximumSize(QSize(400, 500));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        select_2 = new QPushButton(widget);
        select_2->setObjectName(QString::fromUtf8("select_2"));

        horizontalLayout_2->addWidget(select_2);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);

        return_2 = new QPushButton(widget);
        return_2->setObjectName(QString::fromUtf8("return_2"));
        return_2->setCheckable(false);

        horizontalLayout_2->addWidget(return_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        gridLayout->addLayout(horizontalLayout_2, 9, 0, 1, 1);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_14 = new QLabel(widget);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        horizontalLayout_15->addWidget(label_14);

        low = new QLineEdit(widget);
        low->setObjectName(QString::fromUtf8("low"));

        horizontalLayout_15->addWidget(low);


        gridLayout->addLayout(horizontalLayout_15, 0, 0, 1, 1);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        isws = new QCheckBox(widget);
        isws->setObjectName(QString::fromUtf8("isws"));

        horizontalLayout_12->addWidget(isws);

        label_11 = new QLabel(widget);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_12->addWidget(label_11);

        scale_w = new QLineEdit(widget);
        scale_w->setObjectName(QString::fromUtf8("scale_w"));

        horizontalLayout_12->addWidget(scale_w);


        gridLayout->addLayout(horizontalLayout_12, 3, 0, 1, 1);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        isr = new QCheckBox(widget);
        isr->setObjectName(QString::fromUtf8("isr"));

        horizontalLayout_13->addWidget(isr);

        label_12 = new QLabel(widget);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_13->addWidget(label_12);

        rotation = new QLineEdit(widget);
        rotation->setObjectName(QString::fromUtf8("rotation"));

        horizontalLayout_13->addWidget(rotation);


        gridLayout->addLayout(horizontalLayout_13, 2, 0, 1, 1);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_13 = new QLabel(widget);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_14->addWidget(label_13);

        high = new QLineEdit(widget);
        high->setObjectName(QString::fromUtf8("high"));

        horizontalLayout_14->addWidget(high);


        gridLayout->addLayout(horizontalLayout_14, 1, 0, 1, 1);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        ishs = new QCheckBox(widget);
        ishs->setObjectName(QString::fromUtf8("ishs"));

        horizontalLayout_11->addWidget(ishs);

        label_10 = new QLabel(widget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_11->addWidget(label_10);

        scale_h = new QLineEdit(widget);
        scale_h->setObjectName(QString::fromUtf8("scale_h"));

        horizontalLayout_11->addWidget(scale_h);


        gridLayout->addLayout(horizontalLayout_11, 4, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_7 = new QLabel(widget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_10->addWidget(label_7);

        mirror = new QComboBox(widget);
        mirror->addItem(QString());
        mirror->addItem(QString());
        mirror->addItem(QString());
        mirror->setObjectName(QString::fromUtf8("mirror"));

        horizontalLayout_10->addWidget(mirror);


        gridLayout->addLayout(horizontalLayout_10, 5, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        iss = new QCheckBox(widget);
        iss->setObjectName(QString::fromUtf8("iss"));

        horizontalLayout_9->addWidget(iss);

        label_9 = new QLabel(widget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_9->addWidget(label_9);

        sharp = new QLineEdit(widget);
        sharp->setObjectName(QString::fromUtf8("sharp"));

        horizontalLayout_9->addWidget(sharp);


        gridLayout->addLayout(horizontalLayout_9, 6, 0, 1, 1);

        isi = new QCheckBox(widget);
        isi->setObjectName(QString::fromUtf8("isi"));

        gridLayout->addWidget(isi, 7, 0, 1, 1);

        ise = new QCheckBox(widget);
        ise->setObjectName(QString::fromUtf8("ise"));

        gridLayout->addWidget(ise, 8, 0, 1, 1);


        gridLayout_3->addWidget(widget, 0, 0, 1, 1);

        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        scrollArea = new QScrollArea(splitter);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setMinimumSize(QSize(0, 600));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 541, 612));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        imlabel = new QLabel(scrollAreaWidgetContents);
        imlabel->setObjectName(QString::fromUtf8("imlabel"));
        imlabel->setMinimumSize(QSize(0, 0));
        imlabel->setLocale(QLocale(QLocale::Chinese, QLocale::China));
        imlabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(imlabel);

        scrollArea->setWidget(scrollAreaWidgetContents);
        splitter->addWidget(scrollArea);
        widget_2 = new QWidget(splitter);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy1);
        widget_2->setMinimumSize(QSize(0, 80));
        widget_2->setMaximumSize(QSize(16777215, 100));
        gridLayout_2 = new QGridLayout(widget_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        select = new QPushButton(widget_2);
        select->setObjectName(QString::fromUtf8("select"));

        horizontalLayout->addWidget(select);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

        splitter->addWidget(widget_2);

        gridLayout_3->addWidget(splitter, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 967, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        select_2->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256\345\233\276\347\211\207", nullptr));
        return_2->setText(QCoreApplication::translate("MainWindow", "\345\233\236\351\200\200\346\223\215\344\275\234", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "\347\252\227\345\256\275", nullptr));
        low->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        isws->setText(QCoreApplication::translate("MainWindow", "\346\260\264\345\271\263\347\274\251\346\224\276", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\347\274\251\346\224\276\345\200\215\346\225\260", nullptr));
        scale_w->setText(QCoreApplication::translate("MainWindow", "1.0", nullptr));
        isr->setText(QCoreApplication::translate("MainWindow", "\346\227\213\350\275\254", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "\346\227\213\350\275\254\350\247\222\345\272\246", nullptr));
        rotation->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "\347\252\227\344\275\215", nullptr));
        high->setText(QCoreApplication::translate("MainWindow", "4096", nullptr));
        ishs->setText(QCoreApplication::translate("MainWindow", "\347\253\226\347\233\264\347\274\251\346\224\276", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "\347\274\251\346\224\276\345\200\215\346\225\260", nullptr));
        scale_h->setText(QCoreApplication::translate("MainWindow", "1.0", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\347\277\273\350\275\254", nullptr));
        mirror->setItemText(0, QCoreApplication::translate("MainWindow", "\344\270\215\347\277\273\350\275\254", nullptr));
        mirror->setItemText(1, QCoreApplication::translate("MainWindow", "\346\260\264\345\271\263\347\277\273\350\275\254", nullptr));
        mirror->setItemText(2, QCoreApplication::translate("MainWindow", "\347\253\226\347\233\264\347\277\273\350\275\254", nullptr));

        iss->setText(QCoreApplication::translate("MainWindow", "\351\224\220\345\214\226", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\351\224\220\345\214\226\347\250\213\345\272\246", nullptr));
        sharp->setText(QCoreApplication::translate("MainWindow", "1.0", nullptr));
        isi->setText(QCoreApplication::translate("MainWindow", "\347\201\260\345\272\246\345\217\215\350\275\254", nullptr));
        ise->setText(QCoreApplication::translate("MainWindow", "\347\233\264\346\226\271\345\233\276\345\235\207\350\241\241\345\214\226", nullptr));
        imlabel->setText(QCoreApplication::translate("MainWindow", "image", nullptr));
        select->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\345\233\276\347\211\207", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230\345\233\276\347\211\207", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
