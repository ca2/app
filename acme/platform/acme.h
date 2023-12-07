//
//  base_static_start.h
//  acme
//
//  Created by camilo on 14/04/2021. 00:30 BRT <3TBS_!!
//
#pragma once


#include "acme/primitive/primitive/pointer.h"
#include "acme/parallelization/critical_section.h"

class task_message_queue;

class referencing_debugging;

namespace acme
{


   class CLASS_DECL_ACME acme
   {
   public:


      inline static ::acme::acme *           s_pacme;
      ::pointer < ::task_message_queue >     m_ptaskmessagequeue;
      ::pointer < ::platform::platform >     m_pplatform;
      ::heap::management *                   m_pheapmanagement;




#if REFERENCING_DEBUGGING 


      ::referencing_debugging *              m_preferencingdebugging;

#endif

      acme();
      ~acme();


#if defined(WINDOWS) && defined(UNICODE)

      void initialize(int argc, wchar_t * argv[], wchar_t * envp[]);

      void initialize(hinstance hinstanceThis, hinstance hinstancePrev, wchar_t * pCmdLine, int nCmdShow);

#else

      void initialize(int argc, platform_char ** argv, platform_char ** envp);

#endif


#if REFERENCING_DEBUGGING

      void initialize_referencing_debugging();
//      void dump_pending_releases();

#endif


      ::platform::platform * platform() { return m_pplatform; }
      ::heap::management * heap() { return m_pheapmanagement; }
      ::task_message_queue * task_message_queue() { return m_ptaskmessagequeue; }



   protected:
      
      void acme_construct();
      void acme_destruct();


      void acme_construct_platform_dependent();
      void acme_destruct_platform_dependent();


      void initialize_memory_management();
      void finalize_memory_management();


      void initialize_message_queue();
      void finalize_message_queue();


   };


   inline ::acme::acme * get() { return ::acme::acme::s_pacme; }

} // namespace acme



