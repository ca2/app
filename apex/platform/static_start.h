//
//  base_static_start.h
//  apex
//
//
//
#pragma once



#include "acme/platform/static_start.h"


class plex_heap_alloc_array;


namespace apex
{





   //extern CLASS_DECL_APEX critical_section* g_pcsGlobal;

   extern CLASS_DECL_APEX string_to_string* g_pmapFontFaceName;

   extern CLASS_DECL_APEX critical_section* g_pcsFont;

   //extern critical_section* g_pcsRefDbg;









   extern critical_section* g_pcsTrace;

   extern ::generic* g_ptrace;

   extern simple_trace* g_psimpletrace;



   extern CLASS_DECL_APEX array < generic* >* g_paAura;












   CLASS_DECL_APEX void ref();

   class apex
   {
   public:


      bool m_bRef;


      apex();
      ~apex();

      static apex g_apex;
      
      void this_ref();

      
      
      void construct();


      ::estatus init();
      ::estatus term();


      void init_windowing();
      void term_windowing();


      //void init_id_pool();
      //void term_id_pool();


   };


} // namespace apex


//extern ::apex::apex __apex;

//::get_context_system()

//__apex.g_psystem

