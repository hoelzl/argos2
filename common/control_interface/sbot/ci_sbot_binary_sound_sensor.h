/*
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
 * @file <common/control_interface/ci_sbot_binary_sound_sensor.h> 
 * 
 * @brief This file provides the interface of the sound sensor. This
 * interface reflects what is present on the s-bot, where the sound
 * recorded through the microphones is processed through a IFFT,
 * resulting in a power spectrum that encodes the average sound
 * intensity at given frequency intervals. The sensor can be
 * configured by specifying the target frequencies that will be
 * monitored, and the intensity threshold. In this way, it is possible
 * to perceive multiple signals at the same time, provided that the
 * frequencies are separated enough with respect to the FFT precision
 * (user specified).
 *
 * @author Vito Trianni - <vito.trianni@istc.cnr.it>
 */


#ifndef CCI_SBOTBINARYSOUNDSENSOR_H
#define CCI_SBOTBINARYSOUNDSENSOR_H


/* To avoid dependency problems when including */
namespace argos {
  class CCI_SBotBinarySoundSensor;
};


#include <argos2/common/control_interface/ci_sensor.h>

using namespace std;

namespace argos {

  class CCI_SBotBinarySoundSensor: public CCI_Sensor {
  protected:
    /** Number of target frequencies */
    unsigned int m_unNumTargetFrequencies;

    /** List of target frequencies to be perceived through the FFT */
    Real* m_pfTargetFrequencies;

    /** Intensity threshold for binary output */
    Real m_fIntensityThreshold;

    /** Precision of the IFFT (precision is 2^n, n = m_unFFTLogPrecision) */
    unsigned int m_unFFTLogPrecision;
	
  public:
    static Real BASE_FFT_FREQUENCY;

  public:
    CCI_SBotBinarySoundSensor();
    virtual ~CCI_SBotBinarySoundSensor();

    virtual int Init( const TConfigurationTree t_tree );
  };
};

#endif
