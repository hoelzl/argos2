/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */
/**
 * @file ci_eyebot_pan_and_tilt_camera.h
 *
 * @date Jun 24, 2010
 * @author Alessandro Stranieri
 *
 * This file defines the common interface for the Pan and Tilt camera installed
 * on the eyebot.
 */

#ifndef CI_EYEBOT_PAN_AND_TILT_CAMERA_
#define CI_EYEBOT_PAN_AND_TILT_CAMERA_H_

namespace argos {
class CCI_EyeBotPanAndTiltCameraSensor;
}

#include <argos2/common/control_interface/swarmanoid/ci_camera_sensor.h>
#include <argos2/common/utility/math/vector2.h>

namespace argos {

/**
 * This class defines the common interface to the Pan and Tilt camera installed
 * on the Eyebot.
 *
 * @see CCI_CameraSensor
 */
class CCI_EyeBotPanAndTiltCameraSensor: public CCI_CameraSensor {

public:

	/* ***************** */
	/* 	INNER CLASS    */
	/* ***************** */

	struct SBookshelf {
		CVector2 m_cPosition;

		SBookshelf() :
			m_cPosition(-1, -1) {
		}

		void SetPosition(Real f_x, Real f_y) {
			m_cPosition.Set(f_x, f_y);
		}

		friend std::ostream& operator<<(std::ostream& c_os, const SBookshelf& s_bookshelf) {
			c_os << "(Bookshelf: Position " << s_bookshelf.m_cPosition << ")";
			return c_os;
		}
	};


   struct SFootbot {

        CVector2 m_cPosition;
        CColor  m_cColor;
        UInt64 m_unCounter;

        SFootbot() :
            m_cPosition(-1, -1), m_cColor(CColor::BLACK), m_unCounter(0) {
        }

        void SetPosition(Real f_x, Real f_y) {
            m_cPosition.Set(f_x, f_y);
        }

        void SetColor(CColor c_color) {
            m_cColor = c_color;
        }
    };

	/* ******************** */
	/* CLASS IMPLEMENTATION */
	/* ******************** */

	CCI_EyeBotPanAndTiltCameraSensor() :
		m_bIsCameraEnabled(false), m_bIsBookshelfDetectionEnabled(false),m_bIsFootbotCounterEnabled(false) {
	}

	virtual ~CCI_EyeBotPanAndTiltCameraSensor() {
	}

	virtual void FlipImage() = 0;

	/* ***************************** */
	/*  BOOKSHELF DETECTION METHODS	 */
	/* ***************************** */

	virtual inline void EnableBookshelfDetection() {
		m_bIsBookshelfDetectionEnabled = true;
	}

	virtual inline void DisableBookshelfDetection() {
		m_bIsBookshelfDetectionEnabled = false;
	}

	virtual inline bool IsBookshelfDetectionEnabled() const {
		return m_bIsBookshelfDetectionEnabled;
	}

   /* ***************************** */
    /*  FOOTBOT COUNTER METHODS  */
    /* ***************************** */

    virtual inline void EnableFootbotCounter() {
        m_bIsFootbotCounterEnabled = true;
    }

    virtual inline void DisableFootbotCounter() {
        m_bIsFootbotCounterEnabled = false;
    }

    virtual inline bool IsFootbotCounterEnabled() const {
        return m_bIsFootbotCounterEnabled;
    }


	/**
	 * Returns true if the camera can detect the bookshelf.
	 * @return True if the camera can detect the bookshelf
	 */
	virtual bool IsBookshelfInView() = 0;

	virtual SBookshelf GetBookshelf() = 0;

	virtual std::vector<SFootbot> GetFootbotsDetected() = 0;

protected:

	bool m_bIsCameraEnabled;
	bool m_bIsBookshelfDetectionEnabled;
	bool m_bIsFootbotCounterEnabled;

};

}

#endif
