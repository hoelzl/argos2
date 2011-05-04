/* -*- Mode: C++ -*-
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/**
 * @file <argos2/simulator/sensors/foot-bot/footbot_simple_omnidirectional_camera_sensor.h>
 *
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#ifndef FOOTBOT_SIMPLE_OMNIDIRECTIONAL_CAMERA_SENSOR_H
#define FOOTBOT_SIMPLE_OMNIDIRECTIONAL_CAMERA_SENSOR_H

#include <string>
#include <map>

namespace argos {
  class CFootBotSimpleOmnidirectionalCameraSensor;
  class CSpace;
}

#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_omnidirectional_camera_sensor.h>
#include <argos2/simulator/sensors/foot-bot/footbot_sensor.h>
#include <argos2/simulator/simulator.h>
#include <argos2/simulator/space/space.h>
#include <argos2/simulator/space/entities/footbot_entity.h>
#include <argos2/simulator/space/entities/embodied_entity.h>
#include <argos2/simulator/space/entities/led_equipped_entity.h>

namespace argos {

  class CFootBotSimpleOmnidirectionalCameraSensor : public CFootBotSensor,
						    public CCI_FootBotOmnidirectionalCameraSensor {

  public:

    CFootBotSimpleOmnidirectionalCameraSensor();
    virtual ~CFootBotSimpleOmnidirectionalCameraSensor() {}

    virtual void Init(TConfigurationNode& t_tree);

    virtual void Update();
    virtual void Reset();

    virtual void Destroy();

    virtual void Enable() {
      m_bEnabled = true;
    }

    virtual void Disable() {
      m_bEnabled = false;
      /* Erase the last detected blobs */
      while(!m_sCameraReadings.BlobList.empty()) {
	delete m_sCameraReadings.BlobList.back();
	m_sCameraReadings.BlobList.pop_back();
      }
    }

  private:

    void CalculateBlobs();

  private:

    bool m_bEnabled;
    CSpace& m_cSpace;
    CRange<Real> m_cCameraRange;
    bool m_bShowRays;
    bool m_bCheckOcclusions;
  };

}

#endif
