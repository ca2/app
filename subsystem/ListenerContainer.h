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


//#include aaa_<vector>

////#include "subsystem/thread/critical_section.h"
////#include "subsystem/thread/critical_section.h"

namespace subsystem
{
   template<class T> class ThreadSafeVector : public ::array_base<T>,
                                        public critical_section {
   public:
      virtual ~ThreadSafeVector() { };
   };

   //
   // Template class that contains listeners array and methods
   // for adding, removing listeners.
   //

   template<class T> class ListenerContainer :
   virtual public ::particle

   {
   public:

      //
      // Adds listener to class listeners ::list_base
      //

      void addListener(T listener) {
         critical_section_lock l(&m_listeners);

         typename ::array_base<T>::iterator it;
         for (it = m_listeners.begin(); it != m_listeners.end(); it++) {
            T current = *it;
            if (current == listener) {
               return ;
            } // if found
         } // for all listeners
         m_listeners.add(listener);
      } // void

      void removeAllListeners() {
         critical_section_lock l(&m_listeners);

         m_listeners.clear();
      }

      //
      // Removes listener from class listeners ::list_base
      //

      void removeListener(T listener) {
         critical_section_lock l(&m_listeners);

         typename ::array_base<T>::iterator it;
         for (it = m_listeners.begin(); it != m_listeners.end(); it++) {
            T current = *it;
            if (current == listener) {
               m_listeners.erase(it);
               return ;
            } // if found
         } // for all listeners
      } // void

   protected:
      ThreadSafeVector<T> m_listeners;
   };
} // namespace subsystem

