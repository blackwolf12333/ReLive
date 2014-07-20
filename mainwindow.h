#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCamera>
#include <QCameraInfo>
#include <QCameraViewfinder>
#include <QStackedWidget>
#include <QPushButton>
#include <QMediaRecorder>
#include <QMediaPlayer>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onCameraChange(int newDevice);
    void onStartStopClicked();
    void recorderError(QMediaRecorder::Error error);
    void onRecordedTimeUpdate();
private:
    Ui::MainWindow *ui;
    QCamera *camera;
    QList<QCameraInfo> cameras;
    QCameraViewfinder *cameraViewer;
    QStackedWidget *stackedWidget;
    QPushButton *startStopButton;
    QMediaRecorder *recorder;
    QMediaPlayer *player;
    QLabel *recordedTime;
    bool recording;
    void chooseOutputFile();
    void setupRecorder();
};

#endif // MAINWINDOW_H
