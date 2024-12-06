#ifndef MAINWINDOWRECEIVE_H
#define MAINWINDOWRECEIVE_H

#include <QMainWindow>
#include <QSerialPort>
#include <QChart>
#include <QLineSeries>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initializeChart();
    QChart *chart; // 图表
    QChart *chart1; // 图表
    QChart *chart2; // 图表
    QByteArray data;
    QLineSeries *series;
    void updateChartRange();
    void applyStyles();
    void setupSignalLight();

private slots:
    void readData(); // 槽函数，用于读取数据
    void on_ui_connectbutton_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *serial; // 串口对象
    void setupSerialPort(); // 函数，用于设置串口
};

#endif // MAINWINDOWRECEIVE_H
