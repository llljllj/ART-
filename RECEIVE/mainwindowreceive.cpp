#include "mainwindowreceive.h"
#include "ui_mainwindowreceive.h"
#include <QSerialPortInfo>
#include <QDebug>
#include <QDateTime>
#include <QVBoxLayout>
#include <QTimer>
#include <QDateTimeAxis>
#include <QValueAxis>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), serial(new QSerialPort(this)), series(new QLineSeries(this)) {
    ui->setupUi(this);
    initializeChart();
    setWindowTitle("阿尔泰上位机软件（开发者：徐兴安&林俊）");

    //调整表格设置
    ui->ui_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->ui_tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->ui_tableWidget->setAlternatingRowColors(true);
    //美化控件
    applyStyles();
    //信号灯初始化
    ui->ui_signallight->setStyleSheet("background-color: red; border: 1px solid black; color: white;");
}

MainWindow::~MainWindow() {
    if (serial->isOpen()) {
        serial->close();
    }
    delete serial;
    delete ui;
    delete series;
    delete chart;
}

void MainWindow::setupSerialPort() {
    serial->setPortName(ui->ui_PortCombox->currentText());
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (!serial->open(QIODevice::ReadOnly)) {
        qCritical() << "Error opening COM2:" << serial->errorString();
        ui->ui_signallight->setStyleSheet("background-color: red; border: 1px solid black; color: white;");
    } else {
        connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);
         setupSignalLight();  //设置动态信号灯
    }
}

void MainWindow::readData() {
    QByteArray data = serial->readAll();
    qDebug() << "Received from COM2:" << data;
    bool ok;
    double value = data.toDouble(&ok);
    if (ok) {
        series->append(QDateTime::currentMSecsSinceEpoch(), value);
        updateChartRange();
    } else {
        qDebug() << "Data conversion error:" << data;
    }
}

void MainWindow::initializeChart() {
    chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("实时数据显示");


    chart->setBackgroundBrush(QBrush(QColor(255, 255, 255, 0)));

    chart->setTitleBrush(QBrush(QColor(52, 152, 219)));  //标题颜色

    QPen pen(Qt::red);
    pen.setWidth(2);
    series->setPen(pen); // 设置曲线样式
    series->setName("光信号强度");
    //设置X轴为时间轴
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setFormat("hh:mm:ss");        //时间格式
    axisX->setTitleText("时间");
    axisX->setLabelsFont(QFont("Arial", 10, QFont::Bold));
    axisX->setLabelsColor(QColor(52, 152, 219));
    axisX->setGridLineVisible(true);
    axisX->setGridLinePen(QPen(QColor(200, 200, 200)));

    //设置Y轴为数值轴
    QValueAxis *axisY = new QValueAxis;
    axisY->setRange(0, 1);
    axisY->setTitleText("值");
    axisY->setLabelsFont(QFont("Arial", 10, QFont::Bold));
    axisY->setLabelsColor(QColor(52, 152, 219));
    axisY->setGridLineVisible(true);
    axisY->setGridLinePen(QPen(QColor(200, 200, 200)));

    //将轴添加到图表
    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    //将数据系列连接到轴
    series->attachAxis(axisX);
    series->attachAxis(axisY);

    ui->ui_chartView->setChart(chart);
}



void MainWindow::updateChartRange() {
    //获取当前时间和最小时间
    qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
    qint64 exTime = QDateTime::currentMSecsSinceEpoch()-4000;
    qint64 timeRange = 9000;

    //获取数据中最早的时间点
    qint64 firstDataTime = series->at(0).x();  // 获取第一个数据点的时间

    //如果第一个数据点在当前时间之前，更新 X 轴范围，保持完整显示
    QDateTimeAxis *axisX = qobject_cast<QDateTimeAxis *>(chart->axisX());
    if (axisX) {
        axisX->setRange(QDateTime::fromMSecsSinceEpoch(exTime), QDateTime::fromMSecsSinceEpoch(currentTime));
    }
}



void MainWindow::on_ui_connectbutton_clicked() {
    setupSerialPort();
}

void MainWindow::applyStyles() {
    setStyleSheet(R"(
        QMainWindow {
            background: qlineargradient(
                spread:pad, x1:0, y1:0, x2:1, y2:1,
                stop:0 #F5F5F5, stop:1 #AED6F1);
        }
        QTextEdit, QLineEdit {
            background-color: #2C3E50;
            color: #ECF0F1;
            font-size: 14px;
            padding: 8px;
            border-radius: 10px;
            border: 2px solid #3498DB;
        }
        QTextEdit:focus, QLineEdit:focus {
            border: 2px solid #2980B9;
        }
        QChartView {
            background-color: white;  /* 设置背景为白色 */
            border-radius: 10px;
            color: #2C3E50; /* 字体颜色为深色，确保与白色背景对比明显 */
            font-family: Arial, Helvetica, sans-serif; /* 设置字体为无衬线字体 */
            font-size: 12px; /* 设置字体大小 */
        }
        QChartView::title {
            color: #2C3E50; /* 设置标题字体颜色为深色 */
            font-size: 16px; /* 设置标题字体大小 */
            font-weight: bold; /* 设置标题为粗体 */
        }
        QChartView::axisX, QChartView::axisY {
            color: #2C3E50; /* 设置坐标轴字体颜色为深色 */
            font-size: 12px; /* 设置坐标轴字体大小 */
        }
        QChartView::grid {
            color: #BDC3C7; /* 设置网格线颜色为浅灰色 */
        }
        QPushButton {
            background-color: #5DADE2;
            border: 2px solid #2980B9;
            border-radius: 10px;
            color: white;
            font-size: 14px;
            padding: 6px;
            box-shadow: 2px 2px 5px #BDC3C7;
        }
        QPushButton:hover {
            background-color: #3498DB;
        }
        QPushButton:pressed {
            background-color: #1F618D;
        }
        QTableWidget {
            background-color: #FAFAFA;
            border: 1px solid #BDC3C7;
            border-radius: 10px;
            gridline-color: #BDC3C7;
        }
        QTableWidget::item {
            border: 1px solid #BDC3C7;
            padding: 5px;
        }
        QHeaderView::section {
            background-color: #34495E;
            color: white;
            border: 1px solid #BDC3C7;
        }
        QLabel {
            font-size: 16px;
            color: #2E4053;
        }
    )");
}



void MainWindow::setupSignalLight() {
    // 启动定时器动态改变信号灯的颜色
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [this]() {
        static bool isGreen = false;
        if (isGreen) {
            ui->ui_signallight->setStyleSheet("background-color: green; border: 1px solid black; color: white;");
        } else {
            ui->ui_signallight->setStyleSheet("background-color: lightgreen; border: 1px solid black; color: white;");
        }
        isGreen = !isGreen;
    });
    timer->start(500); // 每 500 毫秒切换颜色
}
