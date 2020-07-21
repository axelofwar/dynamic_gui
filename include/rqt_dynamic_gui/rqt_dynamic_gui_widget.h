#ifndef DYNAMIC_GUI_WIDGET
#define DYNAMIC_GUI_WIDGET

#include <QWidget>
#include <QProcess>

#include <cstdlib>
#include <iostream>
#include <string>
#include <QString>
#include <QObject>
#include <QCoreApplication>

#include <ros/ros.h>
#include <ros/master.h>


namespace Ui {
class dynamic_gui_widget;
}

class dynamic_gui_widget : public QWidget
{
    Q_OBJECT

public:
    dynamic_gui_widget(QWidget *parent = nullptr);
    ~dynamic_gui_widget();

    void shutdown_process();


protected:
//    qint64 *pid;


private slots:

  void on_btnDbcBrowse_clicked();

  void on_btnRoslaunchBrowse_clicked();

  void on_btnRoslaunchBrowse_2_clicked();

  void on_btnPortPathBrowse_clicked();

  void on_btnOK_clicked();

  void on_btnPlayback_clicked();

  //void on_comboBox_currentTextChanged(const QString &arg1);

  //void on_TopicSliderRange_valueChanged(int value);


private:
    Ui::dynamic_gui_widget *ui;

    ros::NodeHandle nh;
    QString file;
    QString bag;

//        QObject *logging;
        QProcess *loggingProcess = new QProcess;
        QString vudaLog = "/home/vuda/catkin_ws/vuda.sh";

//        QObject *playback;
        QProcess *playbackProcess = new QProcess;
        QString vudaPlay = "/home/vuda/catkin_ws/playback.sh";

};

#endif // DYNAMIC_GUI_WIDGET
