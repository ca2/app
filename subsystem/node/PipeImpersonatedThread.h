// Copyright (C) 2011,2012 GlavSoft LLC.
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
#pragma once


#include "subsystem/thread/Thread.h"


namespace subsystem
{


   class PipeImpersonatedThreadInterface :
   virtual public ::Particle
   {
   public:
      //PipeImpersonatedThread(HANDLE pipeHandle);


      //PipeImpersonatedThread();
      //virtual ~PipeImpersonatedThreadInterface() = 0;


      virtual void initialize_pipe_impersonated_thread(::subsystem::FileInterface * pfilePipe) = 0;

      virtual void waitUntilImpersonated() = 0;
      virtual bool getImpersonationSuccess() = 0;
      virtual ::string getFaultReason() = 0;

   //private:
      virtual void execute() = 0;
      virtual void onTerminate() = 0;

      // HANDLE m_pipeHandle;
      // bool m_success;
      // ::string m_faultReason;
      // WindowsEvent m_impersonationReadyEvent;
      // WindowsEvent m_threadSleeper;
   };

    //using PipeImpersonatedThreadInterface = particle_interface<PipeImpersonatedThreadInterface, ThreadInterface>;


   class CLASS_DECL_SUBSYSTEM PipeImpersonatedThreadComposite :
      virtual public Composite < PipeImpersonatedThreadInterface>
   {
   public:

      ImplementCompositeø(PipeImpersonatedThread, pipeimpersonatedthread)

      //PipeImpersonatedThread(FileInterface * pfilePipe);
      //PipeImpersonatedThreadComposite();
       //~PipeImpersonatedThreadComposite() override;

      void initialize_pipe_impersonated_thread(::subsystem::FileInterface * pfilePipe) override
      {

         m_ppipeimpersonatedthread->initialize_pipe_impersonated_thread(pfilePipe);
      }

      void waitUntilImpersonated() override {m_ppipeimpersonatedthread->waitUntilImpersonated();}
      bool getImpersonationSuccess() override { return m_ppipeimpersonatedthread->getImpersonationSuccess(); }
      ::string getFaultReason() override {return m_ppipeimpersonatedthread->getFaultReason();}

   //private:
      void execute() override{}
      void onTerminate() override{}

      // HANDLE m_pipeHandle;
      // bool m_success;
      // ::string m_faultReason;
      // WindowsEvent m_impersonationReadyEvent;
      // WindowsEvent m_threadSleeper;
   };



   class CLASS_DECL_SUBSYSTEM PipeImpersonatedThreadAggregate
       : virtual public Aggregate<PipeImpersonatedThreadComposite, ThreadAggregate>
   {
   public:

      ImplementAggregateø(PipeImpersonatedThread, Thread);

   };


   class CLASS_DECL_SUBSYSTEM PipeImpersonatedThread :
 virtual public Object < PipeImpersonatedThreadAggregate >
   {
   public:

   };



} // namespace subsystem



