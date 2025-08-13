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
#include "listener.h"
#include "watcher.h"
#include "watch.h"
#include "acme/parallelization/manual_reset_happening.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/application.h"


namespace file
{


   //listener::~listener()
   //{


   //}


   //void listener::handle_file_action(::file::action * paction)
   //{

   //   if (m_function)
   //   {

   //      m_function(paction);

   //   }

   //}


   watcher::watcher()
   {

      //m_pThis = nullptr;
      //m_pfilewatchLast = 0;
      m_bCreateWatchThread = true;

   }


   watcher::~watcher()
   {

   }


   //watch_id watcher::watch_folder_with_listener_function(const ::file::path & pathFolder, listener_function function, bool bRecursive)
   //{

   //   return watch_folder_with_listener(pathFolder, __allocate listener(function), bRecursive);

   //}

   
   ::file::watch * watcher::add_watch(const ::file::path& pathFolder, typename listener::base* pbase, bool bRecursive)
   {

      return add_watch_listener(pathFolder, pbase, bRecursive);

   }


   void watcher::destroy()
   {

      for (auto& item : m_watchset)
      {

         item.element().defer_destroy();

      }

      m_watchset.clear();

      ::task::destroy();

   }


   ::file::watch * watcher::add_watch_listener(const ::file::path & pathFolder, const listener & listener, bool bRecursive)
   {

#ifdef __ANDROID__
      return nullptr;
#endif

      if (pathFolder.is_empty())
      {

         return nullptr;

      }

      _synchronous_lock synchronouslock(this->synchronization());

      ::pointer<watch>pwatch;

      __øconstruct(pwatch);

      pwatch->m_pwatcher = this;

      m_watchset.set_item(pwatch);

      //if (m_bCreateWatchThread)
      //{

      //   if (!m_htask)
      //   {

      //      branch();

      //   }

      //}

      if (!pwatch->open(pathFolder, bRecursive))
      {

         m_watchset.erase_key(pwatch);

         return nullptr;

      }

      if (m_bCreateWatchThread)
      {

         if (!m_htask)
         {

            application()->post([this]()
               {

                  branch();

               });

         }

      }

      if (pwatch.is_null())
      {

         return nullptr;

      }

      pwatch->add_listener(listener);

      pwatch->m_pathFolder = pathFolder;

      return pwatch;

   }


   void watcher::erase_watch(::file::watch *pwatch, ::function < void () > functionErased)
   {

      synchronous_lock synchronouslock(this->synchronization());

      auto iterator = m_watchset.find(pwatch);

      if (!iterator)
      {

         return;

      }

      manual_reset_happening happening;

      pwatch->m_functionDestroy = functionErased;

   }


   void watcher::run()
   {
      
      while (task_get_run())
      {

         if (!file_watcher_step())
         {

            break;

         }

         //while (defer_pump_message());

      }
      
      //return ::success;

   }


   void watcher::erase_watch(const ::file::path & pathFolder)
   {

      synchronous_lock synchronouslock(this->synchronization());

      for (auto & item : m_watchset)
      {

         if (::file_path_is_equal(pathFolder, item.item()->m_pathFolder))
         {

            erase_watch(item.item());

            return;

         }

      }

   }


   bool watcher::file_watcher_step()
   {

//restart:

      for (auto & item : m_watchset)
      {

         if (::is_set(item.item()))
         {
            
            //if(::is_set(item.item()->m_pwatchRelease))
            //{

            //   item.item()->m_bStop = true;

            //   item.item()->m_pwatchRelease.release();

            //   item.item()->m_listenera.clear();

            //   m_watchset.erase_item(item.item());

            //   goto restart;

            //}

            item.item()->file_watch_step();
            
         }

      }

      if (m_watchset.is_empty())
      {

         return false;

      }

      return true;

   }


} //namespace file



