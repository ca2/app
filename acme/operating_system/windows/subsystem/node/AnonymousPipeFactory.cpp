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
#include "acme/operating_system/windows/subsystem/_common_header.h"
#include "AnonymousPipeFactory.h"
#include "acme/operating_system/windows/subsystem/node/security/SecurityAttributes.h"
#include "AnonymousPipe.h"
#include "File.h"


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
      void AnonymousPipeFactory::generatePipes(::pointer < ::subsystem::AnonymousPipe > &firstSide,
                                               bool firstSideIsInheritable,
                                               ::pointer < ::subsystem::AnonymousPipe >&secondSide,
                                               bool secondSideIsInheritable)
      {
         ::pointer < ::windows::subsystem::File > pfileFirstSideWrite;
         ::pointer < ::windows::subsystem::File > pfileFirstSideRead;
         ::pointer < ::windows::subsystem::File > pfileSecondSideWrite;
         ::pointer < ::windows::subsystem::File > pfileSecondSideRead;

         construct_newø(pfileFirstSideWrite);
         construct_newø(pfileFirstSideRead);
         construct_newø(pfileSecondSideWrite);
         construct_newø(pfileSecondSideRead);

         pfileFirstSideWrite->m_bOwned = true;
         pfileFirstSideRead->m_bOwned = true;
         pfileSecondSideWrite->m_bOwned = true;
         pfileSecondSideRead->m_bOwned = true;

         ::windows::subsystem::SecurityAttributes secAttr;
         secAttr.setInheritable();

         try {
            if (CreatePipe(&pfileFirstSideRead->m_handle, &pfileSecondSideWrite->m_handle,
                           secAttr._getSecurityAttributes(), m_bufferSize) == 0) {
               ::subsystem::SystemException("Cannot create anonymous pipe");
                           }
            if (CreatePipe(&pfileSecondSideRead->m_handle, &pfileFirstSideWrite->m_handle,
                           secAttr._getSecurityAttributes(), m_bufferSize) == 0) {
               ::subsystem::SystemException("Cannot create anonymous pipe");
                           }
         } catch (...) {
//            CloseHandle(hFirstSideWrite);
  //          CloseHandle(hFirstSideRead);
    //        CloseHandle(hSecondSideWrite);
      //      CloseHandle(hSecondSideRead);
            throw;
         }

         const ::scoped_string & scopedstrErrMess = "Cannot disable inheritance for anonymous pipe";
         if (!firstSideIsInheritable) {
            if (SetHandleInformation(pfileFirstSideWrite->m_handle, HANDLE_FLAG_INHERIT, 0) == 0) {
               ::subsystem::SystemException(errMess);
            }
            if (SetHandleInformation(pfileFirstSideRead->m_handle, HANDLE_FLAG_INHERIT, 0) == 0) {
               ::subsystem::SystemException(errMess);
            }
         }
         if (!secondSideIsInheritable) {
            if (SetHandleInformation(pfileSecondSideWrite->m_handle, HANDLE_FLAG_INHERIT, 0) == 0) {
               ::subsystem::SystemException(errMess);
            }
            if (SetHandleInformation(pfileSecondSideRead->m_handle, HANDLE_FLAG_INHERIT, 0) == 0) {
               ::subsystem::SystemException(errMess);
            }
         }

         auto panonymouspipeFirst = create_newø < AnonymousPipe>();
         panonymouspipeFirst->initialize_anonymous_pipe(pfileFirstSideWrite, pfileFirstSideRead, m_bufferSize, m_plogwriter);
         firstSide =panonymouspipeFirst;
         auto panonymouspipeSecond = create_newø < AnonymousPipe>();
         panonymouspipeSecond->initialize_anonymous_pipe(pfileSecondSideWrite, pfileSecondSideRead, m_bufferSize, m_plogwriter);
         secondSide = panonymouspipeSecond;
         secondSide->initialize(this);
      }
   } // namespace subsystem
} // namespace windows