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


#include "subsystem/_common_header.h"
#include "subsystem/platform/Exception.h"
#include "subsystem/node/ProcessCommandLine.h"
#include "subsystem/thread/Lockable.h"


namespace subsystem
{

   // class CLASS_DECL_SUBSYSTEM GlobalMutexInterface :
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


   //using GlobalMutexInterface = particle_interface<GlobalMutexInterface>;


   class CLASS_DECL_SUBSYSTEM GlobalMutexComposite :
      virtual public Composite < GlobalMutexInterface >
   {
   public:


      ImplementCompositeø(GlobalMutex, globalmutex)


      //GlobalMutex(const ::scoped_string & scopedstrName = 0, bool interSession = false, bool throwIfExist = false);
      //GlobalMutex();
      // {
      //
      //    m_pparticleThis->initialize_global_mutex(scopedstrName, interSession, throwIfExist);
      //
      // }
      //~GlobalMutex() override;


         void initialize_global_mutex(const ::scoped_string& scopedstrName = {}, bool interSession = false, bool throwIfExist = false) override
      {

         m_pglobalmutex->initialize_global_mutex(scopedstrName, interSession, throwIfExist);

      }


      /**
       * Inherited from lockable.
       */
      ::e_status lock() override
      {

         return m_pglobalmutex->lock();

      }

      /**
       * Inherited from lockable.
       */
      void unlock() override
      {

         m_pglobalmutex->unlock();

      }

   };


    class CLASS_DECL_SUBSYSTEM GlobalMutexAggregate :
    virtual public Aggregate< GlobalMutexComposite >
    {
    public:

        ImplementBaseø(GlobalMutex);

    };


   class CLASS_DECL_SUBSYSTEM GlobalMutex :
   virtual public Object< GlobalMutexAggregate >
   {
   public:


   };


} // namespace subsystem
