//rqt plugin for tuning parameters
//Author: Sebastian Schüller

#include <ros/ros.h>
#include <dynamic_reconfigure/server.h>
#include <rqt_gui_cpp/plugin.h>
#include <sensor_msgs/Joy.h>
#include <ui_parametertuner.h>

#include <config_server/ParameterList.h>
#include <QMutex>

#ifndef PARAMETERTUNER_H
#define PARAMETERTUNER_H

namespace parametertuner
{

class Parametertuner : public QWidget
{
    Q_OBJECT
public:
    Parametertuner(ros::NodeHandle nh_);
    virtual ~Parametertuner();
    ros::NodeHandle nh_;
    void handleList(const config_server::ParameterListConstPtr& list);
    void handleJoystickInput(const sensor_msgs::JoyConstPtr& joy);
//    virtual void initPlugin(qt_gui_cpp::PluginContext& context);
//    virtual void shutdownPlugin();

Q_SIGNALS:
    void updateRequested();
    void moveSelectionRequested(int);
    void ValueChangeRequested(int);

public slots:
    void save();
    void reset();
    void handleJoystickButton();
    void update();
    void moveSelection(int dir);
    void ChangeValue(int dir);

private:
    QMutex m_mutex;
    ros::Subscriber m_sub_paramList;
    config_server::ParameterListConstPtr m_list;

    Ui::parametertuner m_ui;

    ros::Subscriber m_sub_joystick;

    bool m_useJoystick;
    bool m_buttonUp;
    bool m_buttonDown;
    bool m_buttonInc;
    bool m_buttonDec;



    void insertParameter(QString param, QTreeWidgetItem* ancestor, const config_server::ParameterDescription& description);
    QTreeWidgetItem* insertParameterNode(const config_server::ParameterDescription& description, QTreeWidgetItem* ancestor);

    void updateSelection(QTreeWidgetItem* old, QTreeWidgetItem* next);
    QTreeWidgetItem* getSelectedItem();

    void deleteWidget(QTreeWidgetItem* item);

    enum direction
    {
        UP = -1,
        DOWN = 1,
        LEFT = -1,
        RIGHT = 1
    };
};

}
#endif
