#include "zaryabot_rqt/zpanel.h"
#include "ui_zpanel.h"

#include <pluginlib/class_list_macros.h>

zaryabot_rqt::ZPanel::ZPanel() :
  rqt_gui_cpp::Plugin(),
  ui_(new Ui::ZPanel()),
  widget_(0)
{
  setObjectName("ZPanel");
}


zaryabot_rqt::ZPanel::~ZPanel()
{
  delete ui_;
}

void zaryabot_rqt::ZPanel::initPlugin(qt_gui_cpp::PluginContext &context)
{
  widget_ = new QWidget();
  ui_->setupUi(widget_);

  if (context.serialNumber() > 1)
  {
    widget_->setWindowTitle(widget_->windowTitle() + " (" + QString::number(context.serialNumber()) + ")");
  }
  context.addWidget(widget_);


}

void zaryabot_rqt::ZPanel::shutdownPlugin()
{

}

void zaryabot_rqt::ZPanel::saveSettings(qt_gui_cpp::Settings &plugin_settings, qt_gui_cpp::Settings &instance_settings) const
{
//  QString topic = ui_.topics_combo_box->currentText();
//  //qDebug("ImageView::saveSettings() topic '%s'", topic.toStdString().c_str());
//  instance_settings.setValue("topic", topic);
//  instance_settings.setValue("zoom1", ui_.zoom_1_push_button->isChecked());
//  instance_settings.setValue("dynamic_range", ui_.dynamic_range_check_box->isChecked());
//  instance_settings.setValue("max_range", ui_.max_range_double_spin_box->value());
}

void zaryabot_rqt::ZPanel::restoreSettings(const qt_gui_cpp::Settings &plugin_settings, const qt_gui_cpp::Settings &instance_settings)
{
//  bool zoom1_checked = instance_settings.value("zoom1", false).toBool();
//  ui_.zoom_1_push_button->setChecked(zoom1_checked);

//  bool dynamic_range_checked = instance_settings.value("dynamic_range", false).toBool();
//  ui_.dynamic_range_check_box->setChecked(dynamic_range_checked);

//  double max_range = instance_settings.value("max_range", ui_.max_range_double_spin_box->value()).toDouble();
//  ui_.max_range_double_spin_box->setValue(max_range);

//  QString topic = instance_settings.value("topic", "").toString();
//  //qDebug("ImageView::restoreSettings() topic '%s'", topic.toStdString().c_str());
//  selectTopic(topic);
}

PLUGINLIB_EXPORT_CLASS(zaryabot_rqt::ZPanel, rqt_gui_cpp::Plugin)
