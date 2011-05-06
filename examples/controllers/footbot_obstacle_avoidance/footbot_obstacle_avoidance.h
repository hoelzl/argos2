/*
 * AUTHOR: Carlo Pinciroli <cpinciro@ulb.ac.be>
 *
 * An example obstacle avoidance controller for the foot-bot.
 *
 * It uses the proximity sensor to detect obstacles and the wheels to
 * move the robot around. The LEDs are used to visually show to the user
 * the angle where closest obstacle was detected.
 *
 * This controller is meant to be used with the XML files:
 *    xml/obstacle_avoidance_1.xml
 *    xml/obstacle_avoidance_10.xml
 */

#ifndef FOOTBOT_OBSTACLE_AVOIDANCE_H
#define FOOTBOT_OBSTACLE_AVOIDANCE_H

/*
 * Include some necessary headers.
 */
/* Definition of the CCI_Controller class. */
#include <argos2/common/control_interface/ci_controller.h>
/* Definition of the foot-bot wheel actuator */
#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_wheels_actuator.h>
/* Definition of the foot-bot LEDs actuator */
#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_leds_actuator.h>
/* Definition of the foot-bot proximity sensor */
#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_proximity_sensor.h>

/*
 * All the ARGoS stuff in the 'argos' namespace.
 * With this statement, you save typing argos:: every time.
 */
using namespace argos;

/*
 * A controller is simply an implementation of the CCI_Controller class.
 */
class CFootbotObstacleAvoidance : public CCI_Controller {

public:

   /* Class constructor. */
   CFootbotObstacleAvoidance();
   /* Class destructor. */
   virtual ~CFootbotObstacleAvoidance() {}

   /*
    * This function initializes the controller.
    * The 't_node' variable points to the <parameters> section in the XML file
    * in the <controllers><footbot_obstacle_avoidance_controller> section.
    */
   virtual void Init(TConfigurationNode& t_node);

   /*
    * This function is called once every time step.
    * The length of the time step is set in the XML file.
    */
   virtual void ControlStep();

   /*
    * This function resets the controller to its state right after the Init().
    * It is called when you press the reset button in the GUI.
    * In this example controller there is no need for resetting anything, so
    * the function could have been omitted. It's here just for completeness.
    */
   virtual void Reset() {}

   /*
    * Called to cleanup what done by Init() when the experiment finishes.
    * In this example controller there is no need for clean anything up, so
    * the function could have been omitted. It's here just for completeness.
    */
   virtual void Destroy() {}

private:

   /* Pointer to the foot-bot wheels actuator */
   CCI_FootBotWheelsActuator*  m_pcWheels;
   /* Pointer to the foot-bot LEDs actuator */
   CCI_FootBotLedsActuator*  m_pcLEDs;
   /* Pointer to the foot-bot proximity sensor */
   CCI_FootBotProximitySensor* m_pcProximity;

   /*
    * The following variables are used as parameters for the
    * algorithm. You can set their value in the <parameters> section
    * of the XML configuration file, under the
    * <controllers><footbot_obstacle_avoidance_controller> section.
    */

   /* Maximum tolerance for the angle between
    * the robot heading direction and
    * the closest obstacle detected. */
   CDegrees m_cAlpha;
   /* Maximum tolerance for the proximity reading between
    * the robot and the closest obstacle.
    * The proximity reading is 0 when nothing is detected
    * and grows exponentially to 1 when the obstacle is
    * touching the robot.
    */
   Real m_fDelta;
   /* Wheel speed. */
   Real m_fWheelVelocity;
   /* Angle tolerance range to go straight.
    * It is set to [-alpha,alpha]. */
   CRange<CRadians> m_cGoStraightAngleRange;

};

#endif
