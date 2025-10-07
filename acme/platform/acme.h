//
//  base_static_start.h
//  acme
//
//  Created by camilo on 14/04/2021. 00:30 BRT <3TBS_!!
//
#pragma once


#include "acme/prototype/prototype/pointer.h"
#include "acme/parallelization/critical_section.h"
#include "acme/prototype/time/time/time.h"

namespace acme
{


   class singleton_pointer;


   class CLASS_DECL_ACME acme
   {
   public:


      //static ::acme::acme *                     s_p;


      //::pointer < ::platform::platform >      m_pplatform;
      ::heap::management *                      m_pheapmanagement;

      //::pointer < manual_reset_happening >      m_pmanualresethappeningSystemTaskFinished;

#if REFERENCING_DEBUGGING 


      ::referencing_debugging *              m_preferencingdebugging;

#endif

      class ::time                           m_timeStart;




      acme();
      ~acme();


#if defined(WINDOWS) && defined(UNICODE)

      virtual void initialize_system(int argc, wchar_t * argv[], wchar_t * envp[]);

      virtual void initialize_system(hinstance hinstanceThis, hinstance hinstancePrev, wchar_t * pCmdLine, int nCmdShow);

#endif

      virtual void initialize_system(int argc, char ** argv, char ** envp);


#if REFERENCING_DEBUGGING

      void initialize_referencing_debugging();
//      void dump_pending_releases();

#endif
      
      class ::time start_time();


      virtual ::platform::platform * platform();
      ::heap::management * heap() { return m_pheapmanagement; }

      //virtual void on_system_before_destroy();

   protected:
      
      void acme_construct();
      void acme_destruct();


      //void acme_construct_platform_dependent();
      //void acme_destruct_platform_dependent();


      void initialize_memory_management();
      void finalize_memory_management();


      //void initialize_message_queue();
      //void finalize_message_queue();


      virtual void on_acme_before_destroy();


   };


   //class CLASS_DECL_ACME singleton
   //{
   //public:


   //   static acme * s_pacme;


   //   singleton();
   //   ~singleton();


   //   acme * operator ->() { return s_pacme; }


   //};


   CLASS_DECL_ACME ::acme::acme * get();


} // namespace acme



