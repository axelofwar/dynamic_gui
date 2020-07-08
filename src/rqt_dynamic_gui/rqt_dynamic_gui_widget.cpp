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
#include <cstdlib>
#include <iostream>


#include "ui_rqt_dynamic_gui_widget.h"

dynamic_gui_widget::dynamic_gui_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dynamic_gui_widget)
{
    ui->setupUi(this);

    // connect(ui->btnOK, SIGNAL(clicked()), this, SLOT(on_btnOK_clicked()));
    // connect(ui->btnCancel, SIGNAL(clicked()), this, SLOT(on_btnCancel_clicked()));
    // connect(ui->btnDbcBrowse, SIGNAL(clicked()), this, SLOT(on_btnDbcBrowse_clicked()));
    // connect(ui->btnRoslaunchBrowse, SIGNAL(clicked()), this, SLOT(on_btnRoslaunchBrowse_clicked()));
    // connect(ui->btnPortPathBrowse, SIGNAL(clicked()), this, SLOT(on_btnPortPathBrowse_clicked()));
    // connect(ui->TopicSliderRange, SIGNAL(valueChanged()), this, SLOT(on_TopicSliderRange_valueChanged()));


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

     QFile file_obj("Generate_file.json");
      // qDebug()<<"Failed to open "<<"Generate_file.json";
       if(!file_obj.open(QIODevice::ReadOnly))
       {
        //  qDebug()<<"Failed to open2 "<<"Generate_file.json";
     }

    //  std::cout <<"Before QTextStream block";
     QTextStream file_text(&file_obj);
     QString json_string;
     json_string = file_text.readAll();
     file_obj.close();
     QByteArray json_bytes = json_string.toLocal8Bit();
    //  std::cout <<"After QTextStream block";
    
    //  std::cout <<"Before auto block";
     auto json_doc=QJsonDocument::fromJson(json_bytes);
    //  std::cout <<"After auto block";

     if(json_doc.isNull()){
         //qDebug()<<"Failed to create JSON doc.";
         std::cout<<"JSON failed to create";
         exit(2);
     }
     if(!json_doc.isObject()){
         //qDebug()<<"JSON is not an object.";
         std::cout<<"JSON is not an object";
         exit(3);
     }

    std::cout <<"After if statements block";

     QJsonObject json_obj=json_doc.object();

     if(json_obj.isEmpty()){
         //qDebug()<<"JSON object is empty.";
         std::cout<<"JSON is empty";
         exit(4);
     }

    // Mapping from Json to ui
     QVariantMap json_map = json_obj.toVariantMap();

     ui->TopicSliderRange->setValue(json_map["Topic Range"].toInt());
     ui->txtDbcPath->setPlainText(json_map["Dbc Path"].toString());
     ui->plainTextEdit->setPlainText(json_map["Roslaunch file path"].toString());
     ui->txtPort->setPlainText(json_map["Port"].toString());
     ui->comboBox->setCurrentText(json_map["File size"].toString());
     ui->comboBox2->setCurrentText(json_map["File compression"].toString());
     ui->txtPortAddress->setPlainText(json_map["Port address"].toString());

     }

}

dynamic_gui_widget::~dynamic_gui_widget()
{
    delete ui;
}

void dynamic_gui_widget::on_btnCancel_clicked()
{
  //MainWindow* window = new MainWindow();
     dynamic_gui_widget::close();
}

void dynamic_gui_widget::on_btnDbcBrowse_clicked()
{
  QString FileName=QFileDialog::getOpenFileName(
      this, tr("Open File"), "/home/vuda/Desktop", "Dbc file(*.dbc)"
        );

ui->txtDbcPath->setPlainText(FileName);
}

void dynamic_gui_widget::on_btnRoslaunchBrowse_clicked()
{
  QString FileName=QFileDialog::getOpenFileName(
      this, tr("Open File"), "/home/vuda/Desktop"
        );
  ui->plainTextEdit->setPlainText(FileName);
}

void dynamic_gui_widget::on_btnPortPathBrowse_clicked()
{
  QString FileName=QFileDialog::getOpenFileName(
      this, tr("Open File"), "/home/vuda/Desktop"
        );
  ui->txtPort->setPlainText(FileName);
}

void dynamic_gui_widget::on_TopicSliderRange_valueChanged(int value)
{
    ui->TopicSliderRange->setValue(value);
}

void dynamic_gui_widget::on_btnOK_clicked()
{
  dynamic_gui_widget::close();

  QVariant var(ui->TopicSliderRange->value());
  QString uTopicRange = var.toString();//Get
  QString uDbcText = ui->txtDbcPath->toPlainText();//Get
  QString uPlainText = ui->plainTextEdit->toPlainText();//Get
  QString uPortText = ui->txtPort->toPlainText();//Get
  QString uPortAddressText = ui->txtPortAddress->toPlainText();//Get
  QVariant uComboBox = ui->comboBox->currentText();//Get
  QVariant uComboBox2 = ui->comboBox2->currentText();//Get


           //file.setFileName("test.json");
           //QFile jsonFile("test.json");
           //QString filename = "abc";

           //QString data_saved = QFileDialog::getSaveFileName(this, tr("Save File"),"/home/vuda",
                                    //json_filter, &json_filter,QFileDialog::DontUseNativeDialog);


//Saving as Json file
            QString json_filter = "*.json";
            QString data_saved = QFileDialog::getSaveFileName(this, "Save File","./Generate_file.json");


        if (data_saved.isEmpty())
            {

            }

        else
            {
             QJsonDocument doc;
             QJsonObject obj;
             obj["Topic Range"] = uTopicRange;
             obj["Dbc Path"] = uDbcText;
             obj["Roslaunch file path"] = uPlainText;
             obj["Port"] = uPortText;
             obj["Port address"] = uPortAddressText;
             obj["File size"] = uComboBox.toString();
             obj["File compression"] = uComboBox2.toString();

             doc.setObject(obj);
             QByteArray data_json = doc.toJson();
             QFile output(data_saved);

            // std::cout<<"Before QTextStream block";
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

            //  std::cout<<"Before QTextStream block";
            }
}



