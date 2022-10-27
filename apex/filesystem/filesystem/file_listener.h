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






   //using listener_function = ::function < void(::file::action *) >;


   /// Basic interface for listening for file events.
   /// @class file_watch_listener
   class CLASS_DECL_APEX listener :
      public ::function <  void(::file::action *) >
   {
   public:

      //listener_function    m_function;

      comparable_array < ::pointer<watch >>       m_watcha;

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



