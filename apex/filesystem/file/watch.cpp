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
#include "watch.h"
#include "watcher.h"
#include "acme/parallelization/event.h"
#include "apex/filesystem/file/listener.h"


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

      auto & listener = m_listenera.insert_unique(::move(listenerParam));

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


} //namespace file



