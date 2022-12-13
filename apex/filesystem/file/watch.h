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


////#include "acme/primitive/primitive/object.h"
//#include "acme/filesystem/filesystem/path.h"


namespace file
{


   class watch;
   class watcher;
   class listener;
   class os_watch;


   class CLASS_DECL_APEX watch :
      virtual public object
   {
   public:


      watch_id                            m_watchid;
      ::file::path                        m_pathFolder;
      comparable_eq_array < listener >    m_listenera;
      ::pointer<thread>                   m_pthread;
      bool                                m_bRecursive;
      watcher *                           m_pwatcher;
      ::pointer<watch>                    m_pwatchRelease;
      bool                                m_bStop;
      void *                              m_pthis;
      ::function < void () >              m_functionDestroy;
      

      watch();
      ~watch() override;


      virtual bool open(const ::file::path & pathFolder, bool bRecursive);


      virtual void add_listener(const listener & listener);
      virtual void erase_listener(const listener & listener);

      virtual void handle_action(action * paction);

      bool step() override;

      void _addAll();
      void _addFile(const char * name, bool imitEvents = true);
      void _removeFile(const char * name, bool imitEvents = true);
      void _rescan();


   };

   
} // namespace file



