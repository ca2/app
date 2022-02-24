//
//  base_static_start.h
//  apex
//
//
//
#pragma once



#include "acme/platform/acme.h"


class plex_heap_alloc_array;
class simple_trace;


namespace apex
{





   //extern CLASS_DECL_APEX critical_section* g_pcsGlobal;

   //extern CLASS_DECL_APEX string_to_string* g_pmapFontFaceName;

   //extern CLASS_DECL_APEX critical_section* g_pcsFont;

   //extern critical_section* g_pcsRefDbg;









   //extern critical_section * g_pcsTrace;

   //extern ::matter * g_ptrace;

   //extern simple_trace * g_psimpletrace;



   extern CLASS_DECL_APEX array < matter* >* g_paAura;












   CLASS_DECL_APEX void ref();

//   class static_start
//   {
//   public:
//
//
//      bool m_bRef;


      void initialize_system();
      void finalize_system();

//      static static_start g_staticstart;
//
//      void this_ref();
//
//
//
//      void construct();
//
//
//      void init();
//      void term();
//
//
//      void init_windowing();
//      void term_windowing();
//
//
//      //void init_id_pool();
//      //void term_id_pool();
//
//
//   };


} // namespace apex


//extern ::apex::apex __apex;

//::psystem

//__apex.g_psystem

