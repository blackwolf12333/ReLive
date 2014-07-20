#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCameraViewfinder>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QVideoEncoderSettings>
#include <QComboBox>
#include <QCameraInfo>
#include <QHBoxLayout>
#include <QFileDialog>

#include <stdio.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    stackedWidget = new QStackedWidget(ui->verticalLayoutWidget);
    stackedWidget->setObjectName(QStringLiteral("stackedWidget"));

    cameraViewer = new QCameraViewfinder();
    cameraViewer->setObjectName(QStringLiteral("cameraViewer"));
    stackedWidget->addWidget(cameraViewer);
    ui->verticalLayout->addWidget(stackedWidget);

    QHBoxLayout *horizontalLayout;
    horizontalLayout = new QHBoxLayout(ui->verticalLayoutWidget);
    horizontalLayout->setSpacing(6);
    horizontalLayout->setContentsMargins(11, 11, 11, 11);
    horizontalLayout->setObjectName(QStringLiteral("verticalLayout"));
    horizontalLayout->setContentsMargins(0, 0, 0, 0);

    recording = false;
    startStopButton = new QPushButton;
    startStopButton->setText(QString("Start"));
    QObject::connect(startStopButton, SIGNAL(clicked()), this, SLOT(onStartStopClicked()));

    QComboBox *comboBox;
    comboBox = new QComboBox;
    cameras = QCameraInfo::availableCameras();
    foreach (const QCameraInfo &cameraInfo, cameras)
        comboBox->addItem(cameraInfo.deviceName());
    horizontalLayout->addWidget(comboBox);
    horizontalLayout->addWidget(startStopButton);
    QObject::connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onCameraChange(int)));

    recordedTime = new QLabel(QString("Recorded 0"));
    horizontalLayout->addWidget(recordedTime);
    ui->verticalLayout->addLayout(horizontalLayout);

    camera = new QCamera(this);
    camera->setViewfinder(cameraViewer);

    player = new QMediaPlayer(this);

    QVideoWidget *videowidget = new QVideoWidget;
    stackedWidget->addWidget(videowidget);
    player->setVideoOutput(videowidget);

    setupRecorder();

    camera->setCaptureMode(QCamera::CaptureVideo);
    camera->start();
}

void MainWindow::onCameraChange(int newCamera) {
    camera->stop();
    camera = new QCamera(cameras.at(newCamera));
    camera->setViewfinder(cameraViewer);
    player = new QMediaPlayer(this);

    QVideoWidget *videowidget = new QVideoWidget;
    stackedWidget->addWidget(videowidget);
    player->setVideoOutput(videowidget);

    setupRecorder();

    camera->setCaptureMode(QCamera::CaptureVideo);
    camera->start();
}

void MainWindow::onStartStopClicked() {
    recording = !recording;
    if(recording) {
        chooseOutputFile();
        setupRecorder();
        recorder->record();
        startStopButton->setText(QString("Stop"));
        printf("%s\n", recorder->errorString().toStdString().c_str());
    } else {
        recorder->stop();
        startStopButton->setText(QString("Start"));
    }
}

void MainWindow::chooseOutputFile() {
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save location"), "/home/peter", tr("Video Files (*.mp4 *.avi)"));
    QUrl location(fileName);
    recorder->setOutputLocation(location);
}

void MainWindow::setupRecorder() {
    recorder = new QMediaRecorder(camera);

    QVideoEncoderSettings settings = recorder->videoSettings();
    settings.setResolution(1280,720);
    settings.setQuality(QMultimedia::VeryHighQuality);
    recorder->setVideoSettings(settings);
    QObject::connect(recorder, SIGNAL(error(QMediaRecorder::Error)), this, SLOT(recorderError(QMediaRecorder::Error)));
    QObject::connect(recorder, SIGNAL(durationChanged(qint64)), this, SLOT(onRecordedTimeUpdate()));
    camera->setCaptureMode(QCamera::CaptureVideo);
    camera->start();
}

void MainWindow::recorderError(QMediaRecorder::Error error) {
    printf("%s\n", recorder->errorString().toStdString().c_str());
}

void MainWindow::onRecordedTimeUpdate() {
    QString str = QString("Recorded %1 sec").arg(recorder->duration()/1000);
    recordedTime->setText(str);
}

MainWindow::~MainWindow()
{
    delete ui;
}
