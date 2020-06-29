#include <rqt_dynamic_gui/rqt_dynamic_gui.h>

#include <pluginlib/class_list_macros.h>
#include <ros/master.h>

namespace rqt_dynamic_gui {


dynamic_gui::dynamic_gui() :
    rqt_gui_cpp::Plugin()
{
    setObjectName("dynamic_gui");
}

void rqt_dynamic_gui::dynamic_gui::initPlugin(qt_gui_cpp::PluginContext &context)
{
    widget = new dynamic_gui_widget();
    context.addWidget(widget);
}

void rqt_dynamic_gui::dynamic_gui::shutdownPlugin()
{

}

void rqt_dynamic_gui::dynamic_gui::saveSettings(qt_gui_cpp::Settings &plugin_settings, qt_gui_cpp::Settings &instance_settings) const
{

}

void rqt_dynamic_gui::dynamic_gui::restoreSettings(const qt_gui_cpp::Settings &plugin_settings, const qt_gui_cpp::Settings &instance_settings)
{

}

} // end namespace rqt_dynamic_gui

PLUGINLIB_EXPORT_CLASS(rqt_dynamic_gui::dynamic_gui, rqt_gui_cpp::Plugin)
