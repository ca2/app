//
// Created by camilo on Sep/10/23 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "_string.h"



#undef DO
#define DO(e) case e: return STRINGFY(e)


const char * as_psz(::experience::enum_frame eframe)
{

   switch (eframe)
   {
      DO(::experience::e_frame_none);
   DO(::experience::e_frame_sizing_left);
   DO(::experience::e_frame_sizing_top);
   DO(::experience::e_frame_sizing_right);
   DO(::experience::e_frame_sizing_bottom);
   DO(::experience::e_frame_sizing_top_left);
   DO(::experience::e_frame_sizing_top_right);
   DO(::experience::e_frame_sizing_bottom_left);
   DO(::experience::e_frame_sizing_bottom_right);
   DO(::experience::e_frame_client);
default:
   return nullptr;

}

};


::string as_string(::experience::enum_frame eframe)
{

   return as_psz(eframe);

}


#undef DO