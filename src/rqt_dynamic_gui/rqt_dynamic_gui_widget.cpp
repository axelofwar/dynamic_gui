#include <rqt_dynamic_gui/rqt_dynamic_gui_widget.h>

#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QVariant>
#include <QSlider>
#include <QProcess>
#include <QString>

#include <cstdlib>
#include <iostream>
#include <string>

#include "ui_rqt_dynamic_gui_widget.h"

dynamic_gui_widget::dynamic_gui_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dynamic_gui_widget)
{
    ui->setupUi(this);

    {
     //set file size combo box

     ui->comboBox->addItem("Select file size");
     ui->comboBox->addItem("Small");
     ui->comboBox->addItem("Medium");
     ui->comboBox->addItem("Large");

      //set file format combo box

     ui->comboBox2->addItem("Select file format");
     ui->comboBox2->addItem("BZ2");
     ui->comboBox2->addItem("LZ4");

    //read Json
 QFile file_obj("/home/vuda/Desktop/Generate_file.json");
 if(file_obj.exists())
 {
 if(!file_obj.open(QIODevice::ReadOnly))
 {
     qDebug()<<"Failed to open "<<"Generate_file.json";

 }

 QTextStream file_text(&file_obj);
 QString json_string;
 json_string = file_text.readAll();
 file_obj.close();
 QByteArray json_bytes = json_string.toLocal8Bit();


 auto json_doc=QJsonDocument::fromJson(json_bytes);

 if(json_doc.isNull()){
     //qDebug()<<"Failed to create JSON doc.";
     exit(2);
 }
 if(!json_doc.isObject()){
     //qDebug()<<"JSON is not an object.";
     exit(3);
 }

 QJsonObject json_obj=json_doc.object();

 if(json_obj.isEmpty()){
     //qDebug()<<"JSON object is empty.";
     exit(4);
 }

 // Mapping from Json to ui
 QVariantMap json_map = json_obj.toVariantMap();

//     ui->TopicSliderRange->setValue(json_map["Topic Range"].toInt());
     ui->txtDbcPath->setPlainText(json_map["DBC Path"].toString());
     ui->plainTextEdit->setPlainText(json_map["Bag path"].toString());
     ui->txtPort->setPlainText(json_map["usb_cam #"].toString());
     ui->comboBox->setCurrentText(json_map["File size limit"].toString());
     ui->comboBox2->setCurrentText(json_map["File compression"].toString());
     ui->txtPortAddress->setPlainText(json_map["Device 1"].toString());

     }
    }
}
 
 

 dynamic_gui_widget::~dynamic_gui_widget()
 {
     shutdown_process();
     delete ui;
 }

 void dynamic_gui_widget::shutdown_process()
 {
//     loggingProcess->kill();
//     playbackProcess->kill();
//     qint64 largeNum = Q_INT64_C(pid);
//     QString value = QString::number(largeNum);
//     std::string command = "pkill " + value.toString();
//     system(command);
 }

void dynamic_gui_widget::on_btnDbcBrowse_clicked()
{
  QString FileName=QFileDialog::getOpenFileName(
      this, tr("Open File"), "/home/vuda/Desktop", "Dbc file(*.dbc)"
        );
ui->txtDbcPath->setPlainText(FileName);

if(FileName.isEmpty())
{
    QMessageBox::information(this,tr("TITLE"),tr("Please choose a file for the dbc directory!"));
    FileName=QFileDialog::getOpenFileName(
        this, tr("Open File"), "/home/vuda/Desktop"
          );
    ui->plainTextEdit->setPlainText(FileName);
}

}

void dynamic_gui_widget::on_btnRoslaunchBrowse_clicked()
{
  QString FileName=QFileDialog::getOpenFileName(
      this, tr("Open File"), "/home/vuda/Desktop"
        );
  ui->plainTextEdit->setPlainText(FileName);

  if(FileName.isEmpty())
  {
      QMessageBox::information(this,tr("TITLE"),tr("Please choose a file for the bag directory!"));
      FileName=QFileDialog::getOpenFileName(
          this, tr("Open File"), "/home/vuda/Desktop"
            );
      ui->plainTextEdit->setPlainText(FileName);
  }

  std::string FileNamePath;
  std::string bagFilePath;

  bag = FileName;
  FileNamePath = bag.toStdString();

  size_t found;
  found=FileNamePath.find_last_of("/\\");

  bagFilePath = FileNamePath.substr((0,found));
//  std::cout<<bagFilePath;

  nh.setParam("Bag_Log_Directory",bagFilePath);
}

void dynamic_gui_widget::on_btnRoslaunchBrowse_2_clicked()
{
//    Playback Rosbag file path Button
    QString FileName=QFileDialog::getOpenFileName(
        this, tr("Open File"), "/home/vuda/Desktop"
          );
    ui->plainTextEdit_2->setPlainText(FileName);

    if(FileName.isEmpty())
    {
        QMessageBox::information(this,tr("TITLE"),tr("Please choose a file for the bag directory!"));
        FileName=QFileDialog::getOpenFileName(
            this, tr("Open File"), "/home/vuda/Desktop"
              );
        ui->plainTextEdit->setPlainText(FileName);
    }

    std::string stdfilename;
    std::string filePathP;

    file = FileName;
    stdfilename = file.toStdString();

    size_t found;
    found=stdfilename.find_last_of("/\\");

    filePathP = stdfilename.substr(0,found);
//    std::cout<<filePathP;

    nh.setParam("Bag_Play_Directory",filePathP);

}

void dynamic_gui_widget::on_btnPortPathBrowse_clicked()
{
  QString FileName=QFileDialog::getOpenFileName(
      this, tr("Open File"), "/home/vuda/Desktop"
        );
  ui->txtPort->setPlainText(FileName);

  if(FileName.isEmpty())
  {
      QMessageBox::information(this,tr("TITLE"),tr("Please choose a path/port for the usb cam!"));
      FileName=QFileDialog::getOpenFileName(
          this, tr("Open File"), "/home/vuda/Desktop"
            );
      ui->plainTextEdit->setPlainText(FileName);
  }
}

//void dynamic_gui_widget::on_TopicSliderRange_valueChanged(int value)
//{
    //ui->TopicSliderRange->setValue(value);
//}

void dynamic_gui_widget::on_btnPlayback_clicked()
{
       dynamic_gui_widget::close();

//Append JSON file
//       if(uBagDirText = NULL)
//           qDebug()<<"Bag directory required";

             QMessageBox::information(this,tr("TITLE"),tr("Open Playback!!"));


             playbackProcess->start(vudaPlay,QStringList() <<"playback.sh");
             playbackProcess->waitForFinished();

}


void dynamic_gui_widget::on_btnOK_clicked()
{

  dynamic_gui_widget::close();

  //QVariant var(ui->TopicSliderRange->value());
  //QString uTopicRange = var.toString();//Get
  QString uDBCText = ui->txtDbcPath->toPlainText();//Get
  QString uBagPath = ui->plainTextEdit->toPlainText();//Get
  QString uUsbcam = ui->txtPort->toPlainText();//Get
  QString uDevice1 = ui->txtPortAddress->toPlainText();//Get
  QVariant uFileSizeLimit = ui->comboBox->currentText();//Get
  QVariant uFileComp = ui->comboBox2->currentText();//Get


           //file.setFileName("test.json");
           //QFile jsonFile("test.json");
           //QString filename = "abc";

           //QString data_saved = QFileDialog::getSaveFileName(this, tr("Save File"),"/home/vuda",
                                    //json_filter, &json_filter,QFileDialog::DontUseNativeDialog);


//Saving as Json file
//            QString json_filter = "*.json";
            QString data_saved = QFileDialog::getSaveFileName(this, "Save File","./Generate_file.json");


        if (data_saved.isEmpty())
            {

            }

        else
            {
             QJsonDocument doc;
             QJsonObject obj;
             //obj["Topic Range"] = uTopicRange;
             obj["DBC Path"] = uDBCText;
             obj["Bag path"] = uBagPath;
             obj["usb_cam #"] = uUsbcam;
             obj["Device 1"] = uDevice1;
             obj["File size_limit"] = uFileSizeLimit.toString();
             obj["File compression"] = uFileComp.toString();

             doc.setObject(obj);
             QByteArray data_json = doc.toJson();
             QFile output(data_saved);

        if (output.open(QIODevice::WriteOnly | QIODevice::Text))
             {
             output.write(data_json);
             output.close();
             QMessageBox::information(this,tr("TITLE"),tr("Saved!!"));
             }
        else {
               QMessageBox::critical(this,tr("TITLE"),tr("Error while saving!!"),
                                     output.errorString());
             }

            }

        nh.setParam("DBCpath",uDBCText.toStdString());
        nh.setParam("BagPath",uBagPath.toStdString());
        nh.setParam("usbCam",uUsbcam.toStdString());
        nh.setParam("Device1",uDevice1.toStdString());
        nh.setParam("FileSizeLimit",uFileSizeLimit.toString().toStdString());
        nh.setParam("FileCompression",uFileComp.toString().toStdString());


        //command to run logging/bagging from terminal

         loggingProcess->start(vudaLog,QStringList() <<"vuda.sh");
         loggingProcess->waitForFinished();

        //experiment with single-select buttons for file size
}
