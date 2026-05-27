// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the T i g h t V N C software.  Please visit our Web site:
//
//                       http://www.t i g h t v n c.com/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
#include "framework.h"
#include "SpinControl.h"
////#include <CommCtrl.h>
//#include "util/StringParser.h"

namespace innate_subsystem
{
//    SpinControl::SpinControl()
//    // : m_buddy(NULL),
//    //   m_isAutoAccelerationEnabled(false), m_maxDelta(0)
//    {
//    }
//
//    SpinControl::~SpinControl()
//    {
//    }
//
//    /*void SpinControl::setBuddy(ControlInterface *buddyControl)
//    {
//       // SendMessage(m_hwnd, UDM_SETBUDDY, (::wparam)buddyControl->getWindow(), NULL);
//       // m_buddy = buddyControl;
//       m_pparticleThis->setBuddy(buddyControl);
//    }
//
//    void SpinControl::setRange(::i16 lower, ::i16 upper)
//    {
//       //SendMessage(m_hwnd, UDM_SETRANGE, NULL, (::lparam)MAKELONG(upper, lower));
//       m_pparticleThis->setRange(lower, upper);
//    }
//
//    void SpinControl::setRange32(::i32 lower, ::i32 upper)
//    {
//       //SendMessage(m_hwnd, UDM_SETRANGE32, lower, upper);
//       m_pparticleThis->setRange32(lower, upper);
//    }
//
//    void SpinControl::setAccel(::u32 nSec, ::u32 nInc)
//    {
//
//       m_pparticleThis->setAccel(nSec, nInc);
//       // UDACCEL accel = {0};
//       // accel.nSec = nSec;
//       // accel.nInc = nInc;
//       //
//       // SendMessage(m_hwnd, UDM_SETACCEL, 1, (::lparam)&accel);
//    }
//
//    // void SpinControl::autoAccelerationHandler(LPNMUPDOWN message)
//    // {
//    //    m_pparticleThis->aut
//    //    // if (m_limitters.size() == 0 ||
//    //    //     m_buddy == NULL || !m_isAutoAccelerationEnabled) {
//    //    //    return;
//    //    //     }
//    //    //
//    //    // ::i32 currentValue;
//    //    // ::i32 delta = m_maxDelta;
//    //    //
//    //    // // Get buddy textbox value
//    //    // ::string storage;
//    //    // m_buddy->getText(&storage);
//    //    // if (!StringParser::parseInt(storage.getString(), &currentValue)) {
//    //    //    return;
//    //    // }
//    //    //
//    //    // size_t size = min(m_limitters.size(), m_deltas.size());
//    //    //
//    //    // if (message->iDelta < 0) {
//    //    //    for (size_t i = 0; i < size; i++) {
//    //    //       if (currentValue <= m_limitters[i]) {
//    //    //          delta = m_deltas[i];
//    //    //          break;
//    //    //       } // if
//    //    //    } // for
//    //    //    delta = -delta;
//    //    // } // if
//    //    //
//    //    // if (message->iDelta > 0) {
//    //    //    for (size_t i = 0; i < size; i++) {
//    //    //       if (currentValue < m_limitters[i]) {
//    //    //          delta = m_deltas[i];
//    //    //          break;
//    //    //       } // if
//    //    //    } // for
//    //    // } // if
//    //    //
//    //    // ::i32 mod = (currentValue + delta) % delta;
//    //    // if (mod != 0) {
//    //    //    delta -= mod;
//    //    // }
//    //    //
//    //    // message->iDelta = delta;
//    // }
//
//    void SpinControl::enableAutoAcceleration(bool enabled)
//    {
//       //m_isAutoAccelerationEnabled = enabled;
//       m_pparticleThis->enableAutoAcceleration(enabled);
//    }
//
//    void SpinControl::setAutoAccelerationParams(const i32_array & limitters,
//                                                const i32_array & deltas,
//                                                ::i32 maxDelta)
//    {
//       m_pparticleThis->setAutoAccelerationParams(limitters, deltas, maxDelta);
//       // m_limitters = *limitters;
//       // m_deltas = *deltas;
//       // m_maxDelta = maxDelta;
//    }
//    */
} // namespace innate_subsystem


