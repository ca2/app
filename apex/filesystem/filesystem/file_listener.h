//
// Created by camilo on 30/12/2021 11:35 BR <3ThomasBorregaardS~ensen!!
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


      watch * m_pwatch;
      watch_id                         m_atom;
      ::file::path                     m_pathFolder;
      ::file::path                     m_pathFile;
      enumeration < enum_action >      m_eaction;


   };


   //using listener_function = ::function < void(::file::action *) >;


   /// Basic interface for listening for file events.
   /// @class file_watch_listener
   class CLASS_DECL_APEX listener :
      public ::function <  void(::file::action *) >
   {
   public:

      //listener_function    m_function;

      comparable_array < __pointer(watch) >        m_watcha;

      using function::function;


      //listener(listener_function function = nullptr);
      ~listener();


      /// Handles the action file action
      /// @lparam watchwatch_id The watch watch_id for the directory
      /// @lparam dir The directory
      /// @lparam filename The filename that was accessed (not full path)
      /// @lparam action Action that was performed
      //virtual void handle_file_action(::file::action * paction);


   }; // class file_watch_listener



} // namespace file_watcher



