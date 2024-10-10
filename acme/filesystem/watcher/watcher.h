//
//
//	   Main header for the file_watcher class. Declares all implementation
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
#pragma once


#include "listener.h"
#include "acme/parallelization/task.h"


namespace file
{


   class watch;
   class watcher;
   class listener;
   class os_watcher;
   

   class CLASS_DECL_ACME watcher :
      virtual public ::task
   {
   public:

      
      void *               m_pThis;

      typedef ::set < ::pointer<::file::watch >>watch_set;

      watch_set            m_watchset;

      //::pointer < ::file::watch>   m_watchLast;

      bool                 m_bCreateWatchThread;


      watcher();
      ~watcher() override;


      virtual ::file::watch * add_watch_listener(const ::file::path& pathFolder, const listener& listener, bool bRecursive);

      virtual ::file::watch * add_watch(const ::file::path & pathFolder, typename listener::base * pbase, bool bRecursive);

      virtual void erase_watch(const ::file::path & pathFolder);

      virtual void erase_watch(::file::watch * pwatch, ::function < void () > functionErased = nullptr);

      void run() override;

      virtual bool file_watcher_step();


   };//end file_watcher


} // namespace file_watcher



