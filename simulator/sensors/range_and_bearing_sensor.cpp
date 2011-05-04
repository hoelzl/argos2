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
 * @file <argos2/simulator/sensors/foot-bot/footbot_range_and_bearing_sensor.cpp>
 *
 * @author Carlo Pinciroli - <cpinciro@ulb.ac.be>
 */

#include "range_and_bearing_sensor.h"
#include <argos2/simulator/simulator.h>
#include <argos2/simulator/space/entities/composable_entity.h>

namespace argos {

   /****************************************/
   /****************************************/

   CRangeAndBearingSensor::CRangeAndBearingSensor() :
      m_cSpace(CSimulator::GetInstance().GetSpace()),
      m_cEmbodiedSpaceHash(m_cSpace.GetEmbodiedEntitiesSpaceHash()),
      m_pcEntity(NULL),
      m_pcRABEquippedEntity(NULL),
      m_pcEmbodiedEntity(NULL),
      m_bShowRays(false),
      m_bCheckOcclusions(true){}

   /****************************************/
   /****************************************/

   void CRangeAndBearingSensor::Init(TConfigurationNode& t_tree) {
      try {
         CCI_RangeAndBearingSensor::Init(t_tree);
         /* Show rays? */
         GetNodeAttributeOrDefault(t_tree, "show_rays", m_bShowRays, m_bShowRays);
         GetNodeAttributeOrDefault(t_tree, "check_occlusions", m_bCheckOcclusions, m_bCheckOcclusions);
      }
      catch(CARGoSException& ex) {
         THROW_ARGOSEXCEPTION_NESTED("Initialization error in foot-bot range and bearing sensor.", ex);
      }
   }

   /****************************************/
   /****************************************/

   void CRangeAndBearingSensor::SetEntity(CEntity& c_entity) {
      /* Treat the entity as composable */
      CComposableEntity* pcComposableEntity = dynamic_cast<CComposableEntity*>(&c_entity);
      if(pcComposableEntity != NULL) {
         /* The entity is composable, does it have the required components? */
         if(pcComposableEntity->HasComponent("rab_equipped_entity<10>") &&
            pcComposableEntity->HasComponent("embodied_entity") &&
            pcComposableEntity->HasComponent("controllable_entity")) {
            /* Yes, it does */
            m_pcRABEquippedEntity = &(pcComposableEntity->GetComponent< CRABEquippedEntity<10> >("rab_equipped_entity<10>"));
            m_pcEmbodiedEntity = &(pcComposableEntity->GetComponent<CEmbodiedEntity>("embodied_entity"));
            m_pcControllableEntity = &(pcComposableEntity->GetComponent<CControllableEntity>("controllable_entity"));
            m_pcEntity = &c_entity;
         }
         else {
            /* No, error */
            THROW_ARGOSEXCEPTION("Cannot associate a range and bearing sensor to an entity of type \"" << c_entity.GetTypeDescription() << "\"");
         }
      }
   }

   /****************************************/
   /****************************************/

   void CRangeAndBearingSensor::Update() {
      /* Get robot position */
      const CVector3& cRobotPosition = m_pcEmbodiedEntity->GetPosition();
      /* Get robot orientation */
      CRadians cTmp1, cTmp2, cOrientationZ;
      m_pcEmbodiedEntity->GetOrientation().ToEulerAngles(cOrientationZ, cTmp1, cTmp2);
      /* Buffer for calculating the message--robot distance */
      CVector3 cVectorToMessage;
      CVector3 cVectorRobotToMessage;
      Real fMessageDistance;
      /* Buffer for the received packet */
      TRangeAndBearingReceivedPacket tPacket;
      /* Initialize the occlusion check ray start to the position of the robot */
      CRay cOcclusionCheckRay;
      cOcclusionCheckRay.SetStart(cRobotPosition);
      /* Buffer to store the intersection data */
      CSpace::SEntityIntersectionItem<CEmbodiedEntity> sIntersectionData;
      /* Ignore the sensing robot when checking for occlusions */
      TEmbodiedEntitySet tIgnoreEntities;
      tIgnoreEntities.insert(m_pcEmbodiedEntity);
      /*
       * 1. Go through all the CRABEquippedEntities<10> (those compatible with this sensor)
       * 2. For each of them
       *    a) Check that the receiver is not out of range
       *    b) Check if there is an occlusion
       *    c) If there isn't, get the info and set reading for that robot
       */
      CSpace::TAnyEntityMap& tEntityMap = m_cSpace.GetEntitiesByType("rab_equipped_entity<10>");
      for(CSpace::TAnyEntityMap::iterator it = tEntityMap.begin();
          it != tEntityMap.end();
          ++it) {
         CRABEquippedEntity<10>& cRABEntity = *(any_cast<CRABEquippedEntity<10>*>(it->second));
         /* Check the RAB equipped entity is not this robot (avoid self-messaging) */
         if(&cRABEntity != m_pcRABEquippedEntity) {
            /* Get the position of the RAB equipped entity */
            cVectorToMessage = cRABEntity.GetPosition();
            cVectorRobotToMessage = cVectorToMessage - cRobotPosition;
            /* Check that the distance is lower than the range */
            fMessageDistance = cVectorRobotToMessage.Length();
            if(fMessageDistance < cRABEntity.GetRange()) {
               /* Set the ray end */
               cOcclusionCheckRay.SetEnd(cVectorToMessage);
               /* Check occlusion between robot and message location */
               if(!m_bCheckOcclusions ||
              		(! m_cSpace.GetClosestEmbodiedEntityIntersectedByRay(sIntersectionData, cOcclusionCheckRay, tIgnoreEntities)) ||
                  sIntersectionData.IntersectedEntity->GetId() == cRABEntity.GetId()) {
                  /* The message is not occluded */
                  if(m_bShowRays) m_pcControllableEntity->AddCheckedRay(false, cOcclusionCheckRay);
                  /* Set the reading */
                  tPacket.RobotId = cRABEntity.GetId();
                  tPacket.Id = m_unLatestPacketId++;
                  cVectorRobotToMessage.ToSphericalCoordsHorizontal(tPacket.Range,
                                                                    tPacket.BearingVertical,
                                                                    tPacket.BearingHorizontal);
                  tPacket.BearingHorizontal -= cOrientationZ;
                  /* Make the angle clockwise for the robot convention */
                  tPacket.BearingHorizontal.Negate();
                  tPacket.BearingHorizontal.SignedNormalize();
                  tPacket.BearingVertical.SignedNormalize();
                  cRABEntity.GetData(tPacket.Data);
                  m_tLastReceivedPackets[cRABEntity.GetId()] = tPacket;
               }
               else {
                  /* The message is occluded */
                  if(m_bShowRays) {
                     //LOGERR << "[ROBOT id=\"" << GetEntity().GetId() << "\"] occluded by entity \"" << sIntersectionData.IntersectedEntity->GetId() << "\"" << std::endl;
                     m_pcControllableEntity->AddCheckedRay(true, cOcclusionCheckRay);
                     m_pcControllableEntity->AddIntersectionPoint(cOcclusionCheckRay, sIntersectionData.TOnRay);
                  }
               }
            }
         }
      }
   }

   /****************************************/
   /****************************************/

   void CRangeAndBearingSensor::Reset() {
      m_unLatestPacketId = 0;
      ClearRABReceivedPackets();
   }

   /****************************************/
   /****************************************/

   REGISTER_SENSOR(CRangeAndBearingSensor,
                   "range_and_bearing", "default",
                   "The Swarmanoid range and bearing sensor",
                   "Carlo Pinciroli [cpinciro@ulb.ac.be]",
                   "This sensor accesses the foot-bot range and bearing sensor. For a complete\n"
                   "description of its usage, refer to the common interface.\n"
                   "In this implementation, the readings are calculated under the assumption that\n"
                   "the foot-bot is always parallel to the XY plane, i.e., it rotates only around\n"
                   "the Z axis. This implementation is faster than a 3D one and should be used\n"
                   "REQUIRED XML CONFIGURATION\n\n"
                   "  <controllers>\n"
                   "    ...\n"
                   "    <my_controller ...>\n"
                   "      ...\n"
                   "      <sensors>\n"
                   "        ...\n"
                   "        <range_and_bearing implementation=\"default\" />\n"
                   "        ...\n"
                   "      </sensors>\n"
                   "      ...\n"
                   "    </my_controller>\n"
                   "    ...\n"
                   "  </controllers>\n\n"
                   "OPTIONAL XML CONFIGURATION\n\n"
                   "It is possible to draw the rays shot by the distance scanner in the OpenGL\n"
                   "visualization. This can be useful for sensor debugging but also to understand\n"
                   "what's wrong in your controller. In OpenGL, the rays are drawn in cyan when\n"
                   "they are not obstructed and in purple when they are. In case a ray is\n"
                   "obstructed, a black dot is drawn where the intersection occurred.\n"
                   "Additionally, the occlusion check for the range and bearing can be disabled\n"
                   "completely. This is useful, for example, in collective transport, where you\n"
                   "want the robot to communicate as it happens in reality (robots are very close\n"
                   "and hence the IR beam is always received by some of the sensors) but the\n"
                   "simulation would discard messages because occlusions are computed.\n"
                   "The show_rays functionality is off by default, whereas the check occlusion\n"
                   "is on. To switch on or off these functionalities, add the attribute\n"
                   "'show_rays=\"true\"' and/or 'check_occlusions=\"false\"' in the XML\n"
                   "as in this example:\n\n"
                   "  <controllers>\n"
                   "    ...\n"
                   "    <my_controller ...>\n"
                   "      ...\n"
                   "      <sensors>\n"
                   "        ...\n"
                   "        <range_and_bearing implementation=\"default\"\n"
                   "                                  show_rays=\"true\"\n"
                   "                                  check_occlusions=\"false\" />\n"
                   "        ...\n"
                   "      </sensors>\n"
                   "      ...\n"
                   "    </my_controller>\n"
                   "    ...\n"
                   "  </controllers>\n",
                   "Under development"
      );

}
