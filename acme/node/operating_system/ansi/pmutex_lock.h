//
// Created by camilo on 13/02/2021. <3TBS_!!
//
#pragma once


class pmutex_lock
{
public:


   pthread_mutex_t * m_mutex;

   bool m_bLock;


   pmutex_lock(pthread_mutex_t * pmutex, bool bStartLocked = true) :
      m_mutex(pmutex),
      m_bLock(false)
   {

      if(bStartLocked)
      {

         lock();

      }

   }


   ~pmutex_lock()
   {

      unlock();

   }


   void lock()
   {

      if(::is_null(m_mutex))
      {

         return;

      }

      pthread_mutex_lock(m_mutex);

      m_bLock = true;

   }


   void unlock()
   {

      if(::is_null(m_mutex))
      {

         return;

      }

      if(m_bLock)
      {

         m_bLock = false;

         pthread_mutex_unlock(m_mutex);

      }

   }

};



