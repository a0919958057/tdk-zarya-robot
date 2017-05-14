#ifndef zaryabot_rqt__ZPanel_H
#define zaryabot_rqt__ZPanel_H

#include <rqt_gui_cpp/plugin.h>
#include "ui_zpanel.h"

#include <QWidget>

namespace Ui {
class ZPanel;
}

namespace zaryabot_rqt {

  class ZPanel :
      public rqt_gui_cpp::Plugin

  {
    Q_OBJECT

  public:
    ZPanel();
    ~ZPanel();

    virtual void initPlugin(qt_gui_cpp::PluginContext& context);

    virtual void shutdownPlugin();

    virtual void saveSettings(qt_gui_cpp::Settings& plugin_settings, qt_gui_cpp::Settings& instance_settings) const;

    virtual void restoreSettings(const qt_gui_cpp::Settings& plugin_settings, const qt_gui_cpp::Settings& instance_settings);

  private:
    Ui::ZPanel *ui_;

  protected:

    QWidget* widget_;
  };
}

#endif // zaryabot_rqt__ZPanel_H
