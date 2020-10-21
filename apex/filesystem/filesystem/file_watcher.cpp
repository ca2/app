//
//
//	   Main header for the watcher class. Declares all implementation
//	   classes to reduce compilation overhead.
//
//	   @author James Wynn
//	   @date 4/15/2009
//
//	   Copyright (c) 2009 James Wynn (james@jameswynn.com)
//
//	   Permission is hereby granted, free of charge, to any person obtaining a copy
//	   of this software and associated documentation files (the "Software"), to deal
//	   in the Software without restriction, including without limitation the rights
//	   to uxse, cxopy, mxodify, mxerge, pxublish, dxistribute, sxublicense, and/or sxell
//	   copies of the Software, and to permit persons to whom the Software is
//	   furnished to do so, subject to the following conditions:
//
//
#include "framework.h"


namespace file
{


   watch::watch()
   {
      
      m_pthis = this;
      
   }


   watch::~watch()
   {

      try
      {

         for (auto & plistener : m_listenera.ptra())
         {

            try
            {

               plistener->m_watchptra.remove(this);

            }
            catch (...)
            {

            }

         }

      }
      catch (...)
      {

      }

   }


   bool watch::open(const ::file::path & pathFolder, bool bRecursive)
   {

      m_pathFolder = pathFolder;

      m_bRecursive = bRecursive;

      return true;

   }


   void watch::add_listener(listener * plistener)
   {

      m_listenera.add_unique(plistener);

      plistener->m_watchptra.add_unique(this);

   }


   void watch::remove_listener(listener * plistener)
   {

      m_listenera.remove(plistener);

      plistener->m_watchptra.remove(this);

      if (m_listenera.is_empty())
      {

         m_pwatcher->remove_watch(m_id);

      }

   }


   void watch::handle_action(action * paction)
   {

      for (auto & plistener : m_listenera.ptra())
      {

         plistener->handle_file_action(paction);

      }

   }


   bool watch::step()
   {

      return true;

   }


   listener::listener()
   {

   }


   listener::~listener()
   {

      try
      {

         for (auto & pwatch : m_watchptra.ptra())
         {

            try
            {

               pwatch->remove_listener(this);

            }
            catch (...)
            {

            }

         }

      }
      catch (...)
      {

      }


   }


   void listener::handle_file_action(::file::action * paction)
   {

      UNREFERENCED_PARAMETER(paction);

   }

   watcher::watcher()
   {

      m_idLast = 0;
      m_bCreateWatchThread = true;


   }


   watcher::~watcher()
   {

   }


   watch_id watcher::add_watch(const ::file::path & pathFolder, listener * plistenerParam, bool bRecursive)
   {

      if (pathFolder.is_empty())
      {

         return -1;

      }

      __pointer(listener) plistener(plistenerParam);

      sync_lock sl(mutex());

      __pointer(watch) pwatch;

      try
      {

         __construct(pwatch);

         pwatch->m_pwatcher = this;

         pwatch->m_id = ++m_idLast;

         m_watchmap[pwatch->m_id] = pwatch;

         if (m_bCreateWatchThread)
         {

            start(m_pthread);

         }

         if (!pwatch->open(pathFolder, bRecursive))
         {

            m_watchmap.remove_key(pwatch->m_id);

            return -1;

         }

      }
      catch (...)
      {


      }

      if (pwatch.is_null())
      {

         return -1;

      }

      pwatch->add_listener(plistener);

      pwatch->m_pathFolder = pathFolder;

      return pwatch->m_id;

   }


   void watcher::remove_watch(watch_id watch_id)
   {

      sync_lock sl(mutex());

      watch_map::pair * ppair = m_watchmap.plookup(watch_id);

      if (ppair == nullptr)
         return;

      watch * pwatch = ppair->element2();

      pwatch->m_pwatchRelease = pwatch;

   }



   ::estatus     watcher::run()
   {
      
      m_pthread = ::get_task();

      while (::thread_get_run())
      {

         if (!step())
         {

            break;

         }

         while (m_pthread->defer_pump_message());

      }
      
      m_pthread.release();

      return ::success;

   }


   void watcher::remove_watch(const ::file::path & pathFolder)
   {

      sync_lock sl(mutex());

      for (auto & pair : m_watchmap)
      {

         if (::file_is_equal_path(pathFolder, pair.element2()->m_pathFolder))
         {

            remove_watch(pair.element1());

            return;

         }

      }

   }




   bool watcher::step()
   {

restart:

      for (auto & pair : m_watchmap)
      {

         if (pair.element2()->m_pwatchRelease.is_set())
         {

            pair.element2()->m_bStop = true;

            pair.element2()->m_pwatchRelease.release();

            m_watchmap.remove_key(pair.element1());

            goto restart;

         }

         pair.element2()->step();

      }

      if (m_watchmap.is_empty())
      {

         return false;

      }

      return true;

   }


} //namespace watcher



