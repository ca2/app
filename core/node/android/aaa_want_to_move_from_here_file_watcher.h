////
////
////	   Main header for the file_watcher class. Declares all implementation
////	   classes to reduce compilation overhead.
////
////	   @author James Wynn
////	   @date 4/15/2009
////
////	   Copyright (c) 2009 James Wynn (james@jameswynn.com)
////
////	   Permission is hereby granted, free of charge, to any person obtaining a copy
////	   of this software and associated documentation files (the "Software"), to deal
////	   in the Software without restriction, including without limitation the rights
////	   to uxse, cxopy, mxodify, mxerge, pxublish, dxistribute, sxublicense, and/or sxell
////	   copies of the Software, and to permit persons to whom the Software is
////	   furnished to do so, subject to the following conditions:
////
////
//#pragma once
//
//
//namespace file
//{
//
//
//   class CLASS_DECL_CORE  os_watch :
//      virtual public watch
//   {
//   public:
//
//
//
//      os_watch();
//      virtual ~os_watch();
//      /// type for a map from id to watch_struct pointer
//      //typedef map < id, id, __pointer(watch), __pointer(watch) > WatchMap;
//
//   ////public:
//   //   ///
//   //   ///
//   //   os_watch(::object * pobject);
//
//   //   ///
//   //   ///
//   //   virtual ~os_watch();
//
//   //   /// Add a directory watch
//   //   /// @exception file_not_found_exception Thrown when the requested directory does not exist
//   //   id add_watch(const string & directory, listener * watcher, bool bRecursive, bool bOwn);
//
//   //   /// Remove a directory watch. This is a brute force lazy search O(nlogn).
//   //   void erase_watch(const string & directory);
//
//   //   /// Remove a directory watch. This is a map lookup O(logn).
//   //   void erase_watch(id watchid);
//
//   //   string watch_path(id watchid);
//
//   //   /// Updates the watcher. Must be called often.
//   //   bool select();
//
//   //   virtual ::e_status     run() override;
//
//   //   /// Handles the action
//   //   virtual void handle_action(action * psubject);
//
//   ////private:
//   //   /// Map of id to watch_struct pointers
//   //   //WatchMap m_watchmap;
//   //   /// The last watchid
//   //   //id mLastWatchID;
//   //   /// inotify file descriptor
//   //   //i32 mFD;
//   //   /// time out data
//   //   //struct timeval mTimeOut;
//   //   /// File descriptor set
//   //   //void *  m_pDescriptorSet; // fd_set
//
//
//   };
//
//
//   //class watch_item
//   //{
//   //public:
//
//   //   id                            m_id;
//   //   string                        m_strDirName;
//
//   //};
//
//
//   //class watch :
//   //   public watch_item,
//   //   virtual public ::object
//   //{
//   //public:
//
//   //   bool                          m_bRecursive;
//   //   listener *                    m_plistener;
//   //   array < watch_item >          m_itema;
//   //   bool                          m_bOwn;
//   //   file_watcher_impl *           m_pwatcher;
//
//
//   //};
//
//
//   class os_watcher :
//      virtual public watcher
//   {
//   public:
//
//
//      i32 mFD;
//      struct timeval mTimeOut;
//      fd_set mDescriptorSet;
//
//
//      os_watcher();
//      virtual ~os_watcher();
//
//
//      virtual watch_id add_watch(const ::file::path& pathFolder, listener* plistenerParam, bool bRecursive) override;
//
//
//      virtual bool step() override;
//
//      virtual ::e_status     run() override;
//
//
//   };
//
//
//} // namespace file_watcher
//
//
//
