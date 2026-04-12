// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
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


#include "subsystem_acme/_common_header.h"
#include "subsystem_acme/Exception.h"
#include "subsystem_acme/node/ProcessCommandLine.h"
#include "subsystem_acme/thread/Lockable.h"


namespace subsystem
{

   // class CLASS_DECL_ACME GlobalMutexInterface :
   //    virtual public LockableInterface
   // {
   // public:
   //
   //
   //
   //    /**
   //     * Deletes global mutex.
   //     */
   //    virtual ~GlobalMutex() = 0;
   //
   //    virtual void initialize_global_mutex(const ::scoped_string & scopedstrName = 0, bool interSession = false, bool throwIfExist = false) = 0;
   //
   //    /**
   //     * Inherited from lockable.
   //     */
   //    virtual ::e_status lock() = 0;
   //
   //    /**
   //     * Inherited from lockable.
   //     */
   //    virtual void unlock() = 0;
   //
   // };

   /**
    * Global mutex (allows to use mutex between separate processes).
    *
    * @author yuri, enikey.
    */
   class GlobalMutexInterface :
   virtual public ::subsystem::particle_interface<GlobalMutexInterface>,
      virtual public LockableInterface
   {
   public:


      //::pointer < GlobalMutex > m_pglobalmutexThis;
      /**
       * Creates new global mutex.
       * @param [optional] name name of mutex.
       * @param throwIfExsist if flag is set then thows exception if mutex exsists.
       * @param interSession if set, then mutex can be accessed from separate sessions, if not,
       * then every session will create it's own mutex.
       * @remark if name is 0, then mutex will be unnamed.
       * @throws ::subsystem::Exception when cannot create mutex or when throwIfExist flag is set
       * and mutex already exist.
       */
      //GlobalMutexInterface(const ::scoped_string & scopedstrName = 0, bool interSession = false, bool throwIfExist = false);
      //GlobalMutex();
      /**
       * Deletes global mutex.
       */
//      virtual ~GlobalMutexInterface() = 0;


      virtual void initialize_global_mutex(const ::scoped_string & scopedstrName = 0, bool interSession = false, bool throwIfExist = false) = 0;


      /**
       * Inherited from lockable.
       */
      virtual ::e_status lock() = 0;

      /**
       * Inherited from lockable.
       */
      virtual void unlock() = 0;

   //private:
      //void setAccessToAll(HANDLE objHandle);

      //HANDLE m_mutex;
   };


   class CLASS_DECL_ACME GlobalMutex :
      virtual public ::subsystem::composite < GlobalMutexInterface >
   {
   public:

      //GlobalMutex(const ::scoped_string & scopedstrName = 0, bool interSession = false, bool throwIfExist = false);
      GlobalMutex();
      // {
      //
      //    m_pparticleThis->initialize_global_mutex(scopedstrName, interSession, throwIfExist);
      //
      // }
      ~GlobalMutex() override;


      void initialize_global_mutex(const ::scoped_string & scopedstrName = {}, bool interSession = false, bool throwIfExist = false) override;


      /**
       * Inherited from lockable.
       */
      ::e_status lock() override;

      /**
       * Inherited from lockable.
       */
      void unlock() override;

   };

   //// __GLOBALMUTEX_H__
} // namespace subsystem
