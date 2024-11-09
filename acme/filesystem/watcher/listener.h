//
// Created by camilo on 30/12/2021 11:35 BR <3ThomasBorregaardS~ensen!!
//
#pragma once


#include "action.h"
//#include "acme/prototype/collection/array.h"
//#include "acme/prototype/collection/comparable_eq_array.h"
//#include "acme/prototype/collection/comparable_array.h"
//#include "acme/prototype/prototype/function.h"


namespace file
{


   class watch;
   class watcher;
   class listener;

   //using watch_id = huge_integer;


   typedef ::pointer_array < watch> file_watch_array;






   //using listener_function = ::function < void(::file::action *) >;


   /// Basic interface for listening for file happenings.
   /// @class file_watch_listener
   class listener :
      public ::function <  void(::file::action*) >
   {
   public:

      
      //::function <  void(::file::action*) >       m_functionListener;

      comparable_array < watch * >       m_watcha;

      using function::function;


      //listener(listener_function function = nullptr);
      ~listener()
      {

      }
 


      /// Handles the action file action
      /// @lparam watchwatch_id The watch watch_id for the directory
      /// @lparam dir The directory
      /// @lparam filename The filename that was accessed (not full path)
      /// @lparam action Action that was performed
      //void operator()(::file::action* paction)
      //{

      //   m_functionListener(paction);

      //}

      //bool operator == (const listener& listener) const
      //{

      //   return m_functionListener.m_pbase == listener.m_functionListener.m_pbase;

      //}


   }; // class file_watch_listener



} // namespace file_watcher



