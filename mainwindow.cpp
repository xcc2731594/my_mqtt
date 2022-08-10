#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client = new QMqttClient;
    client->setHostname("192.168.124.24");
    client->setPort(1883);
    client->setUsername("test");
    client->setPassword("test");

    connect(client,&QMqttClient::connected,this,&MainWindow::connectSuccessSlot);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    qDebug()<<"123";
    client->connectToHost();
}

void MainWindow::connectSuccessSlot()
{
    qDebug()<<"456";
    connect(client,&QMqttClient::messageReceived,this,&MainWindow::receiveMessageSlot);
    connect(client,&QMqttClient::disconnected,[this]()
    {
        qDebug()<<"disconnect";
    });
    client->subscribe(ui->lineEdit->text());
}

void MainWindow::receiveMessageSlot(const QByteArray &ba,const QMqttTopicName &topic)
{
    qDebug()<<"789";
    QString str = topic.name() + QString(ba);
    qDebug()<<str;

}


void MainWindow::on_pushButton_2_clicked()
{
    client->publish(ui->lineEdit->text(),ui->lineEdit_2->text().toUtf8(),0);

}

