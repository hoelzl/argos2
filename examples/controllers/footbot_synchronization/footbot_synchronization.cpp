/* Include the controller definition */
#include "footbot_synchronization.h"

/****************************************/
/****************************************/

CFootbotSynchronization::CFootbotSynchronization() :
   m_pcLEDs(NULL),
   m_pcCamera(NULL),
   m_pcRNG(NULL),
   m_unCounter(0),
   m_cCountRange(0, 100) {}

/****************************************/
/****************************************/

void CFootbotSynchronization::Init(TConfigurationNode& t_node) {
   /* Get sensor/actuator handles */
   m_pcLEDs   = dynamic_cast<CCI_FootBotLedsActuator*               >(GetRobot().GetActuator("footbot_leds"                  ));
   m_pcCamera = dynamic_cast<CCI_FootBotOmnidirectionalCameraSensor*>(GetRobot().GetSensor  ("footbot_omnidirectional_camera"));
   /*
    * Create a random number generator.
    * We use the 'argos' category so that creation, reset, seeding and cleanup are managed by ARGoS.
    */
   m_pcRNG = CARGoSRandom::CreateRNG("argos");
   /* To make all the robots initially out of sync, choose the value of the counter at random */
   m_unCounter = m_pcRNG->Uniform(m_cCountRange);
   /* Enable the camera */
   m_pcCamera->Enable();
}

/****************************************/
/****************************************/

void CFootbotSynchronization::ControlStep() {
   /* Get colored blobs from the camera */
   const CCI_CameraSensor::SCameraReadings& sBlobs = m_pcCamera->GetCameraReadings();

   /*
    * Count the red blobs.
    */
   UInt32 unRedBlobs = 0;
   for(size_t i = 0; i < sBlobs.BlobList.size(); ++i) {
      if(sBlobs.BlobList[i]->Color == CColor::RED) {
         ++unRedBlobs;
      }
   }

   /*
    * If a red blob is seen, it means someone flashed its LEDs
    * Following Strogatz' algorithm, the counter increases by an amount
    * that depends on the value of m_unCounter. For simplicity, here we
    * just increment m_unCounter by m_unCounter/10.
    * If no blobs were seen, then just increase the counter by 1.
    */
   if(unRedBlobs > 0) {
      m_unCounter += m_unCounter / 10;
   }
   else {
      ++m_unCounter;
   }

   /*
    * If the counter reached the max value, flash the LEDs
    * and zero m_unCounter.
    * Otherwise, switch the LEDs off, which means
    * setting their color to black.
   */
   if(m_unCounter > m_cCountRange.GetMax()) {
      m_pcLEDs->SetAllColors(CColor::RED);
      m_unCounter = 0;
   }
   else {
      m_pcLEDs->SetAllColors(CColor::BLACK);
   }
}

/****************************************/
/****************************************/

void CFootbotSynchronization::Reset() {
   /*
    * Reset the controller.
    * This means bringing the controller to the same state as when Init() finished its execution.
    * Since we created the RNG in the 'argos' category, we don't need to reset it.
    * The only thing we need to do here is resetting the counter.
    */
   m_unCounter = m_pcRNG->Uniform(m_cCountRange);
}

/****************************************/
/****************************************/

REGISTER_CONTROLLER(CFootbotSynchronization, "footbot_synchronization_controller")
