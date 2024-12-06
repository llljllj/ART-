#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QTimer>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startSending();
    void stopSending();
    void sendLightIntensity();
    void simulateLightIntensity();

private:
    Ui::MainWindow *ui;
    QSerialPort *serialPort;
    QTimer *sendTimer;
    int sampleIndex;              // 当前发送索引
    bool isSending;               // 是否正在发送
    bool dataReady;               // 数据是否准备好
    std::vector<double> I_real;   // 光强数据
    std::vector<std::vector<double>> path_noise;  // 光程噪声
    void applyStyles();           // 界面样式设置
};

#endif // MAINWINDOW_H
