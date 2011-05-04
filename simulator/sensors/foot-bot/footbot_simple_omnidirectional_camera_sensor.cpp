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
 * @file <argos2/simulator/sensors/foot-bot/footbot_simple_omnidirectional_camera_sensor.cpp>
 *
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */

#include "footbot_simple_omnidirectional_camera_sensor.h"
#include <argos2/simulator/space/entities/light_entity.h>
#include <argos2/simulator/space/entities/led_equipped_entity.h>

using namespace argos;

/****************************************/
/****************************************/

static const Real FOOTBOT_HEIGHT = 0.288699733f;

/****************************************/
/****************************************/

CFootBotSimpleOmnidirectionalCameraSensor::CFootBotSimpleOmnidirectionalCameraSensor() :
  m_bEnabled(false),
  m_cSpace(CSimulator::GetInstance().GetSpace()),
  m_cCameraRange(0,1),
  m_bShowRays(false),
  m_bCheckOcclusions(true) {
}

/****************************************/
/****************************************/

void CFootBotSimpleOmnidirectionalCameraSensor::Init(TConfigurationNode& t_tree) {
  try {
    CCI_FootBotOmnidirectionalCameraSensor::Init(t_tree);
    
    // get the camera range: nothing is perceived beyond these values
    GetNodeAttributeOrDefault(t_tree, "range", m_cCameraRange, m_cCameraRange);

    // Show rays?
    GetNodeAttributeOrDefault(t_tree, "show_rays", m_bShowRays, m_bShowRays);

    // Check occlusions
    GetNodeAttributeOrDefault(t_tree, "check_occlusions", m_bCheckOcclusions, m_bCheckOcclusions);
  }
  catch(CARGoSException& ex) {
    THROW_ARGOSEXCEPTION_NESTED("Initialization error in foot-bot omnidirectional camera.", ex);
  }
}

/****************************************/
/****************************************/

void CFootBotSimpleOmnidirectionalCameraSensor::Update() {
  // Compute only if enabled
  if(m_bEnabled) {
    // Erase the last detected blobs
    while(!m_sCameraReadings.BlobList.empty()) {
      delete m_sCameraReadings.BlobList.back();
      m_sCameraReadings.BlobList.pop_back();
    }
    CalculateBlobs();
  }
}

/****************************************/
/****************************************/

void CFootBotSimpleOmnidirectionalCameraSensor::Reset() {
  // By default, the camera is not enabled
  m_bEnabled = false;

  // Erase the last detected blobs
  while(!m_sCameraReadings.BlobList.empty()) {
    delete m_sCameraReadings.BlobList.back();
    m_sCameraReadings.BlobList.pop_back();
  }

  // Reset the sensor updating counter
  m_sCameraReadings.Counter = 0;
}

/****************************************/
/****************************************/

void CFootBotSimpleOmnidirectionalCameraSensor::Destroy() {
  m_bEnabled = false;

  while(!m_sCameraReadings.BlobList.empty()) {
    delete m_sCameraReadings.BlobList.back();
    m_sCameraReadings.BlobList.pop_back();
  }

  m_sCameraReadings.Counter = 0;
}


/****************************************/
/****************************************/

void CFootBotSimpleOmnidirectionalCameraSensor::CalculateBlobs() {
  // Get the position of the foot-bot
  const CVector3& cFootBotPosition = GetEntity().GetEmbodiedEntity().GetPosition();

  // We make the assumption that the foot-bot is rotated only around Z
  // Get the foot-bot orientation
  CRadians cTmp1, cTmp2, cOrientationZ;
  GetEntity().GetEmbodiedEntity().GetOrientation().ToEulerAngles(cOrientationZ, cTmp1, cTmp2);

  // Buffer to store the intersection data
  CSpace::SEntityIntersectionItem<CEmbodiedEntity> sIntersectionData;

  // Get the list of footbot entities
  try {
    CSpace::TAnyEntityMap& tFootBotEntityMap = m_cSpace.GetEntitiesByType("footbot_entity");
    for( CSpace::TAnyEntityMap::iterator it = tFootBotEntityMap.begin(); it != tFootBotEntityMap.end(); ++it ) {
      CFootBotEntity* footbot = any_cast<CFootBotEntity*>(it->second);
      if( (footbot != NULL) && (footbot != &GetEntity()) ) {
	CVector3 footbot_position = footbot->GetEmbodiedEntity().GetPosition();
	Real     footbot_distance = (cFootBotPosition - footbot_position).Length();
	if( m_cCameraRange.WithinMinBoundIncludedMaxBoundIncluded( footbot_distance ) ) {
	
	  CRay cOcclusionCheckRay;
	  bool bEntityOccluded = false;
	  if( m_bCheckOcclusions ) {
	    // check occlusions - APPROXIMATION: we check occluisions only
	    // among the robots. If the occlusion ray just intersect the
	    // target robot, the robot is visible and also its LEDs can be
	    // detected Initialize the occlusion check ray start to the
	    // top of the foot-bot
	    cOcclusionCheckRay.SetStart(CVector3(cFootBotPosition.GetX(), cFootBotPosition.GetY(), FOOTBOT_HEIGHT));
	    cOcclusionCheckRay.SetEnd(footbot_position);
	    bEntityOccluded = ((m_cSpace.GetClosestEmbodiedEntityIntersectedByRay(sIntersectionData, cOcclusionCheckRay)) &&
			       (sIntersectionData.IntersectedEntity == &(footbot->GetEmbodiedEntity())));
	  }
	
	  // iterate through the visible LEDs (non black)
	  if( !bEntityOccluded ) {
	    TLedEntityList& vec_leds = footbot->GetLEDEquippedEntity().GetAllLeds();
	    for( TLedEntityList::iterator it_leds = vec_leds.begin(); it_leds != vec_leds.end(); it_leds++ ) {
	      if((*it_leds)->GetColor() != CColor::BLACK) {
		CVector3 relative_led_position = (*it_leds)->GetPosition() - cFootBotPosition;
		Real     relative_led_distance = relative_led_position.Length();
	      
		// APPROXIMATION! the LED is visible only if its distance is lower than the footbot entity
		if( relative_led_distance <= footbot_distance ) {
		  CRadians relative_led_direction = relative_led_position.GetZAngle() - cOrientationZ;
		  // Add the blob
		  m_sCameraReadings.BlobList.push_back(new SBlob((*it_leds)->GetColor(),
						  -relative_led_direction,
						  relative_led_distance,
						  0.0f, // TODO: transform cm into pixel
						  0.0f // TODO: calculate area
						  ));
		}
	      }
	    }
	  }
	  else {
	    if(m_bShowRays && m_bCheckOcclusions) {
	      GetEntity().GetControllableEntity().AddCheckedRay(true, cOcclusionCheckRay);
	      GetEntity().GetControllableEntity().AddIntersectionPoint(cOcclusionCheckRay, sIntersectionData.TOnRay);
	    }
	  }
	}
      }
    }
  }
  catch(CARGoSException& ex) {}



  // Get the list of light entities
  try {
    CSpace::TAnyEntityMap& tLightEntityMap = m_cSpace.GetEntitiesByType("light_entity");
    for( CSpace::TAnyEntityMap::iterator it = tLightEntityMap.begin(); it != tLightEntityMap.end(); ++it ) {
      CLightEntity* light = any_cast<CLightEntity*>(it->second);
      CVector3 relative_light_position = light->GetPosition() - cFootBotPosition;
      Real     relative_light_distance = relative_light_position.Length();
      if( (light->GetLEDEntity().GetColor() != CColor::BLACK) &&
	  (m_cCameraRange.WithinMinBoundIncludedMaxBoundIncluded(relative_light_distance) ) ) {
	CRadians relative_light_direction = relative_light_position.GetZAngle() - cOrientationZ;
	// Add the blob
	m_sCameraReadings.BlobList.push_back(new SBlob(light->GetLEDEntity().GetColor(),
					-relative_light_direction,
					relative_light_distance,
					0.0f, // TODO: transform cm into pixel
					0.0f // TODO: calculate area
					));
      }
    }
    m_sCameraReadings.Counter++;
  }
  catch(CARGoSException& ex) {}
}


/****************************************/
/****************************************/

REGISTER_SENSOR(CFootBotSimpleOmnidirectionalCameraSensor,
		"footbot_omnidirectional_camera", "simple",
		"The foot-bot omnidirectional camera sensor (simplified and optimized for 2D)",
		"Vito Trianni [vito.trianni@istc.cnr.it]",
		"This sensor accesses the foot-bot omnidirectional camera sensor. For a\n"
		"complete description of its usage, refer to the common interface.\n"
		"In this implementation, the readings are calculated under the assumption that\n"
		"the foot-bot is always parallel to the XY plane, i.e., it rotates only around\n"
		"the Z axis. This implementation is faster than a 3D one and should be used\n"
		"only when the assumption about the foot-bot rotation holds.\n\n"
		"REQUIRED XML CONFIGURATION\n\n"
		"  <controllers>\n"
		"    ...\n"
		"    <my_controller ...>\n"
		"      ...\n"
		"      <sensors>\n"
		"        ...\n"
		"        <footbot_omnidirectional_camera implementation=\"simple\" />\n"
		"        ...\n"
		"      </sensors>\n"
		"      ...\n"
		"    </my_controller>\n"
		"    ...\n"
		"  </controllers>\n\n"
		"OPTIONAL XML CONFIGURATION\n\n"
		"It is possible to specify the range of the camera for limiting its view\n"
		"within user specified limits. This is useful to oprimize performance.\n"
		"To turn this functionality on, add the attribute 'range=\"x:y\"' in the\n"
		"XML as in this example:\n\n"
		"        ...\n"
		"        <footbot_omnidirectional_camera implementation=\"simple\"\n"
		"                                        range=\"0:1\" />\n"
		"        ...\n"
		"It is possible to draw the rays shot by the camera in the OpenGL\n"
		"visualization. This can be useful for sensor debugging but also to understand\n"
		"what's wrong in your controller.\n"
		"To turn this functionality on, add the attribute 'show_rays=\"true\"' in the\n"
		"XML as in this example:\n\n"
		"        ...\n"
		"        <footbot_omnidirectional_camera implementation=\"simple\"\n"
		"                                        show_rays=\"true\" />\n"
		"        ...\n",
		"Under development"
		);
