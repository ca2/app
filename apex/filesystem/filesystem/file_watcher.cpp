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
//	   furnished to do so, topic to the following conditions:
//
//
#include "framework.h"
#include "file_watcher.h"



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

         for (auto & listener : m_listenera)
         {

            try
            {

               listener.m_watcha.erase(this);

            }
            catch (...)
            {

            }

         }

      }
      catch (...)
      {

      }

      if (m_functionDestroy)
      {

         m_functionDestroy();

      }

   }


   bool watch::open(const ::file::path & pathFolder, bool bRecursive)
   {

      m_pathFolder = pathFolder;

      m_bRecursive = bRecursive;

      return true;

   }


   void watch::add_listener(const listener & listenerParam)
   {

      auto & listener = m_listenera.insert_unique(listenerParam);

      listener.m_watcha.add_unique(this);

   }


   void watch::erase_listener(const listener & listener)
   {

      m_listenera.erase(listener);

      if (m_listenera.is_empty())
      {

         m_pwatcher->erase_watch(m_watchid);

      }

   }


   void watch::handle_action(action * paction)
   {

      for (auto & listener : m_listenera)
      {

         listener(paction);

      }

   }


   bool watch::step()
   {

      //return ::success;

      return true;

   }


   //listener::listener(const listener_function function) :
   //   m_function(function)
   //{

   //}


   listener::~listener()
   {


   }


   //void listener::handle_file_action(::file::action * paction)
   //{

   //   if (m_function)
   //   {

   //      m_function(paction);

   //   }

   //}


   watcher::watcher()
   {

      m_pThis = nullptr;
      m_atomLast = 0;
      m_bCreateWatchThread = true;

   }


   watcher::~watcher()
   {

   }


   //watch_id watcher::watch_folder_with_listener_function(const ::file::path & pathFolder, listener_function function, bool bRecursive)
   //{

   //   return watch_folder_with_listener(pathFolder, __new(listener(function)), bRecursive);

   //}


   watch_id watcher::add_watch(const ::file::path & pathFolder, const listener & listener, bool bRecursive)
   {

#ifdef ANDROID
      return -1;
#endif

      if (pathFolder.is_empty())
      {

         return -1;

      }

      synchronous_lock synchronouslock(mutex());

      __pointer(watch) pwatch;

      __construct(pwatch);

      pwatch->m_pwatcher = this;

      pwatch->m_atom = ++m_atomLast;

      m_watchmap[pwatch->m_atom] = pwatch;

      //if (m_bCreateWatchThread)
      //{

      //   if (m_htask == nullptr)
      //   {

      //      branch();

      //   }

      //}

      if (!pwatch->open(pathFolder, bRecursive))
      {

         m_watchmap.erase_key(pwatch->m_atom);

         return -1;

      }

      if (m_bCreateWatchThread)
      {

         if (m_htask == nullptr)
         {

            branch();

         }

      }

      if (pwatch.is_null())
      {

         return -1;

      }

      pwatch->add_listener(listener);

      pwatch->m_pathFolder = pathFolder;

      return pwatch->m_atom;

   }


   void watcher::erase_watch(watch_id watch_id, ::function < void () > functionErased)
   {

      synchronous_lock synchronouslock(mutex());

      watch_map::pair * ppair = m_watchmap.plookup(watch_id);

      if (ppair == nullptr)
      {

         return;

      }

      watch * pwatch = ppair->element2();

      manual_reset_event event;

      pwatch->m_functionDestroy = functionErased;

      pwatch->m_pwatchRelease = pwatch;


   }



   void watcher::run()
   {
      
      while (task_get_run())
      {

         if (!step())
         {

            break;

         }

         while (defer_pump_message());

      }
      
      //return ::success;

   }


   void watcher::erase_watch(const ::file::path & pathFolder)
   {

      synchronous_lock synchronouslock(mutex());

      for (auto & pair : m_watchmap)
      {

         if (::file_path_is_equal(pathFolder, pair.element2()->m_pathFolder))
         {

            erase_watch(pair.element1());

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

            pair.element2()->m_listenera.clear();

            m_watchmap.erase_key(pair.element1());

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



