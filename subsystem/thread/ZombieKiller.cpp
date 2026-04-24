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
#include "framework.h"
#include "ZombieKiller.h"


namespace subsystem
{
   ZombieKiller::ZombieKiller()
   {
      //resume();
   }

   ZombieKiller::~ZombieKiller()
   {
      // if (isActive()) {
      //    terminate();
      //    wait();
      // }
      // killAllZombies();
   }


   void ZombieKiller::start()
   {

      m_papplication->fork([this]()
      {

         run();

      });

   }


   void ZombieKiller::run()
   {
      while (task_get_run())
      {
         deleteDeadZombies();
         preempt(50_ms);
      }
   }

   void ZombieKiller::addZombie(Thread *zombie)
   {
      critical_section_lock l(&m_lockObj);

      m_zombies.add(zombie);
   }

   void ZombieKiller::deleteDeadZombies()
   {
      critical_section_lock l(&m_lockObj);


      for (auto pthread : m_zombies)
      {

         if (!pthread->isActive()) {
            m_zombies.erase(pthread);
         }
         //  else {
         //   iter++;
         // }
      }
   }

   void ZombieKiller::killAllZombies()
   {

      critical_section_lock l(&m_lockObj);

      for (auto pthread  : m_zombies)
      {
         pthread->terminate();
      }
      for (auto pthread : m_zombies)
      {
         pthread->wait();
      }

      deleteDeadZombies();
   }

}  // namespace subsystem