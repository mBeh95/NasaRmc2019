#pragma once

#include <rqt_gui_cpp/plugin.h>
#include <tfr_mission_control/ui_mission_control.h>

#include <ros/ros.h>
#include <ros/console.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>

#include <tfr_msgs/EmptySrv.h>
#include <tfr_msgs/SystemStatus.h>
#include <tfr_msgs/DurationSrv.h>
#include <tfr_msgs/EmptyAction.h>
#include <tfr_msgs/TeleopAction.h>

#include <tfr_utilities/teleop_code.h>
#include <tfr_utilities/status_code.h>

#include <cstdint>

#include <QWidget>
#include <QObject>
#include <QTimer>
#include <QScrollBar>
#include <QPushButton>

namespace tfr_mission_control {

class MissionControl : public rqt_gui_cpp::Plugin {
Q_OBJECT

public:

  /* ======================================================================== */
  /* Constructor/Destructor                                                   */
  /* ======================================================================== */

  MissionControl();
  ~MissionControl();

  /* ======================================================================== */
  /* Initialize/Shutdown                                                      */
  /* ======================================================================== */

  void initPlugin(qt_gui_cpp::PluginContext& context) override;

  void shutdownPlugin() override;

  /* ======================================================================== */
  /* Settings                                                                 */
  /* ======================================================================== */

  void saveSettings(qt_gui_cpp::Settings& plugin_settings,
                    qt_gui_cpp::Settings& instance_settings) const override;

  void restoreSettings(const qt_gui_cpp::Settings& plugin_settings,
                       const qt_gui_cpp::Settings& instance_settings) override;

private:

  /* ======================================================================== */
  /* Constants                                                                */
  /* ======================================================================== */

  const std::string TAG = "MissionControl";

  /* ======================================================================== */
  /* Variables                                                                */
  /* ======================================================================== */

  Ui::MissionControlWidget ui;
  QWidget* widget;
  QTimer* countdown;

  ros::NodeHandle nh;
  actionlib::SimpleActionClient<tfr_msgs::EmptyAction> autonomy;
  actionlib::SimpleActionClient<tfr_msgs::TeleopAction> teleop;
  ros::Subscriber com;

  /* ======================================================================== */
  /* Methods                                                                  */
  /* ======================================================================== */
  void setTeleopButtons(bool value);

  void setAutonomyButtons(bool value);



  /* ======================================================================== */
  /* Events                                                                   */
  /* ======================================================================== */



  /* ======================================================================== */
  /* Callbacks                                                                */
  /* ======================================================================== */
  void renderStatus(const tfr_msgs::SystemStatusConstPtr &status);



protected slots:

  /* ======================================================================== */
  /* Slots                                                                    */
  /* ======================================================================== */


  virtual void startMission();
  virtual void startManual();
  virtual void startAutonomy();
  virtual void startTeleop();

  virtual void performTeleop(tfr_utilities::TeleopCode code);

  virtual void renderClock();
  virtual void startTimeService();


signals:

  /* ======================================================================== */
  /* Signals                                                                  */
  /* ======================================================================== */




};

} // namespace
