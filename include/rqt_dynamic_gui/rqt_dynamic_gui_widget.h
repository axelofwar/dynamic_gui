#ifndef DYNAMIC_GUI_WIDGET
#define DYNAMIC_GUI_WIDGET

#include <QWidget>

namespace Ui {
class dynamic_gui_widget;
}

class dynamic_gui_widget : public QWidget
{
    Q_OBJECT

public:
    explicit dynamic_gui_widget(QWidget *parent = nullptr);
    ~dynamic_gui_widget();

private slots:
  void on_btnCancel_clicked();

  void on_btnDbcBrowse_clicked();

  void on_btnRoslaunchBrowse_clicked();

  void on_btnPortPathBrowse_clicked();

  void on_TopicSliderRange_valueChanged(int value);

  void on_btnOK_clicked();

  //void on_comboBox_currentTextChanged(const QString &arg1);

  //void on_pushButton_clicked();

private:
    Ui::dynamic_gui_widget *ui;
};

#endif // DYNAMIC_GUI_WIDGET
