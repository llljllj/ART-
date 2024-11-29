#ifndef SINEWAVESENDER_H
#define SINEWAVESENDER_H

#include <QObject>
#include <QSerialPort>
#include <QTimer>
#include <vector>

class SineWaveSender : public QObject {
    Q_OBJECT

public:
    explicit SineWaveSender(const QString &portName, QObject *parent = nullptr);
    ~SineWaveSender();

    // 开始光信号模拟与发送
    void startSending();

private slots:
    void sendNextSample();  // 发送下一次采样值

private:
    QSerialPort *m_serialPort;  // 串口对象
    QTimer *m_timer;           // 定时器，用于发送光强数据
    int m_sampleIndex = 0;     // 采样索引
    int m_numIter;             // 迭代次数
    int m_channel;             // 通道数
    double m_C;                // 光速
    double m_CENTER_WAVELENGTH; // 中心波长
    double m_DELTA_T;          // 时间步长
    int m_NOISE_FREQ_COUNT;    // 噪声频率分量数
    std::vector<double> m_t;   // 时间数组
    std::vector<double> m_I_real; // 存储光强数据

    // 随机数生成函数 (范围 [min, max])
    double rand_in_range(double min, double max);

    // 模拟光信号并计算光强
    void simulate_optical_signal();
};

#endif // SINEWAVESENDER_H
