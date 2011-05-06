/* Include the controller definition */
#include "footbot_obstacle_avoidance.h"
/* Function definitions for XML parsing */
#include <argos2/common/utility/configuration/argos_configuration.h>
/* 2D vector definition */
#include <argos2/common/utility/math/vector2.h>

/****************************************/
/****************************************/

CFootbotObstacleAvoidance::CFootbotObstacleAvoidance() :
   m_pcWheels(NULL),
   m_pcLEDs(NULL),
   m_pcProximity(NULL),
   m_cAlpha(10.0f),
   m_fDelta(0.5f),
   m_fWheelVelocity(2.5f),
   m_cGoStraightAngleRange(-ToRadians(m_cAlpha),
                           ToRadians(m_cAlpha)) {}

/****************************************/
/****************************************/

void CFootbotObstacleAvoidance::Init(TConfigurationNode& t_node) {
   /*
    * Get sensor/actuator handles
    *
    * The passed string (ex. "footbot_wheels") corresponds to the XML tag of the device
    * whose handle we want to have. For a list of allowed values, type at the command
    * prompt:
    *
    * $ launch_argos -q actuators
    *
    * to have a list of all the possible actuators, or
    *
    * $ launch_argos -q sensors
    *
    * to have a list of all the possible sensors.
    *
    * NOTE: ARGoS creates and initializes actuators and sensors internally, on the basis of
    *       the lists provided the XML file at the <controllers><footbot_obstacle_avoidance><actuators>
    *       and <controllers><footbot_obstacle_avoidance><sensors> sections. If you forgot to
    *       list a device in the XML and then you request it here, an error occurs.
    */
   m_pcWheels    = dynamic_cast<CCI_FootBotWheelsActuator* >(GetRobot().GetActuator("footbot_wheels"   ));
   m_pcLEDs      = dynamic_cast<CCI_FootBotLedsActuator*   >(GetRobot().GetActuator("footbot_leds"     ));
   m_pcProximity = dynamic_cast<CCI_FootBotProximitySensor*>(GetRobot().GetSensor  ("footbot_proximity"));
   /*
    * Parse the XML
    *
    * The user defines this part. Here, the algorithm accepts three parameters and it's nice to
    * put them in the XML so we don't have to recompile if we want to try other settings.
    */
   GetNodeAttributeOrDefault(t_node, "alpha", m_cAlpha, m_cAlpha);
   m_cGoStraightAngleRange.Set(-ToRadians(m_cAlpha), ToRadians(m_cAlpha));
   GetNodeAttributeOrDefault(t_node, "delta", m_fDelta, m_fDelta);
   GetNodeAttributeOrDefault(t_node, "velocity", m_fWheelVelocity, m_fWheelVelocity);
}

/****************************************/
/****************************************/

void CFootbotObstacleAvoidance::ControlStep() {
   /* Get readings from proximity sensor */
   const CCI_FootBotProximitySensor::TReadings& tProxReads = m_pcProximity->GetReadings();
   /* Sum them together */
   CVector2 cAccumulator;
   for(size_t i = 0; i < tProxReads.size(); ++i) {
      cAccumulator += CVector2(tProxReads[i].Value, tProxReads[i].Angle);
   }
   cAccumulator /= tProxReads.size();
   /* If the angle of the vector is small enough and the closest obstacle is far enough,
      continue going straight, otherwise curve a little */
   CRadians cAngle = cAccumulator.Angle();
   if(m_cGoStraightAngleRange.WithinMinBoundIncludedMaxBoundIncluded(cAngle) &&
      cAccumulator.Length() < m_fDelta ) {
      /* Go straight */
      m_pcWheels->SetLinearVelocity(m_fWheelVelocity, m_fWheelVelocity);
   }
   else {
      /* Turn, depending on the sign of the angle */
      if(cAngle.GetValue() > 0.0f) {
         m_pcWheels->SetLinearVelocity(m_fWheelVelocity, 0.0f);
      }
      else {
         m_pcWheels->SetLinearVelocity(0.0f, m_fWheelVelocity);
      }
   }
   /* Set LED colors */
   m_pcLEDs->SetAllColors(CColor::BLACK);
   cAngle.UnsignedNormalize();
   UInt32 unIndex = static_cast<UInt32>(cAngle / (CRadians::PI_OVER_FOUR * 2.0f));
   m_pcLEDs->SetSingleColor(unIndex, CColor::RED);
}

/****************************************/
/****************************************/

/*
 * This statement notifies ARGoS of the existence of the controller.
 * It binds the class passed as first argument to the string passed as second argument.
 * The string is then usable in the XML configuration file to refer to this controller.
 * When ARGoS reads that string in the XML file, it knows which controller class to instantiate.
 * See also the XML configuration files for an example of how this is used.
 */
REGISTER_CONTROLLER(CFootbotObstacleAvoidance, "footbot_obstacle_avoidance_controller")
