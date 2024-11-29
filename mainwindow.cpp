#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), m_sineWaveSender(nullptr)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_sineWaveSender;
}

void MainWindow::on_startButton_clicked()
{
    // 初始化 SineWaveSender 对象并开始发送
    if (!m_sineWaveSender) {
        m_sineWaveSender = new SineWaveSender("COM1", this);
    }
    m_sineWaveSender->startSending();
}

void MainWindow::on_stopButton_clicked()
{
    // 停止发送数据并关闭串口
    if (m_sineWaveSender) {
        delete m_sineWaveSender;
        m_sineWaveSender = nullptr;
    }
}
