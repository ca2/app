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


#include "apex/parallelization/thread.h"


namespace file
{


   class watch;
   class watcher;
   class listener;
   class os_watcher;
   

   class CLASS_DECL_APEX watcher :
      virtual public ::thread
   {
   public:

      
      void *               m_pThis;

      typedef ::map < watch_id, ::pointer<watch >>watch_map;

      watch_map            m_watchmap;

      watch_id             m_atomLast;

      bool                 m_bCreateWatchThread;


      watcher();
      ~watcher() override;


      virtual watch_id add_watch(const ::file::path & pathFolder, const listener & listener, bool bRecursive);

      virtual void erase_watch(const ::file::path & pathFolder);

      virtual void erase_watch(watch_id watch_id, ::function < void () > functionErased = nullptr);

      virtual void run() override;

      virtual bool step() override;


   };//end file_watcher


} // namespace file_watcher



