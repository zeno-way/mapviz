// *****************************************************************************
//
// Copyright (C) 2013 All Right Reserved, Southwest Research Institute® (SwRI®)
//
// Contract No.  10-58058A
// Contractor    Southwest Research Institute® (SwRI®)
// Address       6220 Culebra Road, San Antonio, Texas 78228-0510
// Contact       Steve Dellenback <sdellenback@swri.org> (210) 522-3914
//
// This code was developed as part of an internal research project fully funded
// by Southwest Research Institute®.
//
// THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
// KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// *****************************************************************************

#ifndef MAPVIZ_PLUGINS_GPS_PLUGIN_H_
#define MAPVIZ_PLUGINS_GPS_PLUGIN_H_

#include <mapviz/mapviz_plugin.h>
#include <mapviz/map_canvas.h>
#include <mapviz_plugins/point_draw.h>
// C++ standard libraries
#include <list>
#include <string>
#include <vector>

// QT libraries
#include <QGLWidget>
#include <QObject>
#include <QWidget>

// ROS libraries
#include <ros/ros.h>
#include <tf/transform_datatypes.h>
#include <gps_common/GPSFix.h>
#include <swri_transform_util/local_xy_util.h>

// QT autogenerated files
#include "ui_gps_config.h"

namespace mapviz_plugins
{
  class GpsPlugin : public mapviz_plugins::PointDraw
  {
    Q_OBJECT

   public:
    GpsPlugin();
    virtual ~GpsPlugin();

    bool Initialize(QGLWidget* canvas);
    void Shutdown()
    {
    }

    void Draw(double x, double y, double scale);

    void LoadConfig(const YAML::Node& node, const std::string& path);
    void SaveConfig(YAML::Emitter& emitter, const std::string& path);

    QWidget* GetConfigWidget(QWidget* parent);

   protected:
    void PrintError(const std::string& message);
    void PrintInfo(const std::string& message);
    void PrintWarning(const std::string& message);

   protected Q_SLOTS:
    void SelectTopic();
    void TopicEdited();
    void PositionToleranceChanged(double value);
    void AngleToleranceChanged(double value);
    void BufferSizeChanged(int value);

   private:
    Ui::gps_config ui_;
    QWidget* config_widget_;

    std::string topic_;

    float angle_tolerance_;

    ros::Subscriber gps_sub_;
    bool has_message_;

    swri_transform_util::LocalXyWgs84Util local_xy_util_;

    void GPSFixCallback(const gps_common::GPSFixConstPtr gps);
  };
}

#endif  // MAPVIZ_PLUGINS_GPS_PLUGIN_H_
