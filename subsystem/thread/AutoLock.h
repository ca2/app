// Copyright (C) 2008,2009,2010,2011,2012 GlavSoft LLC.
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


class LockableBase
{
public:

   virtual void lock() = 0;
   virtual void unlock() = 0;

};

   template < typename LOCKABLE >
class AutoLock
{
public:
      bool m_bLocked;
  AutoLock(LOCKABLE * plockable):
      m_plockable(plockable),
      m_bLocked(false)
  {
lock();
     //m_plockable->lock();
  }
      AutoLock(const ::pointer < LOCKABLE > & plockable):
          AutoLock(plockable.m_p)
  {

     //m_plockable->lock();
  }
      ~AutoLock()
  {

     unlock();

  }
void lock()
  {

     if (!m_bLocked)
     {

        m_bLocked=true;
        m_plockable->lock();
     }
  }
      void unlock()
  {

     if (m_bLocked)
     {

        m_bLocked = false;
        m_plockable->unlock();

     }

  }
//protected:
  LOCKABLE  *m_plockable;
};



template < typename LOCKABLE >
class Lockable :
public LOCKABLE,
virtual public LockableBase
{
public:

   using LOCKABLE::LOCKABLE;

   void lock() override
   {

      LOCKABLE::lock();
   }

   void unlock() override
   {

      LOCKABLE::unlock();

   }


};


class lockable_critical_section :
virtual public Lockable<critical_section>
{
public:

   using BASE = Lockable<critical_section>;

   using BASE::BASE;


};