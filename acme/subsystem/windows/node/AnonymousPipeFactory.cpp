// Copyright (C) 2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the TightVNC software.  Please visit our Web site:
//
//                       http://www.tightvnc.com/
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
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
#include "framework.h"
#include "acme/_operating_system.h"
#include "AnonymousPipeFactory.h"
#include "acme/subsystem/windows/node/security/SecurityAttributes.h"


namespace windows
{
   namespace subsystem
   {
      AnonymousPipeFactory::AnonymousPipeFactory()
      : m_bufferSize(0),
        m_plogwriter(nullptr)
      {
      }

      AnonymousPipeFactory::~AnonymousPipeFactory()
      {
      }


      void AnonymousPipeFactory::initialize_anonymous_pipe_factory(unsigned int bufferSize,
                                                 ::subsystem::LogWriter *plogwriter)
      //:
        //m_log(log)
      {
         m_bufferSize = bufferSize;

         m_plogwriter =  plogwriter;
      }

      // void AnonymousPipeFactory::init(unsigned int bufferSize,
      //                                      ::subsystem::LogWriter *plogwriter)
      // {
      //    m_bufferSize = bufferSize;
      //
      //    m_plogwriter =  plogwriter;
      // }
      void AnonymousPipeFactory::generatePipes(::pointer < ::subsystem::AnonymousPipeInterface > &firstSide,
                                               bool firstSideIsInheritable,
                                               ::pointer < ::subsystem::AnonymousPipeInterface>&secondSide,
                                               bool secondSideIsInheritable)
      {
         HANDLE hFirstSideWrite = 0, hFirstSideRead = 0,
                hSecondSideWrite = 0, hSecondSideRead = 0;

         ::windows::subsystem::SecurityAttributes secAttr;
         secAttr.setInheritable();

         try {
            if (CreatePipe(&hFirstSideRead, &hSecondSideWrite,
                           secAttr._getSecurityAttributes(), m_bufferSize) == 0) {
               ::subsystem::SystemException("Cannot create anonymous pipe");
                           }
            if (CreatePipe(&hSecondSideRead, &hFirstSideWrite,
                           secAttr._getSecurityAttributes(), m_bufferSize) == 0) {
               ::subsystem::SystemException("Cannot create anonymous pipe");
                           }
         } catch (...) {
            CloseHandle(hFirstSideWrite);
            CloseHandle(hFirstSideRead);
            CloseHandle(hSecondSideWrite);
            CloseHandle(hSecondSideRead);
            throw;
         }

         const ::scoped_string & scopedstrErrMess = "Cannot disable inheritance for anonymous pipe";
         if (!firstSideIsInheritable) {
            if (SetHandleInformation(hFirstSideWrite, HANDLE_FLAG_INHERIT, 0) == 0) {
               ::subsystem::SystemException(errMess);
            }
            if (SetHandleInformation(hFirstSideRead, HANDLE_FLAG_INHERIT, 0) == 0) {
               ::subsystem::SystemException(errMess);
            }
         }
         if (!secondSideIsInheritable) {
            if (SetHandleInformation(hSecondSideWrite, HANDLE_FLAG_INHERIT, 0) == 0) {
               ::subsystem::SystemException(errMess);
            }
            if (SetHandleInformation(hSecondSideRead, HANDLE_FLAG_INHERIT, 0) == 0) {
               ::subsystem::SystemException(errMess);
            }
         }

         firstSide =allocateø AnonymousPipe(hFirstSideWrite, hFirstSideRead, m_bufferSize, m_plogwriter);
         firstSide->initialize(this);
         secondSide = allocateø AnonymousPipe(hSecondSideWrite, hSecondSideRead, m_bufferSize, m_plogwriter);
         secondSide->initialize(this);
      }
   } // namespace subsystem
} // namespace windows