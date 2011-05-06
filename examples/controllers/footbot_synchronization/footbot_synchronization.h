/*
 * AUTHOR: Carlo Pinciroli <cpinciro@ulb.ac.be>
 *
 * An example synchronization controller for the foot-bot based on the synchronized oscillators
 * of Mirollo and Strogatz. See paper at:
 * http://www.math.pitt.edu/~bard/classes/mth3380/syncpapers/Mirollo-Strogatz.pdf
 *
 * The experiment reproduces the synchronization mechanisms presented by Mirollo and Strogatz in their paper.
 * The robots initially flash their LEDs out of synchrony. Using the omnidirectional camera, they can perceive
 * if other robots around have flashed their LEDs. Read the paper for more information about the details.
 *
 * This controller is meant to be used with the XML file:
 *    xml/synchronization.xml
 */

#ifndef FOOTBOT_SYNCHRONIZATION_H
#define FOOTBOT_SYNCHRONIZATION_H

/*
 * Include some necessary headers.
 */
/* Definition of the CCI_Controller class. */
#include <argos2/common/control_interface/ci_controller.h>
/* Definition of the foot-bot LEDs actuator */
#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_leds_actuator.h>
/* Definition of the foot-bot camera sensor */
#include <argos2/common/control_interface/swarmanoid/footbot/ci_footbot_omnidirectional_camera_sensor.h>
/* Definitions for random number generation */
#include <argos2/common/utility/argos_random.h>

using namespace argos;

class CFootbotSynchronization : public CCI_Controller {

public:

   CFootbotSynchronization();
   virtual ~CFootbotSynchronization() {}

   virtual void Init(TConfigurationNode& t_node);
   virtual void ControlStep();
   virtual void Reset();
   virtual void Destroy() {}

private:

   /* Pointer to the foot-bot LEDs actuator */
   CCI_FootBotLedsActuator*  m_pcLEDs;
   /* Pointer to the foot-bot omnidirectional camera sensor */
   CCI_FootBotOmnidirectionalCameraSensor* m_pcCamera;

   /* The random number generator */
   CARGoSRandom::CRNG* m_pcRNG;

   /* An internal counter. When the counter reaches 10, the robot flashes. */
   UInt32 m_unCounter;
   /* The counter range */
   CRange<UInt32> m_cCountRange;
};

#endif
