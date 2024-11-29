#include "sinewavesender.h"
#include <QtMath>
#include <QDebug>

SineWaveSender::SineWaveSender(const QString &portName, QObject *parent)
    : QObject(parent), m_serialPort(new QSerialPort(this)), m_timer(new QTimer(this))
{
    // 配置串口
    m_serialPort->setPortName(portName);
    m_serialPort->setBaudRate(QSerialPort::Baud9600);
    m_serialPort->setDataBits(QSerialPort::Data8);
    m_serialPort->setParity(QSerialPort::NoParity);
    m_serialPort->setStopBits(QSerialPort::OneStop);
    m_serialPort->setFlowControl(QSerialPort::NoFlowControl);

    if (!m_serialPort->open(QIODevice::WriteOnly)) {
        qWarning() << "Failed to open" << portName << ":" << m_serialPort->errorString();
        return;
    }

    // 初始化模拟参数
    m_numIter = 100000;  // 迭代次数（信号长度）
    m_channel = 8;       // 通道数
    m_C = 2.9979e-1;     // 光速
    m_CENTER_WAVELENGTH = 1.03;  // 信号波长
    m_DELTA_T = 1e-4;    // 时间步长（采样率）
    m_NOISE_FREQ_COUNT = 25;  // 噪声频率分量数

    connect(m_timer, &QTimer::timeout, this, &SineWaveSender::sendNextSample);
    // m_timer->start(1000/50);
}

SineWaveSender::~SineWaveSender() {
    if (m_serialPort->isOpen()) {
        m_serialPort->close();
    }
}

double SineWaveSender::rand_in_range(double min, double max) {
    return min + (max - min) * (static_cast<double>(rand()) / RAND_MAX);
}

void SineWaveSender::simulate_optical_signal() {
    // 初始化时间和光程噪声数组
    m_t.resize(m_numIter);
    for (int i = 0; i < m_numIter; i++) {
        m_t[i] = i * m_DELTA_T;
    }

    // 噪声频率
    double noise_frequency[m_NOISE_FREQ_COUNT] = {
        0.0005, 0.001, 0.02, 0.04, 0.06, 0.08, 0.09, 0.1, 0.2, 0.3, 0.4,
        0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4
    };

    // 噪声幅度
    double A0[m_NOISE_FREQ_COUNT];
    for (int i = 0; i < m_NOISE_FREQ_COUNT; i++) {
        A0[i] = (5.0 / m_NOISE_FREQ_COUNT) * exp(-noise_frequency[i]);
    }

    // 光程噪声生成
    std::vector<std::vector<double>> path_noise(m_channel, std::vector<double>(m_numIter));
    for (int i = 0; i < m_channel; i++) {
        for (int j = 0; j < m_numIter; j++) {
            path_noise[i][j] = rand_in_range(-0.5, 0.5) * 0.2;  // 白噪声
            for (int k = 0; k < m_NOISE_FREQ_COUNT; k++) {
                path_noise[i][j] += A0[k] * sin(2 * M_PI * noise_frequency[k] * m_t[j] + rand_in_range(0, 2 * M_PI));  // 随机噪声
            }
        }
    }

    // 相位噪声计算
    std::vector<std::vector<double>> phase_ori(m_channel, std::vector<double>(m_numIter));
    for (int i = 0; i < m_channel; i++) {
        for (int j = 0; j < m_numIter; j++) {
            phase_ori[i][j] = 2 * M_PI * m_C * path_noise[i][j] / m_CENTER_WAVELENGTH;
        }
    }

    // 随机初始化相位
    std::vector<double> phase(m_channel);
    for (int i = 0; i < m_channel; i++) {
        phase[i] = rand_in_range(-M_PI, M_PI);  // 随机生成每个通道的初始相位
    }

    // 光强计算 (I_real)
    m_I_real.resize(m_numIter, 0.0);
    for (int i = 0; i < m_numIter; i++) {
        for (int j = 0; j < m_channel; j++) {
            for (int k = 0; k < m_channel; k++) {
                // 每次计算光强时，加入随机扰动
                double random_phase_shift = rand_in_range(-0.1, 0.1);  // 添加小的随机相位扰动
                m_I_real[i] += cos(phase[j] + phase_ori[j][i] - phase[k] - phase_ori[k][i] + random_phase_shift);
            }
        }
        m_I_real[i] /= (m_channel * m_channel);  // 归一化
    }
}

void SineWaveSender::sendNextSample() {
    // 如果串口已打开，发送光强数据
    if (m_serialPort->isOpen() && m_sampleIndex < m_numIter) {
        QByteArray data = QByteArray::number(m_I_real[m_sampleIndex], 'f', 6) + "\n";  // 转为字符串并附加换行符
        qDebug()<<data;
        m_serialPort->write(data);
        m_serialPort->waitForBytesWritten(100);  // 等待数据写入

        m_sampleIndex++;  // 更新到下一个样本
    }
}

void SineWaveSender::startSending() {
    simulate_optical_signal();
    m_timer->start(1000/50);
}
