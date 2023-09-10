//
// Created by camilo on Sep/10/23 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "_string.h"



#undef DO
#define DO(e) ::pair<::experience::enum_frame, const char *>(e, STRINGFY(e))

::pair<::experience::enum_frame, const char *> g_eframepszpaira[]= {
   DO(::experience::e_frame_none),
   DO(::experience::e_frame_sizing_left),
   DO(::experience::e_frame_sizing_top),
   DO(::experience::e_frame_sizing_right),
   DO(::experience::e_frame_sizing_bottom),
   DO(::experience::e_frame_sizing_top_left),
   DO(::experience::e_frame_sizing_top_right),
   DO(::experience::e_frame_sizing_bottom_left),
   DO(::experience::e_frame_sizing_bottom_right),
   DO(::experience::e_frame_client)
};


::string as_string(::experience::enum_frame eframe)
{

   static ::map<::experience::enum_frame, const char *> s_map(g_eframepszpaira, ARRAY_SIZE(g_eframepszpaira));
   const char * psz = nullptr;
   auto p = s_map.plookup(eframe);

   if(!p)
      return {};
   return p->m_element2;

}


#undef DO