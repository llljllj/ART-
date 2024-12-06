#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QTextStream>
#include <QDebug>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <random>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QChart>
#include <QLineSeries>

#ifndef M_PI
#define M_PI 3.1415926
#endif

// 随机数生成函数
std::vector<double> rand_vector(int len, double offset, double scale) {
    std::vector<double> vec(len);
    for (int i = 0; i < len; i++) {
        vec[i] = (((double)rand()) / RAND_MAX - offset) * scale;
    }
    return vec;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    serialPort(new QSerialPort(this)),
    sendTimer(nullptr),
    sampleIndex(0),
    isSending(false),
    dataReady(false)
{
    ui->setupUi(this);

    // 串口初始化
    serialPort->setPortName("COM1");
    serialPort->setBaudRate(QSerialPort::Baud115200);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);

    // 信号与槽连接
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::startSending);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::stopSending);

    ui->stopButton->setEnabled(false);
    applyStyles();
}

MainWindow::~MainWindow() {
    delete ui;
}
// 发送按钮函数
void MainWindow::startSending()
{
    if (!serialPort->open(QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "串口错误", "无法打开串口：" + serialPort->errorString());
        return;
    }

    isSending = true;
    sampleIndex = 0; // 确保从头开始发送
    ui->sendButton->setEnabled(false);
    ui->stopButton->setEnabled(true);

    // 定时器启动
    if (sendTimer == nullptr) {
        sendTimer = new QTimer(this);
        connect(sendTimer, &QTimer::timeout, this, &MainWindow::sendLightIntensity);
    }
    sendTimer->start(20); // 每20ms发送一次

    // 生成光强数据
    simulateLightIntensity();
}


// 停止按钮函数
void MainWindow::stopSending()
{
    isSending = false;
    ui->sendButton->setEnabled(true);
    ui->stopButton->setEnabled(false);

    if (sendTimer != nullptr) {
        sendTimer->stop();
    }

    serialPort->close();
    qDebug() << "发送已停止";
}

void MainWindow::sendLightIntensity()
{
    if (!isSending || sampleIndex >= I_real.size() || !dataReady) {
        return;
    }


    if (sampleIndex < I_real.size()) {
        QString lightIntensityStr = QString::number(I_real[sampleIndex], 'f', 4) + "\n";
        serialPort->write(lightIntensityStr.toUtf8());
        serialPort->waitForBytesWritten(100);
        sampleIndex++;
    } else {
        qDebug() << "输出超出ireal长度";
    }
}

void MainWindow::simulateLightIntensity()
{
    if (sendTimer != nullptr) {
        sendTimer->stop(); // 暂停发送以防止发送旧数据
    }

    dataReady = false; // 标记数据未准备好
    sampleIndex = 0;   // 重置发送索引

    // 获取用户输入参数
    int lightPaths = ui->OptChannels->currentIndex() + 1;
    int signalLength = ui->SignalLength->text().toInt();
    double samplingRate = ui->SamplingRate->text().toDouble();
    double signalWavelength = ui->SignalWavelength->text().toDouble();
    QStringList frequencyStrings = ui->PhaseNoise->toPlainText().split(',');

    // 验证输入
    if (signalLength <= 0 || samplingRate <= 0 || signalWavelength <= 0 || frequencyStrings.isEmpty()) {
        QMessageBox::critical(this, "输入错误", "请确保所有参数有效。");
        return;
    }

    // 解析噪声频率
    std::vector<double> noisePhaseFrequency;
    for (const QString &freqStr : frequencyStrings) {
        bool ok;
        double freq = freqStr.trimmed().toDouble(&ok);
        if (ok) {
            noisePhaseFrequency.push_back(freq);
        }
    }

    double C = 0.29979;
    double lambda = signalWavelength;
    double max_path_noise = double(5.0 / noisePhaseFrequency.size());

    // 初始化
    std::vector<std::vector<double>> path_noise(lightPaths, std::vector<double>(signalLength));
    std::vector<double> t(signalLength);
    for (int i = 0; i < signalLength; i++) {
        t[i] = i * samplingRate;
    }

    std::vector<double> A_phi1(noisePhaseFrequency.size());
    std::vector<double> A_phi2(noisePhaseFrequency.size());
    std::vector<double> A0(noisePhaseFrequency.size());
    for(int i = 0; i < noisePhaseFrequency.size(); i++){
        A0[i] = max_path_noise * exp(-noisePhaseFrequency[i]);
        if (i > noisePhaseFrequency.size() - 9) {
            A0[i] *= 0.5;
        }
    }
    // 调整因子，令多路之间的相位差异变大
    A0[0] = max_path_noise * 100.0;
    A0[1] = max_path_noise * 10.0;

    // 在程序启动时设置随机数种子
    srand((unsigned)time(NULL));

    // 光程差生成
    for (int i = 0; i < lightPaths; i++) {
        A_phi1 = rand_vector(noisePhaseFrequency.size(), 0, 1);
        A_phi2 = rand_vector(noisePhaseFrequency.size(), 0, 2 * M_PI);

        for (int j = 0; j < signalLength; j++) {
            path_noise[i][j] = (((double)rand()) / RAND_MAX - 0.5) * max_path_noise * 0.2;
            for (size_t k = 0; k < noisePhaseFrequency.size(); k++) {
                path_noise[i][j] += A0[k] * A_phi1[k] *
                                    sin(2 * M_PI * noisePhaseFrequency[k] * t[j] + A_phi2[k]);
            }
        }
    }

    // 将光程差转换为相位
    for (int i = 0; i < lightPaths; i++) {
        for (int j = 0; j < signalLength; j++) {
            path_noise[i][j] *= (2 * M_PI * C) / lambda;
        }
    }

    // 计算光强
    I_real.clear(); // 清空之前的数据
    I_real.resize(signalLength, 0.0); // 重新分配空间并初始化为 0
    for (int i = 0; i < signalLength; i++) {
        for (int j = 0; j < lightPaths; j++) {
            for (int k = 0; k < lightPaths; k++) {
                I_real[i] += cos(path_noise[j][i] - path_noise[k][i]);
            }
        }
        I_real[i] /= (lightPaths * lightPaths);
    }

    dataReady = true;
    qDebug() << "光强信号模拟完成";

    // 启动定时器以发送数据
    if (sendTimer != nullptr) {
        sendTimer->start(20);
    }


    // 数据验证
    if (lightPaths < 2) {
        QMessageBox::critical(this, "错误", "光路数必须大于等于 2！");
        return;
    }

    if (path_noise.size() < 2 || path_noise[0].size() < signalLength) {
        QMessageBox::critical(this, "错误", "光程噪声数据未正确生成！");
        return;
    }

    // 创建绘图数据
    QLineSeries *phaseDifferenceSeries = new QLineSeries();
    for (int i = 0; i < signalLength; i++) {
        double phaseDifference = path_noise[0][i] - path_noise[1][i];
        phaseDifferenceSeries->append(i * samplingRate, phaseDifference);
    }

    // 创建新图表
    QChart *phaseChart = new QChart();
    phaseChart->addSeries(phaseDifferenceSeries);
    phaseChart->setTitle("光路1和光路2的相位差随时间变化");
    phaseChart->createDefaultAxes();
    phaseChart->legend()->setVisible(true);
    phaseChart->legend()->setAlignment(Qt::AlignBottom);

    // 创建新的 QGraphicsScene
    QGraphicsScene *scene = new QGraphicsScene(this);
    ui->chartLayout->setScene(scene);  // 设置场景

    // 将图表作为 GraphicsItem 添加到场景中
    scene->addItem(phaseChart);

    // 启用抗锯齿效果
    ui->chartLayout->setRenderHint(QPainter::Antialiasing);

    // 使图表自适应 QGraphicsView 的大小，并保持比例
    ui->chartLayout->fitInView(phaseChart->sceneBoundingRect(), Qt::KeepAspectRatio);

    // 确保 QGraphicsView 的大小策略使其自适应控件
    ui->chartLayout->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    phaseChart->resize(900,400);

    qDebug() << "相位差图表已成功生成并显示。";;
}

void MainWindow::applyStyles()
{
    setStyleSheet(R"(
    QMainWindow { background-color: #F4F6F8; }
    QPushButton { background-color: #3498DB; color: white; padding: 6px; }
    QPushButton:hover { background-color: #2980B9; }
    QPushButton:pressed { background-color: #1D6FA6; }
    QTextEdit, QLineEdit { border: 1px solid #BDC3C7; padding: 8px; }
    )");
}
