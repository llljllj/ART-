/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCharts/QChartView>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *sendButton;
    QPushButton *stopButton;
    QTextEdit *PhaseNoise;
    QFrame *line;
    QFrame *line_2;
    QLineEdit *SamplingRate;
    QLabel *label_3;
    QFrame *line_5;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_4;
    QFrame *line_8;
    QLabel *label_7;
    QLineEdit *SignalWavelength;
    QFrame *line_4;
    QFrame *line_3;
    QFrame *line_7;
    QLineEdit *SignalLength;
    QLabel *label_5;
    QLabel *label_6;
    QFrame *line_6;
    QComboBox *OptChannels;
    QChartView *chartLayout;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1193, 897);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        sendButton = new QPushButton(centralwidget);
        sendButton->setObjectName("sendButton");
        sendButton->setGeometry(QRect(200, 412, 131, 51));
        stopButton = new QPushButton(centralwidget);
        stopButton->setObjectName("stopButton");
        stopButton->setGeometry(QRect(460, 410, 121, 51));
        PhaseNoise = new QTextEdit(centralwidget);
        PhaseNoise->setObjectName("PhaseNoise");
        PhaseNoise->setGeometry(QRect(340, 290, 221, 91));
        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setGeometry(QRect(220, 30, 461, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(670, 40, 16, 161));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);
        SamplingRate = new QLineEdit(centralwidget);
        SamplingRate->setObjectName("SamplingRate");
        SamplingRate->setGeometry(QRect(370, 150, 131, 31));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(270, 110, 91, 31));
        line_5 = new QFrame(centralwidget);
        line_5->setObjectName("line_5");
        line_5->setGeometry(QRect(670, 230, 16, 161));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(130, 20, 91, 31));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(270, 70, 91, 31));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(270, 150, 91, 31));
        line_8 = new QFrame(centralwidget);
        line_8->setObjectName("line_8");
        line_8->setGeometry(QRect(130, 380, 551, 20));
        line_8->setFrameShape(QFrame::HLine);
        line_8->setFrameShadow(QFrame::Sunken);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(190, 280, 141, 31));
        SignalWavelength = new QLineEdit(centralwidget);
        SignalWavelength->setObjectName("SignalWavelength");
        SignalWavelength->setGeometry(QRect(360, 240, 131, 31));
        line_4 = new QFrame(centralwidget);
        line_4->setObjectName("line_4");
        line_4->setGeometry(QRect(120, 40, 16, 161));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);
        line_3 = new QFrame(centralwidget);
        line_3->setObjectName("line_3");
        line_3->setGeometry(QRect(130, 190, 551, 20));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_7 = new QFrame(centralwidget);
        line_7->setObjectName("line_7");
        line_7->setGeometry(QRect(120, 230, 16, 161));
        line_7->setFrameShape(QFrame::VLine);
        line_7->setFrameShadow(QFrame::Sunken);
        SignalLength = new QLineEdit(centralwidget);
        SignalLength->setObjectName("SignalLength");
        SignalLength->setGeometry(QRect(370, 110, 131, 31));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(130, 210, 91, 31));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(270, 250, 91, 31));
        line_6 = new QFrame(centralwidget);
        line_6->setObjectName("line_6");
        line_6->setGeometry(QRect(220, 220, 461, 16));
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);
        OptChannels = new QComboBox(centralwidget);
        OptChannels->addItem(QString());
        OptChannels->addItem(QString());
        OptChannels->addItem(QString());
        OptChannels->addItem(QString());
        OptChannels->addItem(QString());
        OptChannels->addItem(QString());
        OptChannels->addItem(QString());
        OptChannels->addItem(QString());
        OptChannels->setObjectName("OptChannels");
        OptChannels->setGeometry(QRect(370, 70, 131, 31));
        chartLayout = new QChartView(centralwidget);
        chartLayout->setObjectName("chartLayout");
        chartLayout->setGeometry(QRect(10, 470, 911, 331));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1193, 21));
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
        sendButton->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\345\217\221\351\200\201\344\277\241\345\217\267", nullptr));
        stopButton->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242\345\217\221\351\200\201\344\277\241\345\217\267", nullptr));
        PhaseNoise->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0.0005, 0.001, 0.02, 0.04, 0.06, 0.08, 0.09, 0.1, 0.2, 0.3, 0.4, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4</p></body></html>", nullptr));
        SamplingRate->setText(QCoreApplication::translate("MainWindow", "1e-4", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt;\">\344\277\241\345\217\267\351\225\277\345\272\246\357\274\232</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt;\">\347\263\273\347\273\237\345\217\202\346\225\260\357\274\232</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt;\">\345\205\211\344\277\241\345\217\267\350\267\257\346\225\260\357\274\232</span></p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt;\">\351\207\207\346\240\267\347\216\207\357\274\232</span></p></body></html>", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt;\">\345\231\252\345\243\260\347\233\270\344\275\215\351\242\221\347\216\207\346\225\260\347\273\204\357\274\232</span></p></body></html>", nullptr));
        SignalWavelength->setText(QCoreApplication::translate("MainWindow", "1.03", nullptr));
        SignalLength->setText(QCoreApplication::translate("MainWindow", "100000", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:14pt;\">\344\277\241\345\217\267\345\217\202\346\225\260\357\274\232</span></p></body></html>", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:12pt;\">\344\277\241\345\217\267\346\263\242\351\225\277\357\274\232</span></p></body></html>", nullptr));
        OptChannels->setItemText(0, QCoreApplication::translate("MainWindow", "1", nullptr));
        OptChannels->setItemText(1, QCoreApplication::translate("MainWindow", "2", nullptr));
        OptChannels->setItemText(2, QCoreApplication::translate("MainWindow", "3", nullptr));
        OptChannels->setItemText(3, QCoreApplication::translate("MainWindow", "4", nullptr));
        OptChannels->setItemText(4, QCoreApplication::translate("MainWindow", "5", nullptr));
        OptChannels->setItemText(5, QCoreApplication::translate("MainWindow", "6", nullptr));
        OptChannels->setItemText(6, QCoreApplication::translate("MainWindow", "7", nullptr));
        OptChannels->setItemText(7, QCoreApplication::translate("MainWindow", "8", nullptr));

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
