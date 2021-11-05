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
//	   furnished to do so, subject to the following conditions:
//
//
#pragma once


namespace file
{


   class watch;
   class watcher;
   class listener;


   using watch_id = i64;


   typedef ::array < watch_id > file_watch_array;


   /// Actions to listen for. Rename will send two events, one for
   /// the deletion of the old file, and one for the creation of the
   /// new file.
   enum enum_action
   {
      
      
      e_action_none = 0,
      /// Sent when a file is created or renamed
      e_action_add = 1,
      /// Sent when a file is deleted or renamed
      e_action_delete = 2,
      /// Sent when a file is modified
      e_action_modify = 4
      

   };


   // by CAMILO <3tbs
   class CLASS_DECL_APEX action
   {
   public:


      watch *                          m_pwatch;
      watch_id                         m_id;
      ::file::path                     m_pathFolder;
      ::file::path                     m_pathFile;
      enumeration < enum_action >      m_eaction;


   };


   /// Basic interface for listening for file events.
   /// @class file_watch_listener
   class CLASS_DECL_APEX listener :
      virtual public ::object
   {
   public:


      __pointer_array(watch)     m_watchptra;


      listener();
      virtual ~listener();

      
      /// Handles the action file action
      /// @lparam watchwatch_id The watch watch_id for the directory
      /// @lparam dir The directory
      /// @lparam filename The filename that was accessed (not full path)
      /// @lparam action Action that was performed
      virtual void handle_file_action(::file::action * paction);


   }; // class file_watch_listener


   template < typename PRED >
   class predicate_listener :
      virtual public listener
   {
   public:


      PRED m_predicate;
      

      predicate_listener(PRED pred) :
         m_predicate(pred)
      {
      }

      /// Handles the action file action
      /// @lparam watchwatch_id The watch watch_id for the directory
      /// @lparam dir The directory
      /// @lparam filename The filename that was accessed (not full path)
      /// @lparam action Action that was performed
      virtual void handle_file_action(::file::action * paction) override
      {

         m_predicate(paction);

      }


   };


   class os_watch;


   class CLASS_DECL_APEX watch :
      virtual public object
   {
   public:


      watch_id                            m_id;
      ::file::path                        m_pathFolder;
      __pointer_array(listener)           m_listenera;
      __pointer(thread)                   m_pthread;
      bool                                m_bRecursive;
      watcher *                           m_pwatcher;
      __pointer(watch)                    m_pwatchRelease;
      bool                                m_bStop;
      void *                              m_pthis;
      

      watch();
      virtual ~watch();


      virtual bool open(const ::file::path & pathFolder, bool bRecursive);


      virtual void add_listener(listener * plistener);
      virtual void erase_listener(listener * plistener);

      virtual void handle_action(action * psubject);

      virtual ::e_status step();


   };

   
   class os_watcher;
   

   class CLASS_DECL_APEX watcher :
      virtual public ::thread
   {
   public:

      
      void *               m_pThis;

      typedef ::map < watch_id, __pointer(watch) > watch_map;

      watch_map            m_watchmap;

      watch_id             m_idLast;

      bool                 m_bCreateWatchThread;
      
      watcher();
      virtual ~watcher();


      template < typename PRED >
      watch_id predicate_add_watch(const ::file::path & pathFolder, PRED pred, bool bRecursive)
      {

         return add_watch(pathFolder, __new(predicate_listener < PRED >(pred)), bRecursive);

      }

      virtual watch_id add_watch(const ::file::path & pathFolder, listener * plistener, bool bRecursive);

      virtual void erase_watch(const ::file::path & pathFolder);

      virtual void erase_watch(watch_id watch_id);

      virtual ::e_status run() override;

      virtual ::e_status step() override;


   };//end file_watcher


} // namespace file_watcher



