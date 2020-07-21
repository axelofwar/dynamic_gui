#ifndef DYNAMIC_GUI
#define DYNAMIC_GUI

#include <rqt_gui_cpp/plugin.h>
#include <std_msgs/String.h>
#include <QProcess>
#include <rqt_dynamic_gui/rqt_dynamic_gui_widget.h>

namespace rqt_dynamic_gui {

class dynamic_gui : public rqt_gui_cpp::Plugin
{
public:
    dynamic_gui();
   

    void initPlugin(qt_gui_cpp::PluginContext& context) override;
    void shutdownPlugin() override;

    void saveSettings(qt_gui_cpp::Settings& plugin_settings, qt_gui_cpp::Settings& instance_settings) const override;
    void restoreSettings(const qt_gui_cpp::Settings& plugin_settings, const qt_gui_cpp::Settings& instance_settings) override;
protected:
    dynamic_gui_widget *widget = nullptr;
private:
    // dynamic_gui_widget *widget = nullptr;
};

}

#endif // DYNAMIC_GUI

